#ifndef GROUPSERVICE_H
#define GROUPSERVICE_H

#include "../dao/GroupDao.h"

class GroupService
{
public:
	GroupService();

	/* 通过id查找群 */
	Group *findGroupById(const uint32_t &id);

private:
	GroupDao gd;
};

#endif // GROUPSERVICE_H

