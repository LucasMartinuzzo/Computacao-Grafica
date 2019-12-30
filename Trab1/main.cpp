#include <GL/glut.h>
#include <stdio.h>
#include "config.h"
#include "graphics.h"

int main(int argc, char **argv){
	using namespace std;
	for(int i=0;i<256;i++)
		keyStatus[i]=false;
	moviment.squareStatus = false;
	moviment.leftButtonDown = false;
	Configuration config2(argv[1]);
	config = config2;
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (config.getWindow().width,config.getWindow().height);
	glutInitWindowPosition (100,100);
	glutCreateWindow(config.getWindow().title);
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyPress);
	glutKeyboardUpFunc(keyUp);
	glutIdleFunc(idle);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMoviment);
	glutPassiveMotionFunc(mouseMoviment);
	glutMainLoop();
	return 0;
}
