#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <cstring>
#include <assert.h>

template<typename T>
class BruteList
{
public:

    BruteList() : m_data(0), m_size(0)
    {
    }

    ~BruteList()
    {
        delete[] m_data;
    }

    void append(const T& item)
    {
        //T *data = static_cast<T*>(malloc((m_size + 1) * sizeof(T)));
        T *newData = new T[(m_size +1) * sizeof(T)];
        assert(newData);
        if( m_size > 0)
        {
            for(int i = 0; i < m_size; i++)
            {
                newData[i] = m_data[i];
            }
            delete[] m_data;
        }
        m_data = newData;
        m_data[m_size] = item;
        ++m_size;
    }

    const T& at(int index) const
    {
        assert(index >= 0 && index < m_size);
        return m_data[index];
    }

    int size() const
    {
        return m_size;
    }


private:
    T *m_data;
    int m_size;
};

template<typename T>
struct Bucket
{
    Bucket(int size) : m_filled(0), m_size(size)
    {
        assert(size > 0);
        m_data = malloc(size * sizeof(T));
    }

    ~Bucket()
    {
        free(m_data);
    }

    Bucket* add(T item)
    {
        Bucket *newBucket = 0;
        if( m_filled < m_size)
        {
            m_data[m_filled] = item;
            ++m_filled;
        }
        else
        {
            newBucket = new Bucket(m_size);
            newBucket->add(item);
        }
        return newBucket;
    }

    const T& getItem(int index)
    {
        assert(index >= 0 && index < m_filled);
        return m_data[index];
    }

    void removeItem()
    {
        if( m_filled >= 0)
        {
            --m_filled;
        }
    }

private:
    unsigned int m_filled;
    int m_size;
    T m_data[];
};

template<typename T>
class List
{
public:
    List();
    virtual ~List();

    void append(T item);
    T at(int index);
    void insert(int index, T item);
    void removeAt(int index);

private:
    void* m_data;
    unsigned int m_dataSize;
    unsigned int m_used;
};

template<typename T>
List<T>::List()
    :
    m_data(0),
    m_dataSize(0),
    m_used(0)
{
    m_data = malloc(10 * sizeof(T));
    assert(m_data);
    m_dataSize = 10;
}

template<typename T>
List<T>::~List()
{
    free(m_data);
}

template<typename T>
void List<T>::append(T item)
{

}


template <class T>
class LinkedList{

	struct ListNode{
		ListNode() : next(0) {}
		T item;
		ListNode *next;
	};

public:
	LinkedList() : m_first(0), m_last(0) {}
	~LinkedList()
	{
		ListNode *temp = m_first;
		while( temp )
		{
			ListNode *node = temp->next;
			delete temp;
			temp = node;
		}
	}

	T at(const unsigned int index) const
	{
		ListNode *node = findIndex(index);
		if( node )
		{
			return node->item;
		}
		else
		{
			return T();
		}
	}

	unsigned int size() const
	{
		ListNode *temp = m_first;
		unsigned int i = 0;
		while( temp )
		{
			temp = temp->next;
			++i;
		}
		return i;
	}

	void append(T item)
	{
		ListNode *toAdd = new ListNode();
		toAdd->item = item;
		if( !m_last )
		{
			m_last = m_first = toAdd;
		}
		else
		{
			m_last->next = toAdd;
			m_last = toAdd;
		}
	}

	void remove(const unsigned int index)
	{
		ListNode *temp = m_first;
		if( index == 0 )
		{
			m_first = temp->next;
			delete temp;
		}
		else
		{
			temp = findIndex(index -1);
			if( temp )
			{
				ListNode *toRemove = temp->next;
				temp->next = toRemove->next;
				delete toRemove;
			}
		}
	}

private:
	ListNode* findIndex(const unsigned int index) const
	{
		ListNode *temp = m_first;
		unsigned int i = 0;
		for( ; i < index && temp; ++i)
		{
			temp = temp->next;
		}
		return temp;
	}

private:
	ListNode *m_first;
	ListNode *m_last;
};

#endif // LIST_H
