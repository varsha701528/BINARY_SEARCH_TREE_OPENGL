/*
	*	program to draw the tree on openGL
	*	Gets the tree root from main.cpp file
	*	Lines between nodes are drawn using Bresenham Line drawing and circular nodes are drawn using midpoint algorithm
*/

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <sstream>
#include <string.h>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <climits>
#include <queue>
#include <math.h>
//#include"bst.h"
using namespace std;

#define RADIUS 10									//radius of circle
#define SCALE 30									//coordinate scaling factor
#define WINDOW 1000									//Size of Window
struct Node *mainroot = NULL;						//root of tree

int flag=0,j=0,m=0,l=0;
void *currentfont;


string to_string(int n){
    string str;
    while(n){
        str.push_back(n%10 + 48);
        n = n/10;
    }
    reverse(str.begin(), str.end());
    return str;
}

void setFont(void *font)
{
    currentfont=font;
}

void drawstring(GLfloat x,GLfloat y,char *string)
{
  char *c;
  //glColor3f(1.0,0.0,1.0);
  glRasterPos2f(x,y);

  for(c=string;*c!='\0';*c++)
  {
    glutBitmapCharacter(currentfont,*c);
  }
}
void Text(float r,float g,float b,string abc,int x, int y)
{glClearColor(0,0,0,0.0);
glColor3f(r,g,b);
	glRasterPos2i(x,y);
    for(int i=0; i<abc.size(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, abc[i]);


    }

glColor3f(1.0,0.0,0.0);

}

void title()
{
    glLineWidth(3.0);
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(10,10);
    glVertex2f(10,590);
    glVertex2f(590,590);
    glVertex2f(590,10);
    glEnd();

    setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0.45,0.5,0.8464);
    drawstring(250,440,"BINARY SEARCH TREE ");
    glColor3f(1.0,0.0,1.0);
    drawstring(250,400,"Submitted by");
    glColor3f(1.0,0.0,0.0);
    drawstring(250,360,"VARSHA M");
    glColor3f(1.0,0.0,0.0);
    drawstring(250,320,"1CR15CS169");
    glColor3f(1.0,0.0,0.0);
    drawstring(250,280,"ASHRIT V");
    glColor3f(1.0,0.0,0.0);
    drawstring(250,240,"1CR15CS166");
    glColor3f(1.0,1.0,1.0);
    drawstring(250,200,"Right Click for options");
glFlush();
}




void Text1(float r,float g,float b,string abc,int x0, int y0)
{glClearColor(0,0,0,0.0);
glColor3f(r,g,b);
y0 = WINDOW/2 - y0 - RADIUS/2;
	x0 = x0 - RADIUS/2;
	glRasterPos2i(x0+10,y0+15);
    for(int i=0; i<abc.size(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, abc[i]);

        //glutBitmapCharacter(GLUT_BITMAP_9_BY_15,a[i]);
    }
	//t<<endl;
glColor3f(1.0,0.0,0.0);

}
//Initialize OpenGL
void init(void){
    glClearColor(0,0,0,0.0);						//set display-window background color to black
    glMatrixMode(GL_PROJECTION);					//set projection parameters
    gluOrtho2D(0.0,600.0,0.0,600.0);
    //glLoadIdentity();
}
void init1(void){
    glClearColor(0,0,0,0.0);						//set display-window background color to black
    glMatrixMode(GL_PROJECTION);					//set projection parameters
    gluOrtho2D(0.0,600.0,0.0,600.0);
    glLoadIdentity();
}

void display1()
{
    glClear(GL_COLOR_BUFFER_BIT);
    title();
}


void display()
{

        glFlush();
}


//PlotPixel at given coordinate
void PlotPixel(GLint x, GLint y){
    y = WINDOW/2 - y;								//moving origin to top-left, default is bottom-left
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    glFlush(); 										//executes all OpenGL functions as quickly as possible
}

