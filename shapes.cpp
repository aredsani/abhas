
#include<iostream>
//#include<utils.hpp>
#include<shapes.hpp>
//#include<elements.hpp>
#include<math.h>
using namespace std;

/*void vertex::setVertex(float a,float b,float c){
	x=a;
	y=b;
	z=c;
}
*/
// dir 1=x,2=y,3=z

/*void vertex::moveVertex(int dir,float change){
	if(dir==1){
		x+=change;
	}
	else if(dir==2){
		y+=change;
	}
	else if(dir==3){
		z+=change;
	}
}*/
plane::plane(){
	a=0;
	b=0;
	c=0;
	d=0;
}
coordinates::coordinates(){
	x=0;
	y=0;
	z=0;
}
coordinates::coordinates(float X,float Y,float Z){
	x=X;
	y=Y;
	z=Z;
}
void coordinates::set(float X,float Y,float Z){
	x=X;
	y=Y;
	z=Z;
}
coordinates coordinates::multiply(float multiplier){
	coordinates temp(x,y,z);
	temp.x*=multiplier;
	temp.y*=multiplier;
	temp.z*=multiplier;
	return temp;
}
coordinates coordinates::operator+(const coordinates& other){
    coordinates temp = *this;
    temp.x+=other.x;
    temp.y+=other.y;
    temp.z+=other.z;
    return temp;
}
coordinates coordinates::operator-(const coordinates& other){
    coordinates temp = *this;
    temp.x-=other.x;
    temp.y-=other.y;
    temp.z-=other.z;
    return temp;
}
coordinates coordinates::operator*(const coordinates& other){
	coordinates temp = *this;
	coordinates out;
	out.x = (temp.y*other.z) - (temp.z*other.y);
	out.y = (temp.z*other.x) - (temp.x*other.z);
	out.z = (temp.x*other.y) - (temp.y*other.x);
	return out;
}
/*coordinates coordinates::unitVector(){
	coordinates temp(x,y,z);
	float modulus=mod(temp);
	temp=temp.multiply((1.0/modulus));
	return temp;
}*/
void coordinates::print(){
	cout<<x<<" "<<y<<" "<<z<<endl;	
}
void vertex::move(coordinates change){
	position.x+=change.x;
	position.y+=change.y;
	position.z+=change.z;
}
void vertex::set(coordinates toSet){
	position.x=toSet.x;
	position.y=toSet.y;
	position.z=toSet.z;
}
void vertex::print(){
	cout<<position.x<<" "<<position.y<<" "<<position.z<<endl;	
}
/*void vertex::printVertex(){
	cout<<x<<" "<<y<<" "<<z<<endl;
}
*/
/*void face::evaluate_normal(ply* parent){
	//currently taking the first 3 vertexs of the face and finding its normal the algo needs to be improved
	if(numberOfVertex<3){
		cout<<"this face has less than 3 vertexes :O"<<endl;
	}
	else{
		normalVector=((parent->edges[vertexIndexSorted[1]].position-parent->edges[vertexIndexSorted[2]].position)*(parent->edges[vertexIndexSorted[0]].position-parent->edges[vertexIndexSorted[1]].position)).unitVector();
		normalVector=normalVector.unitVector();//might be a overkill as might be i am getting a unit vector already :P do check if needed
		Plane=find_plane(parent->edges[vertexIndexSorted[0]].position,parent->edges[vertexIndexSorted[1]].position,parent->edges[vertexIndexSorted[2]].position);
	}
}*/
void line::print(){
	cout<<"x - "<<a1<<" = y - "<<a2<<" = z - "<<a3<<endl<<"      "<<b1<<"	"<<b2<<"	"<<b3<<endl;
}
/*void face::evaluate_area(ply* parent){
	coordinates baseVertex(0,0,0);
	for(unsigned int i=0; i<numberOfVertex;i++){
		baseVertex = baseVertex + parent->edges[index[i]].position;
	}
	baseVertex= baseVertex.multiply(1.0/numberOfVertex);
	coordinates areaVector(0,0,0);
	for(unsigned int j=0;j<numberOfVertex;j++){
		areaVector=areaVector + (parent->edges[vertexIndexSorted[j]].position-baseVertex)*(parent->edges[vertexIndexSorted[(j+1)%numberOfVertex]].position-parent->edges[vertexIndexSorted[j]].position); 
	}
	//need to define += operator overload too 
	areaVector = areaVector.multiply(0.5);
	float Final_area = mod(areaVector);
	area = Final_area;
}*/
void edge::print(){
	cout<<index1<<" "<<index2<<endl;
}

