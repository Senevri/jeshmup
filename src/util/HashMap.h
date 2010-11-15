#ifndef _HASHMAP_H_
#define _HASHMAP_H_

#include "List.h"

//!@todo Hope there's some fix for this... use own String class....
#include <string>

template<class Key,
		 class Value>
class HashMap
{
	template<class Key, class Value>
	struct HashTableEntry
	{
	public:
		HashTableEntry(Key k, Value v) : key(k), value(v), next(0) {}
		Key key;
		Value value;
		HashTableEntry *next;
	};
	typedef typename HashTableEntry<Key, Value> HashNode;

public:
	static size_t hash(const void *key, int len)
	{
		const unsigned char *p = static_cast<const unsigned char*>(key);
		size_t h = 0;
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

	size_t hashValue(const std::string &value)
	{
		const char* c_string = value.c_str();
		return hash(static_cast<const void*>(c_string), strlen(c_string));
	}
	size_t hashValue(const int i)
	{
		return static_cast<size_t>(i);
	}
			 
public:
	HashMap(void) : m_size(0), m_tableSize(16), m_table(m_tableSize) {fillTable(m_tableSize);}
	HashMap(const int initialSize) : m_size(0), m_tableSize(initialSize), m_table(m_tableSize) {fillTable(m_tableSize);}
	virtual ~HashMap(void) { }

	template<class Key, class Value>
	void insert(const Key &key, const Value &value)
	{
		size_t h = hashValue(key);
		h %= m_tableSize;
		HashNode *toInsertNode = new HashNode(key, value);
		HashNode *node = m_table.at(h);

		if( !node )
		{
			m_table.replace(h, toInsertNode);
			++m_size;
		}
		else
		{
			while( node->next && !(node->key == key) )
			{
				node = node->next;
			}

			if( node->key == key )
			{
				node->value = value;
			}
			else
			{
				node->next = toInsertNode;
				++m_size;
			}
		}
	}

	Value get(const Key &key)
	{
		size_t hash = hashValue(key);
		hash %= m_tableSize;

		HashNode *node = m_table.at(hash);
		while( node )
		{
			if( node && node->key == key )
			{
				return node->value;
			}
			node = node->next;
		}
		return Value();
	}

	size_t size() const
	{
		return m_size;
	}

private:
	void fillTable(int size)
	{
		for( int i = 0; i < size; ++i )
		{
			m_table.append(0);
		}
	}

private:
	size_t m_size;
	size_t m_tableSize;
	BruteList<HashNode*> m_table;
};

#endif // _HASHMAP_H_