//Draw line based on Bresenham Line drawing algorithm
void draw_line(int x0, int y0, int x1, int y1, int dir){
	//dir=1 for left child
	//printf("line:(%d,%d) to (%d,%d)\n", x0, y0, x1, y1);
	int dx=x1-x0, dy=y1-y0;
	int d = 2*dy - dx;
	int incrE=2*dy, incrNE=2*(dy-dx);
	int x=x0, y=y0;
	PlotPixel(x+50, y);

	while(x < x1){
		if(d<=0){								//choose E
			d = d + incrE;
			if(dir) y--;						//if left child decrement y
		}
		else{									//choose NE
			d = d + incrNE;
			if(!dir) y++;
		}
		x++;
		PlotPixel(x+50, y);
	}
}

//plot pixels based on a circle's symmetry
void draw_circle(int x0, int y0, int x, int y){
	PlotPixel(x0+x, y0+y);
	PlotPixel(x0+y, y0+x);
	PlotPixel(x0-y, y0+x);
	PlotPixel(x0-x, y0+y);
	PlotPixel(x0-x, y0-y);
	PlotPixel(x0-y, y0-x);
	PlotPixel(x0+y, y0-x);
	PlotPixel(x0+x, y0-y);
}

//Draw circle using midpoint circle algorithm
void MidpointCircle(int x0, int y0){
	//printf("Circle: (%d, %d)\n", x0, y0);
	int x=0, y=RADIUS;
	int d = 1 - RADIUS;
	int deltaE=3, deltaSE= -2*RADIUS + 5;
	draw_circle(x0+50, y0, x, y);

	while(y > x){
		if(d<0){								//select E
			d = d + deltaE;
			deltaE = deltaE+2;
			deltaSE += 2;
		}
		else{									//select SE
			d = d + deltaSE;
			deltaE += 2;
			deltaSE += 4;
			y--;
		}
		x++;
		draw_circle(x0+50, y0, x, y);
	}
}

//function to convert integer to string

void drawText1(int data, int x0, int y0){
    glColor3f(0.8,0.0,0.5);                                         //change data color to green
	GLvoid *font_style = GLUT_BITMAP_HELVETICA_12;
	y0 = WINDOW/2 - y0 - RADIUS/2;
	x0 = x0 - RADIUS/2;                                             //bring str to center of circle
	string str = to_string(data);
	glRasterPos2f(x0+50, y0);
	for(int i=0; i<str.size(); i++){
        glutBitmapCharacter(font_style, str[i]);

	}

    glColor3f(1.0,0.0,0.0);											//change drawing color back to red
}


//Write the data inside the drawn node
void drawText(int data, int x0, int y0){
    glColor3f(0.0,1.0,0.0);                                         //change data color to green
	GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_24;
	y0 = WINDOW/2 - y0 - RADIUS/2;
	x0 = x0 - RADIUS/2;                                             //bring str to center of circle
	string str = to_string(data);
	glRasterPos2f(x0+50, y0);
	for(int i=0; i<str.size(); i++){
        glutBitmapCharacter(font_style, str[i]);


	}

    glColor3f(1.0,0.0,0.0);											//change drawing color back to red
}

//Function to remove part of line that lies inside node's circle
pair<pair<int, int>, pair<int, int> > removeRad(float x0, float y0, float x1, float y1){
	float delx=x1-x0, dely=y1-y0;
	float mod = sqrt(delx*delx + dely*dely);
	delx = delx/mod * RADIUS;
	dely = dely/mod * RADIUS;

	x0 = x0 + delx;
    x1 = x1 - delx;
	y0 = y0 + dely;
	y1 = y1 - dely;
	return make_pair(make_pair(x0,y0), make_pair(x1,y1));
}


void raster1(int x,int y,int i)
{
    string s,str;
    s=to_string(i);

    glColor3f(0.956,0.99,0.008);
    drawstring(260,240,"IN-ORDER ");
    glColor3f(0.056,0.4099,0.908);
    j+=20;
    glRasterPos2f(x+j,y);
    for(int k=0; k<s.size(); k++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[k]);


	}

}

void raster2(int x,int y,int i)
{
    string s,str;
    s=to_string(i);

    glColor3f(0.956,0.99,0.008);
    drawstring(260,240,"PRE-ORDER ");
    glColor3f(0.056,0.4099,0.908);
    l+=20;
    glRasterPos2f(x+l,y);
    for(int k=0; k<s.size(); k++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[k]);


	}

}

