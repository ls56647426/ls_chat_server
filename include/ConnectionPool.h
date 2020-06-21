#ifndef MYSQLCONNECTIONPOOL_H
#define MYSQLCONNECTIONPOOL_H

/* c lib */
#include <stdint.h>

/* c++ lib */
#include <string>
#include <list>
#include <mutex>
#include <condition_variable>
using namespace std;

/* mysql lib */
#include <mysql/mysql.h>

/*
 * 数据库连接池类（单例模式）
 * 单例模式：确保一个类只有一个实例，该类自己进行实例化，并且向整个系统提供这个实例
 */
class ConnectionPool
{
public:
	/* 构造函数 */
	ConnectionPool();
	/* 析构函数 */
	~ConnectionPool();

	/* 获取数据库连接 */
	static MYSQL *getConnection();
	/* 释放数据库连接回连接池 */
	static void releaseConnection(MYSQL *connection);
	/* 关闭所有的数据库连接 */
	static void destoryConnectionPool();

	/* select语句 */
	static MYSQL_RES* runOne(const string &content);
	/* insert into语句和update语句 */
	static void runNo(const string &content);

private:
	/* 创建数据库连接 */
	MYSQL* createConnection();

private:
	/* 数据库信息 */
	string databaseType;		//数据库类型
	string hostName;			//主机地址
	uint32_t port;				//端口号
	string databaseName;		//数据库名称
	string username;			//访问账户
	string password;			//访问密码

	/* 连接池配置信息 */
	bool testOnBorrow;			//从连接池获取一个连接时，取出是否检测
	string testOnBorrowSQL;		//取出检测的SQL语句
	int maxWaitTime;			//获取连接最大等待时间
	int waitInterval;			//尝试获取连接时等待间隔时间
	int maxConnectionCount;		//最大连接数
	bool isSQL;					//是否输出sql语句

	list<MYSQL *> usedConnections;		//已使用的数据库连接名
	list<MYSQL *> unusedConnections;	//未使用的数据库连接名

	/* 多线程互斥 */
	static mutex mymutex;
	static condition_variable cv;
	/* 唯一一个实例 */
	static ConnectionPool *instance;

	/* 单例模式：获取数据库连接池对象 */
	static ConnectionPool& getInstance();
};

#endif // MYSQLCONNECTIONPOOL_H
