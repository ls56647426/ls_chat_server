#ifndef FRIEND_H
#define FRIEND_H

/* c lib */
#include <stdio.h>
#include <stdint.h>

/* c++ lib */
#include <string>
using namespace std;

class Friend
{
public:
	Friend();

	uint32_t getId() const;
	void setId(const uint32_t &value);

	uint32_t getSuid() const;
	void setSuid(const uint32_t &value);

	uint32_t getDuid() const;
	void setDuid(const uint32_t &value);

	string getDate() const;
	void setDate(const string &value);

	uint32_t getPermission() const;
	void setPermission(const uint32_t &value);

	string toString() const;

private:
	uint32_t id;
	uint32_t suid;
	uint32_t duid;
	string date;
	uint32_t permission;
};

#endif // FRIEND_H
