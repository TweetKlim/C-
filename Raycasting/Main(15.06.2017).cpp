#include <cmath>
#include <conio.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include "glut.h"
#include <windows.h>


using namespace std;
#define PI 3.14159265359
#define mapWidth 24
#define mapHeight 24
int TIME = 1;
int WINwidth = 700;
int WINheigth = 480;
double factor = WINheigth / mapHeight;
/*double rotSpeed = 0.003;
double moveSpeed = 0.01;*/
struct RGB
{
	double R = 0;
	double G = 0;
	double B = 0;
};


int worldMap[mapWidth][mapHeight] =
{
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,2,0,2,0,2,0,2,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,2,0,2,0,2,0,2,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,2,0,2,0,2,0,2,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,2,0,2,0,2,0,2,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1 },
	{ 1,0,3,0,3,0,3,0,3,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,2,0,2,0,2,0,2,0,0,0,0,1 },
	{ 1,0,2,0,2,0,2,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
};

void Line(int x, int drawStart, int drawEnd, RGB color)
{
	glBegin(GL_LINES);
	glColor3f(color.R, color.G, color.B);
	glVertex2f(x, drawStart);
	glVertex2f(x, drawEnd);
	glEnd();
}
void Sky()
{
	glBegin(GL_POLYGON);
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(0, WINheigth / 2);
	glVertex2f(WINwidth, WINheigth / 2);
	glVertex2f(WINwidth, WINheigth);
	glVertex2f(0, WINheigth);
	glEnd();
}
void Floor()
{
	glBegin(GL_POLYGON);
	glColor3f(0.5, 0.5, 0.5);
	glVertex2f(0, WINheigth / 2);
	glVertex2f(WINwidth, WINheigth / 2);
	glVertex2f(WINwidth, 0);
	glVertex2f(0, 0);
	glEnd();
}
void Ray(double posY, double posX, double rayDirY, double rayDirX, double R, int x)
{
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex2f(- posY * factor, posX * factor);
	glVertex2f(- (posY + R * rayDirY) * factor, (posX + R * rayDirX) * factor);
	glEnd();
}
void Map(double posY,double posX)
{
	for (int i = 0; i < mapWidth; ++i)
	{
		for (int u = 0; u < mapHeight; ++u)
		{
			if (worldMap[u][i] >= 1)
			{
				glBegin(GL_POLYGON);
				glColor3f(1, 0.5, worldMap[u][i] * 0.1);
				glVertex2f(- i * factor, u * factor);
				glVertex2f( - (i + 1) * factor, u * factor);
				glVertex2f( - (i + 1) * factor, (u + 1) * factor);
				glVertex2f( - i * factor, (u + 1) * factor);
				glEnd();
			}
		}
	}
	glBegin(GL_POINTS);
	glColor3f(0, 1, 0);
	glVertex2f(- posY * factor, posX * factor);
	glEnd();
}
void Frame(double frameTime)
{
	char c;
	c = int(1 / frameTime) / 10;
	glColor3f(1, 1, 1);
	glRasterPos2i(WINwidth - 50, WINheigth - 50);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c +'0');
	glEnd();
	c = int(1 / frameTime) % 10;
	glColor3f(1, 1, 1);
	glRasterPos2i(WINwidth - 40, WINheigth - 50);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c + '0');
	glEnd();
}



int display()
{
	double posX = 14, posY = 12;
	double dirX = -1, dirY = 0;
	double planeX = 0, planeY = 0.66;

	clock_t time = 0;
	clock_t oldTime = 0;
	while (true)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		Floor();
		Sky();

		for (int x = 0; x <= WINwidth; x++)
		{

			double cameraX = 2 * x / double(WINwidth) - 1;
			double rayPosX = posX;
			double rayPosY = posY;
			double rayDirX = dirX + planeX * cameraX;
			double rayDirY = dirY + planeY * cameraX;

			int mapX = int(rayPosX);
			int mapY = int(rayPosY);

			double sideDistX;
			double sideDistY;

			double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
			double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
			double perpWallDist;

			int stepX;
			int stepY;

			int hit = 0;
			int side;


			if (rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (rayPosX - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (rayPosY - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
			}
			while (hit == 0)
			{
				if (sideDistX < sideDistY)
				{
					sideDistX += deltaDistX;
					mapX += stepX;
					side = 0;
				}
				else
				{
					sideDistY += deltaDistY;
					mapY += stepY;
					side = 1;
				}
				if (worldMap[mapX][mapY] > 0)
				{
					hit = 1;
				}
			}

			if (side == 0) perpWallDist = (mapX - rayPosX + (1 - stepX) / 2) / rayDirX;
			else           perpWallDist = (mapY - rayPosY + (1 - stepY) / 2) / rayDirY;

			if (sideDistX < sideDistY) { Ray(posY, posX, rayDirY, rayDirX, perpWallDist, x); }
			else { Ray(posY, posX, rayDirY, rayDirX, perpWallDist, x); }

			int lineHeight = int(WINheigth / perpWallDist);

			int drawStart = -lineHeight / 2 + WINheigth / 2;
			if (drawStart < 0)drawStart = 0;
			int drawEnd = lineHeight / 2 + WINheigth / 2;
			if (drawEnd >= WINheigth)drawEnd = WINheigth - 1;

			RGB color;
			switch (worldMap[mapX][mapY])
			{
			case 1:  color.R = 1;								 break; //red
			case 2:  color.G = 1;								 break; //green
			case 3:  color.B = 1;								 break; //blue
			case 4:  color.R = 1; color.G = 1; color.B = 1;	     break; //white
			case 5:  color.R = 0; color.G = 0.7; color.B = 0.7; break; //grey
			}

			if (!side)
			{
				color.R /= 1.5;
				color.G /= 1.5;
				color.B /= 1.5;
			}

			Line(x, drawStart, drawEnd, color);
		}
		oldTime = time;
		time = clock();
		double frameTime = (time - oldTime) / CLOCKS_PER_SEC;
		cout << int(1 / frameTime);
		double moveSpeed = frameTime * 2.0;
		double rotSpeed = frameTime * 1.0;
		Frame(frameTime);

		glEnd();
		system("CLS");


		if (GetAsyncKeyState(VK_ESCAPE)) exit(0);
		if (GetAsyncKeyState(VK_UP))
		{
			if (worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
			if (worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
			cout << "//";
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			if (worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
			if (worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
			cout << "/";
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{

			double oldDirX = dirX;
			dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
			dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
			double oldPlaneX = planeX;
			planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
			planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
			cout << ">";
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			double oldDirX = dirX;
			dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
			dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
			double oldPlaneX = planeX;
			planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
			planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
			cout << "<";
		}
		Map(posY, posX);
		
		glFlush();
		

	}
}

void timer()
{
	display();
	glutTimerFunc(TIME, 0, 0);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WINwidth + WINheigth, WINheigth);
	glutInitWindowPosition(300, 200);
	glutCreateWindow("Raycasting");
	glClearColor(1.0, 1.0, 1.0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-WINheigth, WINwidth, 0, WINheigth, -1, 0);
	glutDisplayFunc(timer);
	glutMainLoop();
}