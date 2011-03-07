#ifndef __HASHED_STRING_H__
#define __HASHED_STRING_H__

#define LOG_MESSAGES

#include <iostream>
#include <map>

class HashedString
{
public:
    HashedString(const std::string& string);
	HashedString(const char * string);

	unsigned long getHash() const { return mHash; }
	std::string getString() const { return mString; }

#ifdef LOG_MESSAGES
	static std::string reverse(unsigned long val);
#endif

private:
	std::string mString;
	unsigned long mHash;

	static unsigned long hash(const char *string);

#ifdef LOG_MESSAGES
	static std::map<unsigned long, std::string> ReverseMappings;
    void fillReverseMappings();
#endif
};

#endif // __HASHED_STRING_H__
