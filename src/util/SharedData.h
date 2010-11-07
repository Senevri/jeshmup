#ifndef _SHAREDDATA_H_
#define _SHAREDDATA_H_

#include <assert.h>

template<typename T>
class SharedData
{
public:
	SharedData() 
	{

	}

	SharedData(T *data) : m_refCount(0), m_data(data)
	{

	}

	SharedData(SharedData<T> *other) : m_refCount(0), m_data(0)
	{
		copy(*other);
	}

	SharedData(const SharedData<T> &other) : m_refCount(0), m_data(0)
	{
		copy(other);
	}

	virtual ~SharedData(void)
	{
	}

	T* data() const
	{
		return m_data;
	}

	SharedData& operator=(const SharedData &rhs)
	{
		if( *this == &rhs )
		{
			return *this;
		}
		copy(rhs);
	}

	void ref()
	{
		++m_refCount;
	}

	bool deRef()
	{
		--m_refCount;
		if( m_refCount <= 0 )
		{
			delete m_data;
			m_data = 0;
			return true;
		}
		else
		{
			return false;
		}
	}

protected:
	void copy(const SharedData &other)
	{
		assert(m_data == 0 && m_refCount == 0);
		m_data = new T(*other.m_data);
		++m_refCount;
	}

private:
	unsigned int m_refCount;
	T* m_data;
};

#endif //_SHAREDDATA_H_
