#include "cJSON.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

const int argnumber = 1;
const char* todolist = "/home/anian/.todo/todo.json";
const char* todolist_history = "/home/anian/.todo/todo_history.json";

void ThrowError(const char* message)
{
    fprintf(stderr, "Error: %s\n", message);
    exit(EXIT_FAILURE);
}

void SaveJsonToFile(const char* filename, cJSON* json)
{
    char* jsonString = cJSON_Print(json);
    if (!jsonString) {
        ThrowError("Failed to convert JSON to string\n");
    }

    FILE* file = fopen(filename, "w+");
    if (!file) {
        ThrowError("Failed to open File (SaveJsonToFile())");
    }

    fprintf(file, "%s", jsonString);
    fclose(file);
    free(jsonString);
}

cJSON* ReadJsonFromFile(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (!file) {
        ThrowError("Failed to open File (ReadJsonFromFile())");
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    rewind(file);

    char* jsonData = (char*)malloc(length + 1);
    fread(jsonData, 1, length, file);
    jsonData[length] = '\0';
    fclose(file);

    cJSON* jsonArray = cJSON_Parse(jsonData);
    free(jsonData);

    if (!jsonArray) {
        cJSON* jsonArray = cJSON_CreateArray();
        printf("Empty file, or parsing failed");
        return jsonArray;
    }
    return jsonArray;
}

char* GenerateId(int length)
{
    srand(time(NULL));
    char* id = malloc(length);
    const char charset[] = "abcdefghijklmnopqrstuvwxyz0123456789";
    for (int i = 0; i < length; i++) {
        int randomIndex = rand() % (sizeof(charset) - 1);
        id[i] = charset[randomIndex];
    }
    return id;
}

cJSON* CreateObject(char* id, char* titel, char* description, char* flags[], int flagCount)
{
    cJSON* json = cJSON_CreateObject();
    char* randomId = GenerateId(5);
    cJSON_AddStringToObject(json, "id", randomId);
    cJSON_AddStringToObject(json, "titel", titel);
    cJSON_AddStringToObject(json, "description", description);
    cJSON* flagsArray = cJSON_CreateArray();
    for (int i = 0; i < flagCount; i++) {
        cJSON_AddItemToArray(flagsArray, cJSON_CreateString(flags[i]));
    }
    cJSON_AddItemToObject(json, "flags", flagsArray);

    return json;
}

void ExecuteOperation(char* id, char* titel, char* description, char* flags[], int flagCount, int operation)
{
    if (operation == 1) {
        // ADD
        cJSON* newTodo = CreateObject(id, titel, description, flags, flagCount);
        cJSON* todos = ReadJsonFromFile(todolist);
        cJSON_AddItemToArray(todos, newTodo);
        SaveJsonToFile(todolist, todos);

        printf("\n\033[1;36mId: \033[0m%s\n\033[1;36mTitel: \033[0m%s\n\033[1;36mDescription: \033[0m%s\n", cJSON_GetObjectItem(newTodo, "id")->valuestring, cJSON_GetObjectItem(newTodo, "titel")->valuestring, cJSON_GetObjectItem(newTodo, "description")->valuestring);
        cJSON* flags = cJSON_GetObjectItem(newTodo, "flags");
        printf("\033[1;36mFlags: \033[0m");
        for (int ii = 0; ii < cJSON_GetArraySize(flags); ii++) {
            printf("%s ", cJSON_GetArrayItem(flags, ii)->valuestring);
        }
        printf("\n");
    }
    if (operation == 2) {
        // EDIT
    }
    if (operation == 3) {
        // REMOVE
        cJSON* todos = ReadJsonFromFile(todolist);
        for (int i = 0; i < cJSON_GetArraySize(todos); i++) {
            cJSON* todo = cJSON_GetArrayItem(todos, i);
            if (strcmp(cJSON_GetObjectItem(todo, "id")->valuestring, id) == 0) {
                cJSON_DeleteItemFromArray(todos, i);
                break;
            }
        }
        SaveJsonToFile(todolist, todos);
    }
    if (operation == 4) {
        // FINISH
        cJSON* todos = ReadJsonFromFile(todolist);
        cJSON* todo_history = ReadJsonFromFile(todolist_history);
        for (int i = 0; i < cJSON_GetArraySize(todos); i++) {
            cJSON* todo = cJSON_GetArrayItem(todos, i);
            if (strcmp(cJSON_GetObjectItem(todo, "id")->valuestring, id) == 0) {
                cJSON_AddItemToArray(todo_history, cJSON_Duplicate(todo, 1));
                cJSON_DeleteItemFromArray(todos, i);
                break;
            }
        }
        SaveJsonToFile(todolist, todos);
        SaveJsonToFile(todolist_history, todo_history);
    }
    if (operation == 5) {
        // LIST
        cJSON* todos = ReadJsonFromFile(todolist);
        for (int i = 0; i < cJSON_GetArraySize(todos); i++) {
            cJSON* todo = cJSON_GetArrayItem(todos, i);
            printf("\n\033[1;36mId: \033[0m%s\n\033[1;36mTitel: \033[0m%s\n\033[1;36mDescription: \033[0m%s\n", cJSON_GetObjectItem(todo, "id")->valuestring, cJSON_GetObjectItem(todo, "titel")->valuestring, cJSON_GetObjectItem(todo, "description")->valuestring);
            cJSON* flags = cJSON_GetObjectItem(todo, "flags");
            printf("\033[1;36mFlags: \033[0m");
            for (int ii = 0; ii < cJSON_GetArraySize(flags); ii++) {
                printf("%s ", cJSON_GetArrayItem(flags, ii)->valuestring);
            }
            printf("\n");
        }
    }
}

int EvaluateOperation(char* argv[])
{
    int operation = 0;
    switch (*argv[argnumber]) {
    case 'a':
        // ADD
        operation = 1;
        break;
    case 'e':
        // EDIT
        operation = 2;
        break;
    case 'r':
        // REMOVE
        operation = 3;
        break;
    case 'f':
        // FINISH
        operation = 4;
        break;
    case 'l':
        // LIST
        operation = 5;
        break;
    }
    if (operation == 0) {
        ThrowError("No valid operation given");
    }
    return operation;
}

int main(int argc, char* argv[])
{
    char* id;
    char* titel;
    char* description;
    char* flags[argc];
    int flagCount = 0;
    int operation = EvaluateOperation(argv);

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-t") == 0) {
            titel = argv[i + 1];
        }
        if (strcmp(argv[i], "-d") == 0) {
            description = argv[i + 1];
        }
        if (strcmp(argv[i], "-i") == 0) {
            id = argv[i + 1];
        }
        if (argv[i][0] == '#') {
            flags[flagCount] = argv[i];
            flagCount++;
        }
    }

    ExecuteOperation(id, titel, description, flags, flagCount, operation);

    return 0;
}
