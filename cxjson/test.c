#include <stdio.h>
#include <string.h>
#include "cxJson.h"

int main()
{
	Json_t	*json = Json_ParseFile("data.json");
	if(!json)
	{
		fprintf(stderr, "fail to Json_ParseFile: %s\n", Json_GetError());
		return 0;
	}
printf("json getfile\n");
	Json_t *c1 = cJSON_GetObjectItem(json, "services");
	printf("type: %d, string: %s\n", c1->type, c1->string);
	
	Json_t *c2 = cJSON_GetObjectItem(c1, "100001");
	printf("type: %d, string: %s\n", c2->type, c2->string);

	Json_t *c3 = cJSON_GetObjectItem(c2, "flow");
	printf("type: %d, string: %s\n", c3->type, c3->string);
	printf("size: %d\n", cJSON_GetArraySize(c3));

	Json_t *c4 = cJSON_GetArrayItem(c3, 0);
	printf("type: %d, string: %s, value:%s\n", c4->type, c4->string, c4->valuestring);
/*
	Json_t *c5 = cJSON_GetObjectItem(json, "conn");
	printf("type: %d, string: %s, value:%s\n", c5->type, c5->string, c5->valuestring);
*/	

	int  ret;
	Json_t *c6 = NULL;
	printf("c2: %s\n", c2->string);
	ret = Json_GetArray(c2, "flow", &c6);
	if(ret)
	{
		printf("get json object fail\n");
		return -1;
	}

	if(c6 == NULL)
	{
		printf("c6 is null\n");
	}
	printf("c6: %s, %d\n", c6->string, c6->type);	

	int i=0;
	Json_t *t = NULL;
	char	val[100];
	for(; Json_JsonArrayIter(c6, &i, &t) != 1; )
	{
		test(t);
	}

	Json_t *c7 = Json_Create();
	if(!c7) return -1;

	test_json_create(c7);

	return 0;
}

int test(Json_t *t)
{
	char	val[100];

	 memset(val, 0, sizeof(val));
     Json_GetString(t, "trade", val, 100);
     printf("get trade: %s\n", val);
     memset(val, 0, sizeof(val));
     Json_GetString(t, "conf", val, 100);
     printf("get conf: %s\n", val);
	return 0;
}

int test_json_create(Json_t *json)
{
	Json_SetString(json, "server", "XoEx");
	Json_SetString(json, "version", "1.0.1");
	Json_SetJsonString(json, "config", "home", "/home/etc");
	Json_SetJsonString(json, "config", "file", "/test.ini");

	printf("%s\n", cJSON_Print(json));
	return 0;
}

