#ifndef USERGROUPMAPDAO_H
#define USERGROUPMAPDAO_H

/* c++ lib */
#include <list>
#include <string>

#include "../pojo/UserGroupMap.h"
#include "../include/Specification.h"
#include "../include/ConnectionPool.h"

class UserGroupMapDao
{
public:
	UserGroupMapDao();

	/* 查找 */
	UserGroupMap* findOne(const uint32_t &id);
	UserGroupMap* findOne(const Specification &spec);

	list<UserGroupMap> findAll(const Specification &spec);

	/* 保存 */
	void save(const UserGroupMap *userGroupMap);

	/* 删除 */
	void del(const uint32_t &id);

private:
	/* 单条记录缓存，key:"id"，value:"UserGroupMap" */
//	static QCache<string, UserGroupMap> userGroupMapCache;
	/* 缓存多条记录，key:"方法名+参数"，value：userGroupMap列表 */
//	static QCache<string, list<UserGroupMap>> userGroupMapsCache;
};

#endif // USERGROUPMAPDAO_H
