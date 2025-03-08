#ifndef UTILS_H
#define UTILS_H

#include "cJSON.h"

void ThrowError(const char* message);
char* GenerateId(int length);
void PrintJsonObject(cJSON* obj);
void PrintJsonArray(cJSON* jsonArray);

#endif
