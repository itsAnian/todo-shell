#include "cJSON.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

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
