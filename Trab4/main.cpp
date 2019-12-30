#include <GL/glut.h>
#include <stdio.h>
#include "config.h"
#include "graphics.h"
void inicialize(){
	config.win = 0;
	config.arena.player.movement.tetaCannonG = 0;
	config.arena.player.movement.tetaCannonR = 0;
	config.arena.player.movement.tetaWheelsG = 0;
	config.arena.player.movement.tetaWheelsR = 0;
	config.arena.player.movement.increment = 0;
	config.arena.player.movement.tetaCarG = 0;
	config.arena.player.movement.tetaCarR = 0;
	config.arena.player.movement.mouse = 0;
	config.arena.player.movement.checkpoint = -1;
	config.arena.player.movement.increment = 0;
	config.enemyConf.nShots = 0;
	for(std::vector<Player>::iterator it = config.arena.enemies.begin(); it != config.arena.enemies.end(); it++){
		(*it).movement.tetaCannonG = 0;
		(*it).movement.tetaCannonR = 0;
		(*it).movement.tetaWheelsG = 0;
		(*it).movement.tetaWheelsR = 0;
		(*it).movement.increment = 0;
		(*it).movement.tetaCarG = 0;
		(*it).movement.tetaCarR = 0;
		(*it).movement.mouse = 0;
		(*it).movement.checkpoint = -1;
		(*it).movement.increment = 0;
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
	inicialize();
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (config.window.width,config.window.height);
	glutInitWindowPosition (350,200);
	glutCreateWindow("Trabalho Curto 4");
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
