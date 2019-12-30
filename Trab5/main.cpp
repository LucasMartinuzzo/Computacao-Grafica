#include <GL/glut.h>
#include <stdio.h>
#include "config.h"
#include "graphics.h"
#include "glutFunctions.h"
#include <math.h>

void initialize(){
	config.win = 0;
    config.cam = 3;
	config.nightMode = false;
	config.killAll = false;
	config.arena.player.movement.tetaCannonXG = 0;
	config.arena.player.movement.tetaCannonXR = 0;
	config.arena.player.movement.tetaCannonZG = 0;
	config.arena.player.movement.tetaCannonZR = 0;
	config.arena.player.movement.tetaWheelsG = 0;
	config.arena.player.movement.tetaWheelsR = 0;
	config.arena.player.movement.increment = 0;
	config.arena.player.movement.tetaCarG = 0;
	config.arena.player.movement.tetaCarR = 0;
	config.arena.player.movement.mouseX = 0;
	config.arena.player.movement.mouseY = 0;
	config.arena.player.movement.checkpoint = false;
	config.enemyConf.nShots = 0;
	config.arena.player.movement.tetaCamXG = 0;
	config.arena.player.movement.tetaCamXR = 0;
	config.arena.player.movement.tetaCamZG = 45;
	config.arena.player.movement.tetaCamZR = M_PI*45/180;
	config.arena.player.movement.camX = 0;
	config.arena.player.movement.camY = 0;
	config.arena.player.movement.rightButtonDown = false;
	for(std::vector<Player>::iterator it = config.arena.enemies.begin(); it != config.arena.enemies.end(); it++){
		(*it).movement.tetaCannonXG = 0;
		(*it).movement.tetaCannonXR = 0;
		(*it).movement.tetaWheelsG = 0;
		(*it).movement.tetaWheelsR = 0;
		(*it).movement.increment = 0;
		(*it).movement.tetaCarG = 0;
		(*it).movement.tetaCarR = 0;
		(*it).movement.mouseX = 0;
		(*it).movement.checkpoint = -1;
	}
	chrono.seconds = 0;
	chrono.init = 0;
	chrono.hasStarted = false;
}

int main(int argc, char **argv){
	using namespace std;
	for(int i=0;i<256;i++)
		keyStatus[i]=false;
	Configuration config2(argv[1]);
	config = config2;
	srand ((unsigned)time(0));
	initialize();
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (500,700);
	glutInitWindowPosition (350,200);
	glutCreateWindow("Trabalho Final");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyPress);
	glutKeyboardUpFunc(keyUp);
	glutIdleFunc(idle);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMovement);
	glutPassiveMotionFunc(mousePassiveMovement);
	glutMainLoop();
	return 0;
}
