#ifndef UTILS_H
#define UTILS_H

#include "cJSON.h"
#include <stdbool.h>

void ThrowError(const char* message);
char* GetPath(char* foldername, char* filename);
char* GenerateId(int length);
void PrintJsonObject(cJSON* obj);
void PrintJsonArray(cJSON* jsonArray);
void PrintHelp();
void CreateFolderIfNotExists(char* foldername);

#endif
