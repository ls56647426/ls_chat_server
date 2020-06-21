/*
 * =====================================================================================
 *
 *       Filename:  usertest.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/19/2020 06:54:55 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdlib.h>

#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

#include "../pojo/User.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
	User *user = new User();
	
	user->setUsername("zhangsan" + to_string(11));
	user->setPassword("123456");
	user->setMobile("12345678910");
	
	cout << user->toString() << endl;

	list<string> l;

	l.push_back("123");
	l.push_back("122");
	l.push_back("121");

	cout << "find" << endl;
	auto it = find(l.begin(), l.end(), "125");

	if(it == l.end())
	{
		cout << "no 125" << endl;
	}

	cout << it->size() << endl;

	return EXIT_SUCCESS;
}

