#include <boost/thread.hpp>
#include <boost/date_time.hpp>

#include <GL/gl.h>
#include <GL/glut.h>
#include <vector>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <maya.hpp> 
#include <stdio.h>
#include <math.h>
#include <iterator>

using namespace std;
extern "C"
 {
    #include <pthread.h>
    #include <unistd.h>
 }
GLuint texture;
double angle = 0;
typedef struct{
	int X;
	int Y;
    int Z;
    double U;
    double V;
}VERTICES;
int argc1;
char **argv1;
const double PI = 3.1415926535897;
const int space = 10;
const int VertexCount = (90 / space) * (360 / space) * 4;
VERTICES VERTEX[VertexCount];
GLuint LoadTextureRAW( const char * filename );



void DisplaySphere (double R, GLuint texture)
{

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    int b;
    glScalef (0.0125 * R, 0.0125 * R, 0.0125 * R);
    glRotatef (-90, 1, 0, 0);
   glBindTexture (GL_TEXTURE_2D, texture);
    glBegin (GL_TRIANGLE_STRIP);
    for ( b = 0; b <VertexCount; b++)
    {
        glTexCoord2f (VERTEX[b].U, VERTEX[b].V);
        glVertex3f (VERTEX[b].X, VERTEX[b].Y, -VERTEX[b].Z);
    }



for ( b = 0; b <VertexCount; b++)
{

    glTexCoord2f (VERTEX[b].U, -VERTEX[b].V);

    glVertex3f (VERTEX[b].X, VERTEX[b].Y, VERTEX[b].Z);

}

    glEnd();
}
void CreateSphere (double R, double H, double K, double Z) {
    int n;
    double a;
    double b;
    n = 0;
for( b = 0; b <= 90 - space; b+=space){

    for( a = 0; a <= 360 - space; a+=space)
    {
        VERTEX[n].X = R * sin((a) / 180 * PI) * sin((b) / 180 * PI) - H;
        VERTEX[n].Y = R * cos((a) / 180 * PI) * sin((b) / 180 * PI) + K;
        VERTEX[n].Z = R * cos((b) / 180 * PI) - Z;
        VERTEX[n].V = (2 * b) / 360;
        VERTEX[n].U = (a) / 360;

        n++;
        VERTEX[n].X = R * sin((a) / 180 * PI) * sin((b + space) / 180 * PI) - H;
        VERTEX[n].Y = R * cos((a) / 180 * PI) * sin((b + space) / 180 * PI) + K;
        VERTEX[n].Z = R * cos((b + space) / 180 * PI) - Z;
        VERTEX[n].V = (2 * (b + space)) / 360;
        VERTEX[n].U = (a) / 360;
        n++;
        VERTEX[n].X = R * sin((a + space) / 180 * PI) * sin((b) / 180 * PI) - H;
        VERTEX[n].Y = R * cos((a + space) / 180 * PI) * sin((b) / 180 * PI) + K;
        VERTEX[n].Z = R * cos((b) / 180 * PI) - Z;
        VERTEX[n].V = (2 * b) / 360;
        VERTEX[n].U = (a + space) / 360;
        n++;
        VERTEX[n].X = R * sin((a + space) / 180 * PI) * sin((b + space) /180 * PI) - H;
        VERTEX[n].Y = R * cos((a + space) / 180 * PI) * sin((b + space) /180 * PI) + K;
        VERTEX[n].Z = R * cos((b + space) / 180 * PI) - Z;
        VERTEX[n].V = (2 * (b + space)) / 360;
        VERTEX[n].U = (a + space) / 360;
        n++;
    }

}
}
void display (void) {
	
    glClearDepth(1);
    glClearColor (0.0,0.0,0.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f,0.0f,-10.0f);
    glRotatef(angle,0,1,0);
    DisplaySphere(1, texture);
    glutSwapBuffers();
    angle +=0.015f;
}
void init (void) {
    glEnable(GL_DEPTH_TEST);
    glEnable( GL_TEXTURE_2D );

    glDepthFunc(GL_LEQUAL);

    texture= LoadTextureRAW( "earth.bmp" );

    
}
void reshape (int w, int h) {

    glViewport (0, 0, (GLsizei)w, (GLsizei)h);

    glMatrixMode (GL_PROJECTION);

    glLoadIdentity ();

    gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 100.0);

    glMatrixMode (GL_MODELVIEW);
}
void workerFunc(){
	boost::posix_time::seconds workTime(3);
	std::cout << "Worker: running" << std::endl;
    // Pretend to do something useful...
	boost::this_thread::sleep(workTime);
	std::cout << "Worker: finished" << std::endl;
}
void *junky(void * argument){
	glutInit (&argc1, argv1);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("A basic OpenGL Window");
    init();
    CreateSphere(300,0,0,0);
	glutDisplayFunc (display);
	glutIdleFunc (display);
	glutReshapeFunc (reshape);
	glutMainLoop ();
	return 0;
}
void  * function1(void * argument);
void  * function2(void * argument);
int main (int argc,char **argv){
	argc1=argc;
	argv1=argv;
	/*glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("A basic OpenGL Window");
    init();
    CreateSphere(300,0,0,0);
    
    glutDisplayFunc (display);
    //glutIdleFunc (display);
    glutReshapeFunc (reshape);
    glutMainLoop ();

    std::cout << "main: startup" << std::endl;
	boost::thread workerThread(gestureREC),workerThread2(junky);
    

    std::cout << "main: waiting for thread" << std::endl;
	workerThread2.join();
    workerThread.join();
    

    std::cout << "main: done" << std::endl;*/
    pthread_t t1, t2 ; // declare 2 threads.
    pthread_create( &t1, NULL, junky,NULL); // create a thread running function1
    pthread_create( &t2, NULL, gestureREC,NULL); // create a thread running function2

    // Because all created threads are terminated when main() finishes, we have
    // to give the threads some time to finish. Unfortunately for function1, main()
    // will give only 1 second, but function1 needs at least 2 seconds. So function1 will
    // probably be terminated before it can finish. This is a BAD way to manage threads.
    sleep(1000);
    



    
    return 0;
}

void * function1(void * argument)
{
    cout << " hello " << endl ;
    sleep(2); // fall alseep here for 2 seconds...
    return 0;
}

void * function2(void * argument)
{
    cout << " world "  << endl ;
    return 0;
}
GLuint LoadTextureRAW( const char * filename ){
	GLuint texture;
	int width, height;
	unsigned char * data;
	FILE * file;



  file = fopen( filename, "rb" );

  if ( file == NULL ) return 0;



  width = 3200;

  height = 1600;

  data = (unsigned char *)malloc( width * height * 3 );


    //int size = fseek(file,);
  fread( data, width * height * 3, 1, file );

  fclose( file );

for(int i = 0; i < width * height ; ++i){
    int index = i*3;
    unsigned char B,R;
    B = data[index];
    R = data[index+2];
    //B = data[index];
    data[index] = R;
    data[index+2] = B;
}


    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );


    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
    free( data );

return texture;
}
