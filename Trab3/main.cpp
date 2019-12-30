#include <GL/glut.h>
#include <stdio.h>
#include "config.h"
#include "graphics.h"

int main(int argc, char **argv){
	using namespace std;
	movement.tetaCannonG = 0;
	movement.tetaCannonR = 0;
	movement.tetaWheelsG = 0;
	movement.tetaWheelsR = 0;
	movement.increment = 0;
	movement.tetaCarG = 0;
	movement.tetaCarR = 0;
	movement.mouse = 0;
	for(int i=0;i<256;i++)
		keyStatus[i]=false;
	Configuration config2(argv[1]);
	config = config2;
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (config.window.width,config.window.height);
	glutInitWindowPosition (350,200);
	glutCreateWindow("Trabalho Curto 3");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyPress);
	glutKeyboardUpFunc(keyUp);
	glutIdleFunc(idle);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMovement);
	glutPassiveMotionFunc(mouseMovement);
	glutMainLoop();
	return 0;
}
