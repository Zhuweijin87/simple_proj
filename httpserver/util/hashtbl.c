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

static hashnode_t *hashnode_create(char *key, void *val, size_t size)
{
	hashnode_t *node = malloc(sizeof(hashnode_t));
	
	strcpy(node->key, key);
	node->val = strmemdup(val, size);

	return node;
}

static hashnode_t *hashnode_get(hashtbl_t *htbl, char *key)
{
	int 		hkey = 0;
	hashnode_t	*temp = NULL;

	hkey = hashcode(key, strlen(key));
	temp = htbl->tables[hkey % HASH_CAPACITY];
	while(temp != NULL)
	{
		if(strcmp(temp->key, key) == 0)
			return temp;
		temp = temp->next;
	}	
	return NULL;
}

hashtbl_t *hashtbl_new()
{
	hashtbl_t *htbl = malloc(sizeof(hashtbl_t));
	return htbl;	
}

static int hash_set_node(hashtbl *htbl, char *key, void *val, size_t size)
{
	int			hkey = 0;
	hashnode_t *node = NULL;

	node = hashnode_get(htbl, key);
	if(node)
	{
		return 1;
	}

	hkey = hashcode(key, strlen(key));
	node = hash_node_create(key, val, size);
	if(node == NULL)
		return -1;

	temp = htbl->tables[hkey % HASH_CAPACITY]
	while(temp)
	{
		if(temp->next == NULL)
		{
			temp->next = node;
			break;
		}
		temp = temp->next
	}
	
	return 0;
}

static int hash_get_node(hashtbl_t *htbl, char *key, void *val, size_t size)
{
	int         hkey = 0;
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



