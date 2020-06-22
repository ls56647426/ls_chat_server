obj=$(wildcard *.o)
UserDao_obj=UserDaoTest.o User.o UserDao.o ConnectionPool.o ConfigFileReader.o Specification.o
group_obj=GroupTest.o Group.o
friend_obj=FriendTest.o Friend.o
usergroupmap_obj=UsergroupmapTest.o Usergroupmap.o
ConnectionPool_obj=ConnectionPoolTest.o ConnectionPool.o ConfigFileReader.o User.o Specification.o
target=UserDaoTest GroupTest FriendTest UsergroupmapTest ConnectionPoolTest
CFLAGS=-Wall -std=c++11 -lpthread -L/usr/lib64/mysql/ -lmysqlclient
CC=g++

all:$(target)

UserDaoTest:$(UserDao_obj)
	$(CC) $^ -o $@ $(CFLAGS)

GroupTest:$(group_obj)
	$(CC) $^ -o $@ $(CFLAGS)

FriendTest:$(friend_obj)
	$(CC) $^ -o $@ $(CFLAGS)

UsergroupmapTest:$(usergroupmap_obj)
	$(CC) $^ -o $@ $(CFLAGS)

ConnectionPoolTest:$(ConnectionPool_obj)
	$(CC) $^ -o $@ $(CFLAGS)

UserDaoTest.o:UserDaoTest.cpp ../pojo/User.cpp ../pojo/User.h \
	../dao/UserDao.cpp ../dao/UserDao.h
	$(CC) -c $< -o $@ $(CFLAGS)

User.o:../pojo/User.cpp ../pojo/User.h
	$(CC) -c $< -o $@ $(CFLAGS)

UserDao.o:../dao/UserDao.cpp ../dao/UserDao.h \
	../pojo/User.cpp ../pojo/User.h
	$(CC) -c $< -o $@ $(CFLAGS)

GroupTest.o:GroupTest.cpp ../pojo/Group.cpp ../pojo/Group.h
	$(CC) -c $< -o $@ $(CFLAGS)

Group.o:../pojo/Group.cpp ../pojo/Group.h
	$(CC) -c $< -o $@ $(CFLAGS)

FriendTest.o:FriendTest.cpp ../pojo/Friend.cpp ../pojo/Friend.h
	$(CC) -c $< -o $@ $(CFLAGS)

Friend.o:../pojo/Friend.cpp ../pojo/Friend.h
	$(CC) -c $< -o $@ $(CFLAGS)

UsergroupmapTest.o:UsergroupmapTest.cpp ../pojo/Usergroupmap.cpp ../pojo/Usergroupmap.h
	$(CC) -c $< -o $@ $(CFLAGS)

Usergroupmap.o:../pojo/Usergroupmap.cpp ../pojo/Usergroupmap.h
	$(CC) -c $< -o $@ $(CFLAGS)

ConnectionPoolTest.o:ConnectionPoolTest.cpp ../include/ConnectionPool.cpp \
	../include/ConnectionPool.h ../pojo/User.cpp ../pojo/User.h

	$(CC) -c $< -o $@ $(CFLAGS)

ConnectionPool.o:../include/ConnectionPool.cpp ../include/ConnectionPool.h \
	../include/ConfigFileReader.cpp ../include/ConfigFileReader.h \
	../include/Specification.cpp ../include/Specification.h
	$(CC) -c $< -o $@ $(CFLAGS)

ConfigFileReader.o:../include/ConfigFileReader.cpp ../include/ConfigFileReader.h
	$(CC) -c $< -o $@ $(CFLAGS)

Specification.o:../include/Specification.cpp ../include/Specification.h
	$(CC) -c $< -o $@ $(CFLAGS)

.PHONY:clean
clean:
	rm -rf $(target) $(obj)

