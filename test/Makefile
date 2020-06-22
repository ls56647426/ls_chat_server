obj=$(wildcard *.o)
ConnectionPool_lib=ConnectionPool.o ConfigFileReader.o Specification.o
UserService_obj=UserServiceTest.o User.o UserDao.o UserService.o $(ConnectionPool_lib)
GroupService_obj=GroupServiceTest.o Group.o GroupDao.o GroupService.o $(ConnectionPool_lib)
FriendDao_obj=FriendDaoTest.o Friend.o FriendDao.o $(ConnectionPool_lib)
UserGroupMapDao_obj=UserGroupMapDaoTest.o UserGroupMap.o UserGroupMapDao.o $(ConnectionPool_lib)
ConnectionPool_obj=ConnectionPoolTest.o $(ConnectionPool_lib)
target=UserServiceTest GroupServiceTest FriendDaoTest UserGroupMapDaoTest ConnectionPoolTest
CFLAGS=-Wall -std=c++11 -lpthread -L/usr/lib64/mysql/ -lmysqlclient
CC=g++

all:$(target)

UserServiceTest:$(UserService_obj)
	$(CC) $^ -o $@ $(CFLAGS)

GroupServiceTest:$(GroupService_obj)
	$(CC) $^ -o $@ $(CFLAGS)

FriendDaoTest:$(FriendDao_obj)
	$(CC) $^ -o $@ $(CFLAGS)

UserGroupMapDaoTest:$(UserGroupMapDao_obj)
	$(CC) $^ -o $@ $(CFLAGS)

ConnectionPoolTest:$(ConnectionPool_obj)
	$(CC) $^ -o $@ $(CFLAGS)

UserServiceTest.o:UserServiceTest.cpp ../pojo/User.cpp ../pojo/User.h \
	../dao/UserDao.cpp ../dao/UserDao.h \
	../service/UserService.cpp ../service/UserService.h
	$(CC) -c $< -o $@ $(CFLAGS)

User.o:../pojo/User.cpp ../pojo/User.h
	$(CC) -c $< -o $@ $(CFLAGS)

UserDao.o:../dao/UserDao.cpp ../dao/UserDao.h \
	../pojo/User.cpp ../pojo/User.h
	$(CC) -c $< -o $@ $(CFLAGS)

UserService.o:../service/UserService.cpp ../service/UserService.h \
	../dao/UserDao.cpp ../dao/UserDao.h \
	../pojo/User.cpp ../pojo/User.h
	$(CC) -c $< -o $@ $(CFLAGS)

GroupServiceTest.o:GroupServiceTest.cpp ../pojo/Group.cpp ../pojo/Group.h \
	../dao/GroupDao.cpp ../dao/GroupDao.h \
	../service/GroupService.cpp ../service/GroupService.h
	$(CC) -c $< -o $@ $(CFLAGS)

Group.o:../pojo/Group.cpp ../pojo/Group.h
	$(CC) -c $< -o $@ $(CFLAGS)

GroupDao.o:../dao/GroupDao.cpp ../dao/GroupDao.h \
	../pojo/Group.cpp ../pojo/Group.h
	$(CC) -c $< -o $@ $(CFLAGS)

GroupService.o:../service/GroupService.cpp ../service/GroupService.h \
	../dao/GroupDao.cpp ../dao/GroupDao.h \
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

UserGroupMapDaoTest.o:UserGroupMapDaoTest.cpp ../pojo/UserGroupMap.cpp ../pojo/UserGroupMap.h \
	../dao/UserGroupMapDao.cpp ../dao/UserGroupMapDao.h
	$(CC) -c $< -o $@ $(CFLAGS)

UserGroupMap.o:../pojo/UserGroupMap.cpp ../pojo/UserGroupMap.h
	$(CC) -c $< -o $@ $(CFLAGS)

UserGroupMapDao.o:../dao/UserGroupMapDao.cpp ../dao/UserGroupMapDao.h \
	../pojo/UserGroupMap.cpp ../pojo/UserGroupMap.h
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

