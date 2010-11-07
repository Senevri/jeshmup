#include "String.h"

#include "SharedData.h"

class StringPrivate{
	StringPrivate& operator=(const StringPrivate &rhs);
public:
	StringPrivate() : m_length(0), m_string(0)
	{}
	StringPrivate(const char *string) : m_length(0), m_string(0)
	{
		copyFrom(string);
	}

	StringPrivate(const StringPrivate &other)
	{
		copyFrom(other.m_string);
	}

private:
	void copyFrom(const char *string)
	{
		if( !string )
		{
			return;
		}

		//maybe this should/can be non-copying....
		m_length = strlen(string) +1;
		m_string = static_cast<char*>(malloc(m_length));
		memcpy(m_string, string, m_length);
	}

public:
	size_t m_length;
	char *m_string;
};

String::String() : m_d(new SharedData<StringPrivate>(new StringPrivate()))
{
}

String::String(const char* string) : m_d(new SharedData<StringPrivate>(new StringPrivate(string)))
{
	
}

String::String(const String& other)
{
	if( this == &other )
	{
		return;
	}
	else
	{
		m_d = other.m_d;
		m_d->ref();
	}
}

String::~String(void)
{

}

std::string String::toStd() const
{
	return std::string(m_d->data()->m_string);
}

void String::detach()
{
	SharedData<StringPrivate> *temp = new SharedData<StringPrivate>(m_d);
	if( m_d->deRef() )
	{
		delete m_d;
	}
	m_d = temp;
}
