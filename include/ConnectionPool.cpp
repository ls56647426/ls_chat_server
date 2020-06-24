#include "ConnectionPool.h"
#include "ConfigFileReader.h"

/* c lib */
#include <stdlib.h>

/* c++ lib */
#include <iostream>
#include <algorithm>
using namespace std;

/* unix lib */
#include <unistd.h>
#include <pthread.h>

mutex ConnectionPool::mymutex;
condition_variable ConnectionPool::cv;
ConnectionPool* ConnectionPool::instance = NULL;

/* 构造函数 */
ConnectionPool::ConnectionPool()
{
	/* 从ini配置文件中读取配置信息 */
	CConfigFileReader config("../config/connection_pool.conf");

	/* 获取数据库配置信息 */
	hostName = config.getConfigName("hostName");
	port = atoi(config.getConfigName("port"));
	databaseName = config.getConfigName("databaseName");
	username = config.getConfigName("username");
	password = config.getConfigName("password");

	/* 获取连接池配置信息 */
	testOnBorrow = atoi(config.getConfigName("testOnBorrow"));
	maxWaitTime = atoi(config.getConfigName("maxWaitTime"));
	waitInterval = atoi(config.getConfigName("waitInterval"));
	maxConnectionCount = atoi(config.getConfigName("maxConnectionCount"));
	isSQL = atoi(config.getConfigName("isSQL"));

	testOnBorrowSQL = "select 1";
}

/* 析构函数 */
ConnectionPool::~ConnectionPool()
{
	/* 销毁连接池的时候 关闭 并 删除 所有的连接 */
	for(MYSQL *connection : usedConnections)
	{
		mysql_close(connection);
		delete connection;
	}

	for(MYSQL *connection : unusedConnections)
	{
		mysql_close(connection);
		delete connection;
	}
}

/* 获取数据库连接 */
MYSQL *ConnectionPool::getConnection()
{
	ConnectionPool& pool = ConnectionPool::getInstance();
	MYSQL *connection;

	unique_lock<mutex> lock(mymutex);

	/* 已创建连接数 */
	int connectionCount = pool.unusedConnections.size() + pool.usedConnections.size();

	/* 如果连接已经用完，等待 waitInterval 毫秒看看是否有可用连接，最长等待 maxWaitTime 毫秒 */
	for (int i = 0; i < pool.maxWaitTime && pool.unusedConnections.size() == 0 &&
		 connectionCount == pool.maxConnectionCount; i += pool.waitInterval)
	{
		cv.wait_for(lock, std::chrono::milliseconds(pool.waitInterval));

		/* 重新计算已创建连接数 */
		connectionCount = pool.unusedConnections.size() + pool.usedConnections.size();
	}

	if (pool.unusedConnections.size() > 0)
	{	/* 有已经回收的连接，复用它们 */
		connection = pool.unusedConnections.front();
		pool.unusedConnections.pop_front();
	}
	else if (connectionCount < pool.maxConnectionCount)
	{	/* 没有已经回收的连接，但是没有达到最大连接数，则创建新的连接 */
		connection = pool.createConnection();
	}
	else
	{	/* 已经达到最大连接数 */
		cout << "Cannot create more connections." << endl;
		return nullptr;
	}

	/* 有效的连接才放入 usedConnections */
	pool.usedConnections.push_back(connection);

	return connection;
}

/* 释放数据库连接回连接池 */
void ConnectionPool::releaseConnection(MYSQL *connection)
{
	ConnectionPool& pool = ConnectionPool::getInstance();

	/* 如果是我们创建的连接，从 used 里删除，放入 unused 里 */
	if (find(pool.usedConnections.begin(), pool.usedConnections.end(),
				connection) != pool.usedConnections.end())
	{
		unique_lock<mutex> lock(mymutex);

		remove(pool.usedConnections.begin(),
				pool.usedConnections.end(), connection);
		pool.unusedConnections.push_back(connection);
	}
}

/* 关闭所有的数据库连接 */
void ConnectionPool::destoryConnectionPool()
{
	unique_lock<mutex> lock(mymutex);
	delete instance;
	instance = NULL;
}

/* select语句 */
MYSQL_RES *ConnectionPool::runOne(const string &content)
{
	//输出sql语句
	ConnectionPool& pool = ConnectionPool::getInstance();
	if(pool.isSQL)
		cout << "sql:" << content << endl;

	//打开数据库
	MYSQL *conn = ConnectionPool::getConnection();

	//执行sql语句
	if(mysql_query(conn, content.c_str()))
	{
		cout << "mysql_query error:" << mysql_error(conn) << endl;
		ConnectionPool::releaseConnection(conn);
		exit(EOF);
	}

	//获取查询结果
	MYSQL_RES* rec = mysql_store_result(conn);
	int rows = mysql_num_rows(rec);
	if(!rows)
	{
		cout << "MYSQL_RES 没有查询到结果.\n";
		ConnectionPool::releaseConnection(conn);
		return nullptr;
	}
	else
	{
		ConnectionPool::releaseConnection(conn);
		return rec;
	}
}

/* insert into语句和update语句 */
void ConnectionPool::runNo(const string &content)
{
	//输出sql语句
	ConnectionPool& pool = ConnectionPool::getInstance();
	if(pool.isSQL)
		cout << "sql:" << content << endl;

	//打开数据库
	MYSQL *conn = ConnectionPool::getConnection();

	//执行sql语句
	if(mysql_query(conn, content.c_str()))
	{
		cout << "mysql_query error:" << mysql_error(conn);
		ConnectionPool::releaseConnection(conn);
		exit(EOF);
	}

	ConnectionPool::releaseConnection(conn);
}

/* 单例模式：获取数据库连接池对象 */
ConnectionPool &ConnectionPool::getInstance()
{
	/*
	 * 这里判断NULL用了互斥锁，还可以直接：
	 * static ConnectionPooL g_instance;
	 * return g_instance;
	 * 具体是否有什么区别，暂时不知道
	 */
	if (!instance)
	{
		unique_lock<mutex> lock(mymutex);
		if (!instance)
			instance = new ConnectionPool();
	}

	return *instance;
}

/* 创建数据库连接 */
MYSQL *ConnectionPool::createConnection()
{
	/* 创建一个新的连接 */
	MYSQL *conn = mysql_init(NULL);

	if(!conn)
	{
		cout << "can not connect to mysql server:" << mysql_error(conn) << endl;
		exit(1);
	}

	if(!mysql_real_connect(conn, hostName.c_str(), username.c_str(), password.c_str(),
			databaseName.c_str(), port, NULL, CLIENT_MULTI_STATEMENTS | CLIENT_FOUND_ROWS))
	{
		cout << "mysql_real_connect error:" << mysql_error(conn) << endl;
		exit(1);
	}

	return conn;
}