void raster3(int x,int y,int i)
{
    string s,str;
    s=to_string(i);


    m+=20;
    glColor3f(0.956,0.99,0.008);
    drawstring(260,240,"POST-ORDER ");
    glColor3f(0.056,0.409,0.908);
    glRasterPos2f(x+m,y);
    for(int k=0; k<s.size(); k++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[k]);


	}

}


//Inorder traversal of tree
void inorder(struct Node *root){
	//Inorder traversal of tree

	if(root == NULL) return;

	inorder(root->left);
	raster1(200,200,root->data);
	inorder(root->right);

}

void preorder(struct Node *root){
	//Pre traversal of tree

	if(root == NULL) return;
    raster2(200,200,root->data);
	preorder(root->left);

	preorder(root->right);

}

void postorder(struct Node *root){
	//Postorder traversal of tree

	if(root == NULL) return;

	postorder(root->left);

	postorder(root->right);
    raster3(200,200,root->data);
}

//Function to process the tree and call appropriate line and circle drawing functions at appropriate coordinates
void draw(){

string abc;

    j=0,m=0,l=0;
	glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);
    glPointSize(2.0);

    struct Node *root = mainroot, *current;
    queue<struct Node*> Q;
    pair<pair<int, int>, pair<int, int> > p;
    Q.push(root);int i=1;
    int x0, y0, x1, y1;
    if(flag==3)
    {
        preorder(root);
    }
    if(flag==2)
    {
        inorder(root);
    }

    if(flag==4)
    {
        postorder(root);
    }
    while(!Q.empty()){							//BFS of tree
    	root = Q.front();
    	Q.pop();
    	x0 = SCALE*(root->x + 1);
    	y0 = SCALE*(root->y + 1);
    	Text1(0.06,0.9,0.64,"Node:",x0+55,y0+5);
        drawText1(i,x0+25,y0);

    	MidpointCircle(x0, y0);					//draw circle
    	drawText(root->data, x0, y0);



        i++;

                            //draw node value
    	if(root->left){							//if left exists
    		current = root->left;
    		Q.push(current);
    		x1 = SCALE*(current->x + 1);
    		y1 = SCALE*(current->y + 1);

    		p = removeRad(x0, y0, x1, y1);
    		int x02 = p.first.first;
    		int y02 = p.first.second;
    		x1 = p.second.first;
    		y1 = p.second.second;

    		draw_line(x1, y1, x02, y02, 1);

    	}


    	if(root->right){						//if right exists
    		current = root->right;
    		Q.push(current);
    		x1 = SCALE*(current->x + 1);
    		y1 = SCALE*(current->y + 1);

    		p = removeRad(x0, y0, x1, y1);
    		int x02 = p.first.first;
    		int y02 = p.first.second;
    		x1 = p.second.first;
    		y1 = p.second.second;

    		draw_line(x02, y02, x1, y1, 0);


    	}
        drawstring(400,540,"Right Click For more Options ");
    }


    PlotPixel(WINDOW, WINDOW);

}

void scan_menu(int id){

if(id==1){glutDisplayFunc(draw);}
else if(id==2){flag=2;}
else if(id==3){flag=3;}
else if(id==4){flag=4;}
else if(id==5){glutDisplayFunc(display1);}
else{exit(0);}
	glutPostRedisplay();
}




void draw_main(struct Node *root, int height, int argc, char *argv[]){
	mainroot = root;

    glutInit(&argc,argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);										//initialize display mode
    glutInitWindowSize(WINDOW, WINDOW);
    glutInitWindowPosition(50,50);														//Position of top-left corner
    glutCreateWindow("BST");

	glutDisplayFunc(display1);


    glutCreateMenu(scan_menu);

    glutAddMenuEntry("Tree",1);
    glutAddMenuEntry("In-order",2);
    glutAddMenuEntry("Pre-order",3);
    glutAddMenuEntry("Post-order",4);
    glutAddMenuEntry("Back",5);
    glutAddMenuEntry("Quit",6);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

    init();
    glutMainLoop();

}
