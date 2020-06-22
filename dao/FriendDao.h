#ifndef FRIENDDAO_H
#define FRIENDDAO_H

/* c++ lib */
#include <list>

#include "../pojo/Friend.h"
#include "../include/Specification.h"
#include "../include/ConnectionPool.h"

class FriendDao
{
public:
	FriendDao();

	/* 查找 */
	Friend* findOne(const uint32_t &id);
	Friend* findOne(const Specification &spec);

	list<Friend> findAll(const Specification &spec);

	/* 保存 */
	void save(const Friend *_friend);

	/* 删除 */
	void del(const uint32_t &id);

private:
	/* 单条记录缓存，key:"id"，value:"Friend" */
//	static QCache<string, Friend> friendCache;
	/* 缓存多条记录，key:"方法名+参数"，value：friend列表 */
//	static QCache<string, list<Friend>> friendsCache;
};

#endif // FRIENDDAO_H
