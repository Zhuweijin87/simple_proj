/***********************************
 * HASH 容器
 **********************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "hashtbl.h"

static int hashcode(char *str, int size)
{
	unsigned int hash = 5381;
	unsigned int i    = 0;

	for(i = 0; i < size; str++, i++)
	{
		hash = ((hash << 5) + hash) + (*str);
	}

	return hash;
}

static int hash_index(char *str, int size, int capacity)
{
	int 	hashval = hashcode(str, strlen(str));
	return hashval % capacity;
}

static void *strmemdup(void *val, size_t size)
{
	void *data = malloc(size);
	memcpy(data, val, size);
	return data;
}

static hashnode_t *hashnode_create(char *key, void *val, size_t size)
{
	hashnode_t *node = malloc(sizeof(hashnode_t));
	
	strcpy(node->key, key);
	node->val = strmemdup(val, size);

	return node;
}

hashtbl_t *hashtbl_new()
{
	int i;
	hashtbl_t *htbl = malloc(sizeof(hashtbl_t));
	for(i=0; i<HASH_CAPACITY; i++)
		htbl->tables[i] = NULL;
	return htbl;	
}

static hashnode_t *hashnode_get(hashtbl_t *htbl, char *key)
{
	int 		index = 0;
	hashnode_t	*temp = NULL;

	index = hash_index(key, strlen(key), HASH_CAPACITY);
	temp = htbl->tables[index];
	while(temp != NULL)
	{
		if(strcmp(temp->key, key) == 0)
		{
			return temp;
		}
		temp = temp->next;
	}
	
	return NULL;
}

static int hash_set_node(hashtbl_t *htbl, char *key, void *val, size_t size)
{
	int			hindex = 0;
	hashnode_t *node = NULL, *temp = NULL;

	node = hashnode_get(htbl, key);
	if(node)
	{
		printf("%s does exist\n", key);
		return 1;
	}

	hindex = hash_index(key, strlen(key), HASH_CAPACITY);
	node = hashnode_create(key, val, size);
	if(node == NULL)
		return -1;

	if(htbl->tables[hindex] == NULL)
	{
		htbl->tables[hindex] = node;
	}
	else
	{
		node->next = htbl->tables[hindex];
		htbl->tables[hindex] = node;
	}
	
	printf("key: %s, val: %s\n", htbl->tables[hindex]->key, htbl->tables[hindex]->val);

	return 0;
}

static int hash_get_node(hashtbl_t *htbl, char *key, void *val, size_t size)
{
    hashnode_t *node = NULL;

	node = hashnode_get(htbl, key);
    if(!node)
    {
        return -1;
    }

	memcpy(val, node->val, size);

	return 0;
}

int hash_setstring(hashtbl_t *htbl, char *key, char *val)
{
	return hash_set_node(htbl, key, val, strlen(val));
}

int hash_setlong(hashtbl_t *htbl, char *key, int val)
{
	return hash_set_node(htbl, key, &val, sizeof(int));
}

int hash_getstring(hashtbl_t *htbl, char *key, char *val, int size)
{
	return hash_get_node(htbl, key, val, size);
}

int hash_getlong(hashtbl_t *htbl, char *key, long *val)
{
	return hash_get_node(htbl, key, val, sizeof(long));
}



