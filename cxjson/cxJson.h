#ifndef _CX_JSON_H
#define _CX_JSON_H

#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

typedef cJSON	Json_t;

Json_t *Json_Create(void);

Json_t *Json_Parse(char *jbuffer);

Json_t *Json_ParseFile(char *filename);

void Json_Destroy(Json_t **json);

int Json_GetString(Json_t *json, char *key, char *val, int size);

int Json_GetLong(Json_t *json, char *key, int *val);

int Json_GetDouble(Json_t *json, char *key, double *val);

int Json_GetJson(Json_t *json, char *key, Json_t **val);

int Json_GetJsonString(Json_t *json, char *tag, char *key, char *val, int size);

int Json_GetJsonJson(Json_t *json, char *tag, char *key, Json_t **value);

int Json_GetArray(Json_t *json, char *key, Json_t **value);

int Json_GetJsonArray(Json_t *json, char *tag, char *key, Json_t **value);

int Json_StringArrayIter(Json_t *json, int *set, char *value, int valuesize);

int Json_JsonArrayIter(Json_t *json, int *set, Json_t **value);


#endif /* _CX_JSON_H */

