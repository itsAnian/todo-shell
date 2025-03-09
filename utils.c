#include "cJSON.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void ThrowError(const char* message)
{
    fprintf(stderr, "Error: %s\n", message);
    exit(EXIT_FAILURE);
}

char* GetPath(bool history)
{
    const char* home = getenv("HOME");
    int pathSize = 512;
    char* path = malloc(pathSize);

    if (history == true) {
        snprintf(path, pathSize, "%s/.todo/todo_history.json", home);
    } else {
        snprintf(path, pathSize, "%s/.todo/todo.json", home);
    }
    return path;
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

void PrintJsonObject(cJSON* obj)
{
    printf("\n\033[1;36mId: \033[0m%s\n\033[1;36mTitel: \033[0m%s\n\033[1;36mDescription: \033[0m%s\n", cJSON_GetObjectItem(obj, "id")->valuestring, cJSON_GetObjectItem(obj, "title")->valuestring, cJSON_GetObjectItem(obj, "description")->valuestring);
    cJSON* flags = cJSON_GetObjectItem(obj, "flags");
    printf("\033[1;36mFlags: \033[0m");
    for (int ii = 0; ii < cJSON_GetArraySize(flags); ii++) {
        printf("%s ", cJSON_GetArrayItem(flags, ii)->valuestring);
    }
    printf("\n");
}

void PrintJsonArray(cJSON* jsonArray)
{
    for (int i = 0; i < cJSON_GetArraySize(jsonArray); i++) {
        cJSON* todo = cJSON_GetArrayItem(jsonArray, i);
        PrintJsonObject(todo);
    }
}
