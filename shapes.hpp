#include<vector>

#ifndef SHAPES
#define SHAPES
//#include<elements.hpp>
using namespace std;
class ply;
class coordinates{
	public:
		float x;
		float y;
		float z;
		coordinates();
		coordinates(float,float,float);
		void set(float X,float Y,float Z);
		coordinates multiply(float multiplier);
		coordinates unitVector();
		coordinates operator+(const coordinates& other);
		coordinates operator-(const coordinates& other);
		coordinates operator*(const coordinates& other);
		void print();
};
class vertex{
	public:
		//float x,y,z;
		coordinates position;
		void setVertex(float a,float b,float c);
		void set(coordinates toSet);
		void move(coordinates change);
		void print();
		void moveVertex(int dir,float change);
		void printVertex();
};
class plane{
	//ax+by+cz+d=0;
	public:
		float a;
		float b;
		float c;
		float d;
		plane();
};
class line{//it is defined in this format http://www.netcomuk.co.uk/~jenolive/vekeq5c.gif
	public:
		float a1,a2,a3,b1,b2,b3;
		void print();
};
class face{
	public:
	unsigned int numberOfVertex;
	vector<unsigned int> index;
	vector<unsigned int> edgesIndex;
	vector<unsigned int> edgesIndexSorted;
	vector<unsigned int> vertexIndexSorted;
	coordinates normalVector;
	float area;
	plane Plane;
	char faceEntity[20];
	//void evaluate_normal(ply* parent);
	//void evaluate_area(ply * parent);
};
class edge{
	public:
	unsigned int index1;
	unsigned int index2;
	void print();
};
#endif
