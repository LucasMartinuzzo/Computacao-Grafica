#include <GL/glut.h>
#include <stdio.h>
#include "config.h"
#include "graphics.h"

int main(int argc, char **argv){
	/*Não utilizadas neste trabalho, guardar para os próximos
	moviment.squareStatus = false;
	moviment.leftButtonDown = false;
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMoviment);
	glutPassiveMotionFunc(mouseMoviment);
	*/
	using namespace std;
	for(int i=0;i<256;i++)
		keyStatus[i]=false;
	Configuration config2(argv[1]);
	config = config2;
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (config.window.width,config.window.height);
	glutInitWindowPosition (100,100);
	glutCreateWindow("Trabalho Curto 2");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyPress);
	glutKeyboardUpFunc(keyUp);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}
