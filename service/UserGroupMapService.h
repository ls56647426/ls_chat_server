#ifndef USERGROUPMAPSERVICE_H
#define USERGROUPMAPSERVICE_H

#include "../dao/UserGroupMapDao.h"

class UserGroupMapService
{
public:
	UserGroupMapService();

	/* 查询某用户所在的所有群 */
	list<UserGroupMap> findAllByUser(const User &user);

private:
	UserGroupMapDao ugmd;
};

#endif // USERGROUPMAPSERVICE_H

