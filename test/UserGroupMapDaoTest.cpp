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

#include "../dao/UserGroupMapDao.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
	UserGroupMapDao ugmd;
	UserGroupMap *ugm = ugmd.findOne(1);

	cout << ugm->toString() << endl;

	return EXIT_SUCCESS;
}

