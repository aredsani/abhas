#include <vector>
#include <stdio.h>
#include <cstring>
#include <string>
#include <vector>
#include <iostream> 
using namespace std;
#include<objloader.hpp>
#include<shapes.hpp>

bool loadOBJ(const char * path,vector<vertex> & out_vertices,	vector<vertex> & out_uvs,vector<vertex> & out_normals){
	printf("Loading OBJ file %s...\n", path);

	vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	vector<vertex> temp_vertices; 
	vector<vertex> temp_uvs;
	vector<vertex> temp_normals;


	FILE * file = fopen(path, "r");
	if( file == NULL ){
		printf("Unable to open the file!\n");
		return false;
	}

	while( 1 ){

		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break;

		if(strcmp(lineHeader,"v")==0){
			vertex temp;
			//cout<<"yeah"<<endl;
			double a;
			fscanf(file, "%f %f %f\n", &temp.position.x, &temp.position.y, &temp.position.z );
			temp_vertices.push_back(temp);
			//cout<<"This is happning"<<endl;
		}
		else if(strcmp(lineHeader,"vt")==0){
			vertex temp;
			fscanf(file, "%f %f\n", &temp.position.x, &temp.position.y );
			temp.position.z=0;
			temp_uvs.push_back(temp);
		}
		else if ( strcmp( lineHeader, "vn" ) == 0 ){
			vertex temp;
			fscanf(file, "%f %f %f\n", &temp.position.x, &temp.position.y, &temp.position.z );
			temp_normals.push_back(temp);
		}else if ( strcmp( lineHeader, "f" ) == 0 ){
			string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
			if (matches != 9){
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices    .push_back(uvIndex[0]);
			uvIndices    .push_back(uvIndex[1]);
			uvIndices    .push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}else{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	// For each triangle
	for( unsigned int v=0; v<vertexIndices.size(); v+=3 ){
		// For each vertex of the triangle
		for ( unsigned int i=0; i<3; i+=1 ){

			unsigned int vertexIndex = vertexIndices[v+i];
			vertex tempVertex = temp_vertices[ vertexIndex-1 ];
			
			unsigned int uvIndex = uvIndices[v+i];
			vertex tempUV = temp_uvs[ uvIndex-1 ];
			
			unsigned int normalIndex = normalIndices[v+i];
			vertex tempNormal = temp_normals[normalIndex-1];
			
			out_vertices.push_back(tempVertex);
			out_uvs     .push_back(tempUV);
			out_normals .push_back(tempNormal);
		}
	}

	return true;
}
