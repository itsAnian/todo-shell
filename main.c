#include "cJSON.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int argnumber = 1;
const char* todolist = "todo.json";
const char* todolist_history = "todo_history.json";

void throwError(const char* message)
{
    fprintf(stderr, "Error: %s\n", message);
    exit(EXIT_FAILURE);
}

cJSON CreateObject(int id, char* titel, char* description, char* flags[], int flagCount)
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

    char* jsonString = cJSON_Print(json);
    printf("JSON:\n%s\n", jsonString);
    return *json;
}

void Operation(int id, char* titel, char* description, char* flags[], int flagCount, int operation)
{
    if (operation == 1) {
        CreateObject(id, titel, description, flags, flagCount);
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
        throwError("No valid operation given");
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

    Operation(id, titel, description, flags, flagCount, operation);

    return 0;
}
