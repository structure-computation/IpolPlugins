
/*
 *  parser.h
 *  
 *
 *  Created by Antoni Buades 2012.
 *
 * Copyright 2012 IPOL Image Processing On Line http://www.ipol.im/
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */







#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <cmath>
#include <cassert>
#include <vector>
#include <getopt.h>





//
//! Parser
//
typedef struct optstruct
{	
	char *gp;
    int flag;
    char *defvalue;
    char *value;
    char *comment;
    
} OptStruct;



typedef struct parstruct
{
    char * name;
    char * value;
    char * comment;
} ParStruct;



int parsecmdline(char *pname,
                 char *function,
                 int argc, char **argv,
                 std::vector <OptStruct*> & opt,
                 std::vector <ParStruct*> & par);


