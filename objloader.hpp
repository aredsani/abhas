#include <vector>
#include <stdio.h>
#include <cstring>
#include <string>
#include <vector>
#include <iostream> 
using namespace std;
//#include<objloader.hpp>
#include <shapes.hpp>

#ifndef OBJLOADER_H
#define OBJLOADER_H

bool loadOBJ(const char * path,vector<vertex> & out_vertices,	vector<vertex> & out_uvs,vector<vertex> & out_normals);

#endif
