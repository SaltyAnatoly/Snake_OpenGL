#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "field.h"
#include "snake.h"
#include "visual.h"
#include <windows.h>
#include "mmsystem.h"
#include <glut.h>
#include <fstream>

bool pause = 0;

bool isHighscore = 0;

gameCondition status = NORMAL;

int escPressed = 0;

int soundDelay = 3;

field myField;

snake mySnake;

visual vis;

void checkHighscore()
{
	std::fstream highscore;

	highscore.open("highscore.hsc", std::ios::in);

	int highscoreValue;

	highscore >> highscoreValue;

	if (highscoreValue < mySnake.points || !highscore)
	{
		highscore.close();
		highscore.open("highscore.hsc", std::ios::out);
		highscore << mySnake.points;
		highscore.close();
		isHighscore = 1;
	}
}

void updateField()
{
	for (int i = 0; i < myField.fieldLength; i++)
		for (int j = 0; j < myField.fieldWidth; j++)
			if (myField._field[i][j] != cell::FOOD && myField._field[i][j] != cell::WALL)
				myField._field[i][j] = cell::BLANK;

	for (int s = 0; s < mySnake.snakeLength; s++)
		myField._field[mySnake._snake[s].iCurrentPosition][mySnake._snake[s].jCurrentPosition] = cell::SNAKE;
	myField._field[mySnake._snake[0].iCurrentPosition][mySnake._snake[0].jCurrentPosition] = cell::SNAKE_HEAD;

	if (mySnake.snakeLength > 1)
		myField._field[mySnake._snake[mySnake.snakeLength - 1].iCurrentPosition][mySnake._snake[mySnake.snakeLength - 1].jCurrentPosition] = cell::SNAKE_TALE;
}

void display()
{
	glutReshapeWindow(myField.fieldWidth*vis.Scale, myField.fieldLength*vis.Scale);

	vis.gameOpenGLOut(mySnake, myField);

	vis.overlayScreen(mySnake, status, isHighscore);
}

void processNormalKeys(unsigned char key, int x, int y)
{
	if (key == 27)
	{
		escPressed++;
		checkHighscore();
		status = gameCondition::GAMEOVER;
		if (pause || mySnake.dead)
		{
			exit(0);
		}	
		pause = true;
	}
	if (key == ' ' && !mySnake.dead && escPressed != 1)
	{
		checkHighscore();
		pause = !pause;
		status = (gameCondition)pause;
	}		
}

void KeyboardEvent(int caughtKey, int a, int b)
{
	if (!pause)
		mySnake.catchKeyButton(caughtKey);
}

void Tick()
{
	mySnake.snakeMoving(myField);

	if (soundDelay == 3)
	{
		PlaySound(L"sound.wav", NULL, SND_ASYNC | SND_FILENAME);
		soundDelay = 0;
	}
	else soundDelay++;

	if (mySnake.isSnakeEatTheFood)
	{
		myField.spawnFood();
		PlaySound(L"sound2.wav", NULL, SND_ASYNC | SND_FILENAME);
		mySnake.isSnakeEatTheFood = 0;
	}

	if (mySnake.dead)
	{
		checkHighscore();
		status = gameCondition::DEATH;
		mciSendString(L"play gameover.mp3", NULL, 0, NULL);
	}
}

void timer(int = 0)
{
	if (!pause && !mySnake.dead)
	{
		Tick();			
	}

	updateField();
	
	if(mySnake.dead)
	{
		mySnake.killNode();
	}

	display();
	
	glutTimerFunc(70, timer, 0);
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(myField.fieldWidth*vis.Scale, myField.fieldLength*vis.Scale);
	glutCreateWindow("Snake");
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, myField.fieldWidth*vis.Scale, 0, myField.fieldLength*vis.Scale);

	myField.spawnFood();
	display();

	glutDisplayFunc(display);
	glutSpecialFunc(KeyboardEvent);
	glutKeyboardFunc(processNormalKeys);
	glutTimerFunc(70, timer, 0);

	glutMainLoop();
}
