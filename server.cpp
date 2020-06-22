/*
 * =====================================================================================
 *
 *       Filename:  server.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/19/2020 11:27:31 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

/* c std lib */
#include <stdlib.h>

/* c++ lib */
#include <iostream>

/* third-party lib */
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/event.h>

#include "server.h"
#include "include/Msg.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
	Msg msg;

	cout << msg.toString() << endl;

	return EXIT_SUCCESS;
}

