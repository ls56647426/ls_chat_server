/*
 * =====================================================================================
 *
 *       Filename:  usergrouptest.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/19/2020 09:33:41 PM
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
using namespace std;

#include "../pojo/Usergroupmap.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
	UserGroupMap *ugm = new UserGroupMap();

	ugm->setUid(1);
	ugm->setGid(2);

	cout << ugm->toString() << endl;

	return EXIT_SUCCESS;
}

