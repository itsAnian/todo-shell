#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "cJSON.h"

const int argnumber = 1; const char *todolist = "todo.json";
const char *todolist_history = "todo_history.json";

void Operation(int id, char *titel, char *description, char *flags[], int flagCount, int operation){
    if(operation == 0){
        printf("abfangen");
    }
    if(operation == 1){
        printf("ADD-Operation");
        cJSON *json = cJSON_CreateObject();
        cJSON_AddNumberToObject(json, "id", id);
        cJSON_AddStringToObject(json, "titel", titel);
        cJSON_AddStringToObject(json, "description", description);
        cJSON *flagsArray = cJSON_CreateArray();
        for (int i = 0; i < flagCount; i++) {
            cJSON_AddItemToArray(flagsArray, cJSON_CreateString(flags[i]));
        }
        cJSON_AddItemToObject(json, "flags", flagsArray);

        char *jsonString = cJSON_Print(json);
        printf("JSON:\n%s\n", jsonString);
    }
    if(operation == 2){}
    if(operation == 3){}
    if(operation == 4){}
    if(operation == 5){}
}

int main(int argc, char* argv[])
{
    int id;
    char *titel;
    char *description;
    char *flags[argc];
    int flagCount = 0;
    int operation = 0;

    if(strcmp(argv[argnumber], "add") == 0){
        printf("ADD\n");
        operation = 1;
    }
    if(strcmp(argv[argnumber], "edit") == 0){
        printf("EDIT\n");
        operation = 2;
    }
    if(strcmp(argv[argnumber], "remove") == 0){
        printf("REMOVE\n");
        operation = 3;
    }
    if(strcmp(argv[argnumber], "finish") == 0){
        printf("FINISH\n");
        operation = 4;
    }
    if(strcmp(argv[argnumber], "list") == 0){
        printf("LIST\n");
        operation = 4;
    }

    for (int i = 0; i < argc; i++) {
        if(strcmp(argv[i], "-t") == 0){
            titel = argv[i+1];
        }
        if(strcmp(argv[i], "-d") == 0){
            description = argv[i+1];
        } 
        if(argv[i][0] == '#'){
            flags[flagCount] = argv[i];
            flagCount++;
        }
    }

    Operation(id, titel, description, flags, flagCount, operation);

    return 0;
}


