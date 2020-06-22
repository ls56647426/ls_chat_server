obj=$(wildcard *.o)
UserDao_obj=UserDaoTest.o User.o UserDao.o ConnectionPool.o ConfigFileReader.o Specification.o
GroupDao_obj=GroupDaoTest.o Group.o GroupDao.o ConnectionPool.o ConfigFileReader.o Specification.o
FriendDao_obj=FriendDaoTest.o Friend.o FriendDao.o ConnectionPool.o ConfigFileReader.o Specification.o
usergroupmap_obj=UsergroupmapTest.o Usergroupmap.o
ConnectionPool_obj=ConnectionPoolTest.o ConnectionPool.o ConfigFileReader.o User.o Specification.o
target=UserDaoTest GroupDaoTest FriendDaoTest UsergroupmapTest ConnectionPoolTest
CFLAGS=-Wall -std=c++11 -lpthread -L/usr/lib64/mysql/ -lmysqlclient
CC=g++

all:$(target)

UserDaoTest:$(UserDao_obj)
	$(CC) $^ -o $@ $(CFLAGS)

GroupDaoTest:$(GroupDao_obj)
	$(CC) $^ -o $@ $(CFLAGS)

FriendDaoTest:$(FriendDao_obj)
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

GroupDaoTest.o:GroupDaoTest.cpp ../pojo/Group.cpp ../pojo/Group.h \
	../dao/GroupDao.cpp ../dao/GroupDao.h
	$(CC) -c $< -o $@ $(CFLAGS)

Group.o:../pojo/Group.cpp ../pojo/Group.h
	$(CC) -c $< -o $@ $(CFLAGS)

GroupDao.o:../dao/GroupDao.cpp ../dao/GroupDao.h \
	../pojo/Group.cpp ../pojo/Group.h
	$(CC) -c $< -o $@ $(CFLAGS)

FriendDaoTest.o:FriendDaoTest.cpp ../pojo/Friend.cpp ../pojo/Friend.h \
	../dao/FriendDao.cpp ../dao/FriendDao.h
	$(CC) -c $< -o $@ $(CFLAGS)

Friend.o:../pojo/Friend.cpp ../pojo/Friend.h
	$(CC) -c $< -o $@ $(CFLAGS)

FriendDao.o:../dao/FriendDao.cpp ../dao/FriendDao.h \
	../pojo/Friend.cpp ../pojo/Friend.h
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

