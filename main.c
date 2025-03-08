#include "cJSON.h"
#include "json_handler.h"
#include "utils.h"
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

const int argnumber = 1;
const char* todolist = "/home/anian/.todo/todo.json";
const char* todolist_history = "/home/anian/.todo/todo_history.json";

void ExecuteOperation(char* id, char* titel, char* description, char* flags[], int flagCount, int operation)
{
    if (operation == 1) {
        // ADD
        cJSON* newTodo = CreateObject(id, titel, description, flags, flagCount);
        cJSON* todos = ReadJsonFromFile(todolist);
        cJSON_AddItemToArray(todos, newTodo);
        SaveJsonToFile(todolist, todos);
        PrintJsonObject(newTodo);
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
        if (flagCount > 0) {
            cJSON* sortedTodo = cJSON_CreateArray();
            for (int i = 0; i < cJSON_GetArraySize(todos); i++) {
                cJSON* todo = cJSON_GetArrayItem(todos, i);
                cJSON* flagObj = cJSON_GetObjectItem(todo, "flags");
                for (int ii = 0; ii < cJSON_GetArraySize(flagObj); ii++) {
                    for (int iii = 0; iii < flagCount; iii++) {
                        if (strcmp(cJSON_GetArrayItem(flagObj, ii)->valuestring, flags[iii]) == 0) {
                            cJSON_AddItemToArray(sortedTodo, cJSON_Duplicate(todo, 1));
                        }
                    }
                }
            }
            PrintJsonArray(sortedTodo);
        } else {
            PrintJsonArray(todos);
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
