#ifndef _HASHMAP_H_
#define _HASHMAP_H_

#include "List.h"

template<class Key,
		 class Value>
class HashMap
{
	template<class Key, class Value>
	struct HashTableEntry
	{
		Key key;
		Value value;
		LinkedList<HashTableEntry*> overflowTable;
	};

public:
	static unsigned int hash(void *key, int len)
	{
		unsigned char *p = key;
		unsigned h = 0;
		int i;
		
		for( i = 0; i < len; i++ )
		{
			h += p[i];
			h += ( h << 10 );
			h ^= ( h >> 6 );
		}
		 
		h += ( h << 3 );
		h ^= ( h >> 11 );
		h += ( h << 15 );
		
		return h;
	}
			 
public:
	HashMap(void) : m_size(16) {}
	HashMap(const int initialSize) : m_size(initialSize) {}
	virtual ~HashMap(void);

	template<class Key, class Value>
	void insert(Key key, Value value);

private:
	size_t m_size;
	//List<LinkedList> m_table;
};

#endif // _HASHMAP_H_