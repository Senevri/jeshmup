#ifndef _STRING_H
#define _STRING_H

#include <string>

class StringPrivate;
template<typename T> class SharedData;

class String
{
public:
	String();
	String(const char* charArray);
	String(const String& other);
	virtual ~String(void);

	std::string toStd() const;

private:
	void detach();

private:
	SharedData<StringPrivate> *m_d;
};

#endif //_STRING_H