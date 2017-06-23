#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#define HASH_CAPACITY	512

typedef struct hash_node_s
{
	char	key[33];
	void	*val;
	struct hash_node_s *next;
} hashnode_t;

typedef struct hashtable_s
{
	hashnode_t  *tables[HASH_CAPACITY];
} hashtbl_t;

#endif

