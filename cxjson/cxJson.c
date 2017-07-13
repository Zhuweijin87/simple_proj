/***********************************
 * 基于cJSON.c API 重新封装json API
 * *********************************/
#include <string.h>
#include "cxJson.h"
#include <errno.h>

static char error[100] = {'\0'};

static void _SetError(char *err)
{
	memset(error, 0, sizeof(error));
	strcpy(error, err);
}

char *Json_GetError()
{
	return error;
}

/* filename 为绝对路径 */
static char *read_file(char *filename)
{
    char    *temp = NULL;
    FILE    *fp = NULL;
    int     fsize;

    fp = fopen(filename, "r");
    if(!fp)
	{
		_SetError(strerror(errno));
        return NULL;
	}

    fseek(fp, 0, SEEK_END);

	fsize = ftell(fp);
	
    temp = malloc((fsize + 1) * sizeof(char));

	fseek(fp, 0, SEEK_SET);

    fread(temp, 1, fsize, fp); 

	fclose(fp);

    return temp;
}

Json_t *Json_Create(void)
{
	return (Json_t *)cJSON_CreateObject();
}

Json_t *Json_Parse(char *jbuffer)
{
	return (Json_t *)cJSON_Parse(jbuffer);
}

Json_t *Json_ParseFile(char *filename)
{
	char *jbuffer = (char *)read_file(filename);
	if(jbuffer == NULL)
		return NULL;

    Json_t *json = Json_Parse(jbuffer);
	if(json == NULL)
	{
		_SetError("Json String Validate fail");
		return NULL;
	}
	free(jbuffer);
	jbuffer = NULL;
	return json;
}

void Json_Destroy(Json_t **json)
{
	free(*json);
	*json = NULL;
}

int Json_CvtString(Json_t *json, char *jbuffer, size_t size)
{
	;
}

char *Json_Print(Json_t *json)
{
	return cJSON_Print(json);	
}

static Json_t *_GetJsonObject(Json_t *json, char *key, int type)
{
	if(json == NULL)
	{
		_SetError("Null Json Object");
		return NULL;
	}

	Json_t *c = cJSON_GetObjectItem(json, key);
	if(c == NULL)
	{
		_SetError("Not Found Json Object");
		return NULL;
	}

	if(c->type != type)
	{
		_SetError("Type Not Match");
		return NULL;
	}

	return c;
}

static int _Json_GetValue(Json_t *json, char *key, void *val, int size, int type)
{
	Json_t *t = _GetJsonObject(json, key, type);
	if(!t)		return -1;

	if(type == cJSON_Number)
	{
		if(size == sizeof(int))
			memcpy(val, (void *)&t->valueint, size);
		if(size == sizeof(double))
			memcpy(val, (void *)&t->valuedouble, size);
	}

	if(type == cJSON_String)
	{
		size = size > strlen(t->valuestring) ? size : strlen(t->valuestring);
		memcpy(val, t->valuestring, size);
	}

	return 0;
}

int Json_GetString(Json_t *json, char *key, char *val, int size)
{
	return _Json_GetValue(json, key, val, size, cJSON_String);
}

int Json_GetLong(Json_t *json, char *key, int *val)
{
	return _Json_GetValue(json, key, val, sizeof(int), cJSON_Number);
}

int Json_GetDouble(Json_t *json, char *key, double *val)
{
	return _Json_GetValue(json, key, val, sizeof(double), cJSON_Number);
}

int Json_GetJson(Json_t *json, char *key, Json_t **val)
{
	return (*val = _GetJsonObject(json, key, cJSON_Object)) == NULL ? -1 : 0;
}

int Json_GetJsonString(Json_t *json, char *tag, char *key, char *val, int size)
{
	Json_t *t = _GetJsonObject(json, tag, cJSON_Object);
	return Json_GetString(t, key, val, size);
}

int Json_GetJsonLong(Json_t *json, char *tag, char *key, int *val)
{
	Json_t *t = _GetJsonObject(json, tag, cJSON_Object);
	return Json_GetLong(json, key, val);
}

int Json_GetJsonJson(Json_t *json, char *tag, char *key, Json_t **val)
{
	Json_t *t = _GetJsonObject(json, tag, cJSON_Object);
	return Json_GetJson(t, key, val);
}

int Json_GetArray(Json_t *json, char *key, Json_t **val)
{
	return (*val = _GetJsonObject(json, key, cJSON_Array)) == NULL ? -1 : 0;
}

int Json_GetJsonArray(Json_t *json, char *tag, char *key, Json_t **value)
{
	Json_t *t = _GetJsonObject(json, tag, cJSON_Object);
	return Json_GetArray(t, key, value);
}

static Json_t *_Json_ArrayIter(Json_t *json, int *set, int objtype)
{
	if(!json)
	{
		_SetError("Null Json");
		return NULL;
	}

	if(json->type != cJSON_Array)
	{
		_SetError("Json Type Not Match");
		return NULL;
	}

	if(*set > cJSON_GetArraySize(json))				
		return NULL;

	Json_t *obj = cJSON_GetArrayItem(json, *set);
	if(obj->type != objtype)
	{
		_SetError("Json Type Not Match");
		return NULL;
	}

	*set = *set + 1;

	return obj;
}

int Json_StringArrayIter(Json_t *json, int *set, char *value, int valuesize)
{
	if(*set = cJSON_GetArraySize(json))
		return 1;
	Json_t *t = _Json_ArrayIter(json, set, cJSON_String);
	valuesize = valuesize > strlen(t->valuestring) ? strlen(t->valuestring) : valuesize;
	strncpy(value, t->valuestring, valuesize);
	return 0;
}

int Json_JsonArrayIter(Json_t *json, int *set, Json_t **value)
{
	if(*set == cJSON_GetArraySize(json))
		return 1;
	return (*value = _Json_ArrayIter(json, set, cJSON_Object)) == NULL ? -1 : 0;
}

/* setter */
static int _Json_AddValue(Json_t *json, char *key, void *value, int type)
{
	if(json == NULL)
	{
		_SetError("Null Json Object");
		return -1;
	}

	if(type == cJSON_String)
		cJSON_AddStringToObject(json, key, value);
	if(type == cJSON_Number)
		cJSON_AddNumberToObject(json, key, *(int *)value);
	if(type == cJSON_Number)
		cJSON_AddNumberToObject(json, key, *(double *)value);
	return 0;
}

int Json_SetString(Json_t *json, char *key, char *value)
{
	return _Json_AddValue(json, key, value, cJSON_String);
}

int Json_SetInteger(Json_t *json, char *key, int value)
{
	return _Json_AddValue(json, key, &value, cJSON_Number);
}

int Json_FSetString(Json_t *json, char *key, char *value)
{
	Json_t *t = _GetJsonObject(json, key, cJSON_String);
	if(t)
	{
		t->valuestring = cJSON_StrReplace(t, value);
		return 0;
	}
	return Json_SetString(json, key, value);
}

int Json_SetJsonString(Json_t *json, char *tag, char *key, char *value)
{
	Json_t *t = _GetJsonObject(json, tag, cJSON_Object);
	if(!t)
	{
		t = cJSON_CreateObject();
		cJSON_AddItemToObject(json, tag, t);	
	}
	return Json_SetString(t, key, value);
}

int Json_SetStringArray(Json_t *json, char *key, ...)
{
	return 0;
}

