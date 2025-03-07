#include "cJSON.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const int argnumber = 1;
const char* todolist = "home/anian/.todo/todo.json";
const char* todolist_history = "home/anian/.todo/todo_history.json";

void ThrowError(const char* message)
{
    fprintf(stderr, "Error: %s\n", message);
    exit(EXIT_FAILURE);
}

void SaveJsonToFile(const char* filename, cJSON* json)
{
    char* jsonString = cJSON_Print(json);
    printf("%s", jsonString);
    if (!jsonString) {
        ThrowError("Failed to convert JSON to string\n");
    }

    FILE* file = fopen(filename, "w");
    if (!file) {
        free(jsonString);
        ThrowError("Failed to open File (SaveJsonToFile())");
    }

    fprintf(file, "%s", jsonString);
    fclose(file);
    free(jsonString);
}

cJSON* ReadJsonFromFile(const char* filename){
    FILE *file = fopen(filename, "r");
    if (!file) {
        ThrowError("Failed to open File (ReadJsonFromFile())");
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    rewind(file);

    char *jsonData = (char *)malloc(length + 1);
    fread(jsonData, 1, length, file);
    jsonData[length] = '\0';
    fclose(file);

    cJSON *jsonArray = cJSON_Parse(jsonData);
    free(jsonData);

    if (!jsonArray){
        ThrowError("Parsing failed");
    }
    return jsonArray;
}

cJSON* CreateObject(int id, char* titel, char* description, char* flags[], int flagCount)
{
    cJSON* json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "id", id);
    cJSON_AddStringToObject(json, "titel", titel);
    cJSON_AddStringToObject(json, "description", description);
    cJSON* flagsArray = cJSON_CreateArray();
    for (int i = 0; i < flagCount; i++) {
        cJSON_AddItemToArray(flagsArray, cJSON_CreateString(flags[i]));
    }
    cJSON_AddItemToObject(json, "flags", flagsArray);

    return json;
}

void ExecuteOperation(int id, char* titel, char* description, char* flags[], int flagCount, int operation)
{
    if (operation == 1) {
        cJSON* newTodo = CreateObject(id, titel, description, flags, flagCount);
        cJSON* todos = ReadJsonFromFile(todolist);
        cJSON_AddItemToArray(todos, newTodo);
        SaveJsonToFile(todolist, todos);
        cJSON_Delete(newTodo);
        cJSON_Delete(todos);
    }
    if (operation == 2) { }
    if (operation == 3) { }
    if (operation == 4) { }
    if (operation == 5) { }
}

int EvaluateOperation(char* argv[])
{
    int operation = 0;
    switch (*argv[argnumber]) {
    case 'a':
        printf("ADD\n");
        operation = 1;
        break;
    case 'e':
        printf("EDIT\n");
        operation = 2;
        break;
    case 'r':
        printf("REMOVE\n");
        operation = 3;
        break;
    case 'f':
        printf("FINISH\n");
        operation = 4;
        break;
    case 'l':
        printf("LIST\n");
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
    int id;
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
        if (argv[i][0] == '#') {
            flags[flagCount] = argv[i];
            flagCount++;
        }
    }

    ExecuteOperation(id, titel, description, flags, flagCount, operation);

    return 0;
}
