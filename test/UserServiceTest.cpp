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

#include "../service/UserService.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
	UserService us;
	User *user = us.findUserById(1);

	cout << user->toString() << endl;

	return EXIT_SUCCESS;
}

