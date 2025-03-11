#include "cJSON.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

void ThrowError(const char* message)
{
    fprintf(stderr, "\033[1;31mError: \033[0m%s\n", message);
    exit(EXIT_FAILURE);
}

char* GetPath(char* foldername, char* filename)
{
    const char* home = getenv("HOME");
    int pathSize = 512;
    char* path = malloc(pathSize);

    snprintf(path, pathSize, "%s%s%s", home, foldername, filename);

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

void PrintHelp()
{
    printf("Help for todo command:\n\n");
    printf("Usage:\n");
    printf("  todo add -t \"<Title>\" -d \"<Description>\" \"#<Topic1>\" \"#<Topic2>\" ...\n\n");
    printf("Options:\n");
    printf("  -t <Title>        The title of the task.\n");
    printf("  -d <Description>  A detailed description of the task.\n");
    printf("  #<Topic>          One or more topics for the task (with # before the topic).\n");
    printf("  -i <ID>           The ID of the task (for editing, removing, or completing).\n\n");
    printf("Examples:\n");
    printf("  todo add -t \"Project Preparation\" -d \"Creating the project plan\" \"#Project\" \"#Work\"\n");
    printf("  todo add -t \"Code Review\" -d \"Reviewing the code for errors\" \"#Development\" \"#Team\"\n\n");
    printf("Other commands:\n");
    printf("  todo edit -i <ID> -t \"<New Title>\" -d \"<New Description>\" \"#NewFlag\"\n");
    printf("  todo remove -i <ID>\n");
    printf("  todo finish -i <ID>\n");
    printf("  todo list\n");
    printf("  todo list \"#Flag\"\n");
    exit(EXIT_FAILURE);
}

void CreateFolderIfNotExists(char* foldername)
{
    struct stat st = { 0 };
    if (stat(foldername, &st) == -1) {
        mkdir(foldername, 0700);
    }
}
