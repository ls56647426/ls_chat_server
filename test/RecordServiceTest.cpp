/*
 * =====================================================================================
 *
 *       Filename:  RecordServiceTest.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/02/2020 06:40:44 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdlib.h>

#include "../service/RecordService.h"
#include <iostream>

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
	RecordService rs;
	User src, dest;
	src.setId(1);
	dest.setId(2);
	list<Record> list = rs.findRecordByUserAndUser(src, dest);

	for(auto it = list.begin(); it != list.end(); it++)
		cout << it->toString() << endl;



	return EXIT_SUCCESS;
}


