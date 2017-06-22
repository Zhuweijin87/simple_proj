/***********************************
 * HASH 容器
 **********************************/

static int hashcode(char *str, int size)
{

}

static void *strmemdup(void *val, size_t size)
{
	void *data = malloc(size);
	memcpy(data, val, size);

	return data;
}

hashnode_t *hashnode_create(char *key, void *val, size_t size)
{
	hashnode_t *node = malloc(sizeof(hashnode_t));
	
	strcpy(node->key, key);
	node->val = strmemdup(val, size);

	return node;
}


int hash_add(hashtbl *htbl, char *key, char *val)
{
	;
}



