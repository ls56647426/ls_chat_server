#ifndef GROUPDAO_H
#define GROUPDAO_H

/* c++ lib */
#include <list>

#include "../pojo/Group.h"
#include "../include/Specification.h"
#include "../include/ConnectionPool.h"

class GroupDao
{
public:
	GroupDao();

	/* 查找 */
	Group* findOne(const uint32_t &id);
	Group* findOne(const Specification &spec);

	list<Group> findAll(const Specification &spec);

	/* 保存 */
	void save(const Group *group);

	/* 删除 */
	void del(const uint32_t &id);

private:
	/* 单条记录缓存，key:"id"，value:"Group" */
//	static QCache<string, Group> groupCache;
	/* 缓存多条记录，key:"方法名+参数"，value：group列表 */
//	static QCache<string, list<Group>> groupsCache;
};

#endif // GROUPDAO_H
