#include <windows.h>		// Header File For Windows
#include <fstream>

#include <gl/gl.h>			// Header File For The OpenGL32 Library
#include <gl/glu.h>			// Header File For The GLu32 Library
#include <gl/glaux.h>		// Header File For The Glaux Library
#include <cmath>
#include <texture.h>
#include <heightMap.h>
#include <Model_3ds.h>
#include <3DTexture.h>
#include <camera.h>
#include "tgaLoader.h"
#include <math3d.h>
#include <mmsystem.h> // for PlaySound()
#include <iostream>

HDC			hDC = NULL;		// Private GDI Device Context
HGLRC		hRC = NULL;		// Permanent Rendering Context
HWND		hWnd = NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active = TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen = TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc


// Console Data:

using namespace std;

int treesNum, buildingNum, carsNum, shipsNum;
int baseBuildingFloors, baseBuildingRooms;
bool turnMode = false;

// Nighting Mode
// Lighting
float Lightpos[] = { 0, 0, 0, 1.0 };
float Lightdiff[] = { 1, 1, 1, 1 };
float Lightamb[] = { 1, 1, 1, 1 };
float Lightspec[] = { 1, 1, 1, 1 };
float Matamb[] = { 1, 1, 1, 1 };
float Matspec[] = { 1, 1, 1, 1 };


GLfloat lightPos[] = { -1.0f, 3.0f, 0.0f, 0.0f };
GLfloat LightAmb[] = { 1.0f,1.0f,1.0f,1.0f };
GLfloat LightDiff[] = { 0.6f,0.6f,0.6f,1.0f };// Transformation matrix to project shadow
M3DMatrix44f shadowMat;
M3DVector3f points[3] = { { -30.0f, -2.0f, -20.0f }, { -30.0f, -2.0f, 20.0f },{ 40.0f, -2.0f, 20.0f } };

// Models:
Model_3DS *stair, *house, *sofa,
		  *table, *garbage, *cat,
		  *tree[2], *streetLamp[2],
		  *car, *fountain,*bridge,*ship;

// Tree
GLTexture m1, m2, m3,m4,m5;
GLTexture f1, f2, f3;
GLTexture sl1, sl2, sl3, sl4;
GLTexture img7, b[14], garbageTex, catTex[6];
int terrainImage, img2, img3, img4;
int buildingTexture, doorTexture, windowTexture, fourtSText, fourtWText;

// Terrain Data:
int terrainWidth = 25;
int terrainDepth = 25;
GLubyte* heightData;
int terrainTexture;
double texSStep = 1.0 / 25;
double texTStep = 1.0 / 25;
int TerrainSize = 25;

// River Data:
int riverWidth = 512;
int riverDepth = 512;
GLubyte* riverData;
int riverTexture;
double riverSStep = 1.0 / 512;
double riverTStep = 1.0 / 512;
int riverSize = 512;

// TEST
GLubyte* heightData1;

// Skybox
int SKYFRONT, SKYBACK, SKYLEFT, SKYRIGHT, SKYUP, SKYDOWN;

// RoadWay
int ROAD, grassGround,sandGround;

int img[5];

int image, image2;


float scaley = 0.2;

// Camera:
Camera MyCamera;


// Grass TGA Image
TGAImage grass;

GLfloat color[4] = { 0.5, 0.5, 0.5, 1 }; // color of fog


float fog = 0;

int ground;

/****************************************************************************/
class HOTEL {
public:
	int imgH1;
	int imgH2;
	int imgH3;
	int imgH4;
	int imgH5;
	int textures[6];
	int bigBuilt[3];
	int romBuilt[3];



	Model_3DS* models[10];
	GLTexture matereal_1[4];
	GLTexture matereal_2[1];
	GLTexture matereal_3[2];
	GLTexture matereal_4[3];

	Model_3DS* bed_room[10];
	GLTexture bed_room_0[4];
	GLTexture bed_room_1[4];
	GLTexture bed_room_2[4];
	GLTexture bed_room_3[4];
	GLTexture bed_room_4[4];
	GLTexture bed_room_5[4];



	void initmodels(Model_3DS* models[], int narray) {

		for (int i = 0; i < 10; i++)
			models[i] = new Model_3DS();
		//1,,,,,,,,,,,,,,,,,,,,,,,,,,
		models[0]->Load((char*)"3DS\\wall_clock\\Clock cristal N260119.3ds");
		//GLTexture matereal_1[4];
		matereal_1[0].LoadBMP((char*)"3DS\\wall_clock\\dialga.bmp");
		matereal_1[1].LoadBMP((char*)"3DS\\wall_clock\\Metal G6.bmp");
		matereal_1[2].LoadBMP((char*)"3DS\\wall_clock\\rd3.bmp");
		matereal_1[3].LoadBMP((char*)"3DS\\wall_clock\\wall_clock.bmp");
		models[0]->scale = 0.0007;
		//2,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
		models[1]->Load((char*)"3DS\\carpet\\Carpet NowCarpets Corso N240220\\Carpet NowCarpets Corso N240220.3ds");
		//GLTexture matereal_2[1];
		matereal_2[0].LoadBMP((char*)"3DS\\carpet\\Carpet NowCarpets Corso N240220\\Corso_df2.bmp");
		models[1]->scale = 0.0004;
		//3,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
		models[2]->Load((char*)"3DS\\armchair\\Armchair Madison Formdecor N030720\\Armchair Madison Formdecor N030720.3ds");
		//GLTexture matereal_3[2];
		matereal_3[0].LoadBMP((char*)"3DS\\armchair\\Armchair Madison Formdecor N030720\\HorlyWht.bmp");
		matereal_3[1].LoadBMP((char*)"3DS\\armchair\\Armchair Madison Formdecor N030720\\W1234sml.bmp");
		models[2]->scale = 0.01;//return 0.008
		//4,,,,,,,,,,
		models[3]->Load((char*)"3DS\\books\\Books N051017.3ds");
		//GLTexture matereal_4[3];
		matereal_4[0].LoadBMP((char*)"3DS\\books\\Cover_02.bmp");
		matereal_4[1].LoadBMP((char*)"3DS\\books\\Cover_03.bmp");
		matereal_4[2].LoadBMP((char*)"3DS\\books\\Pages_01.bmp");
		models[3]->scale = 0.008;
		//5:Armchair
		models[4]->Load((char*)"3DS\\armchair\\Armchair Madison Formdecor N030720\\Armchair Madison Formdecor N030720.3ds");
		//GLTexture matereal_3[2];
		matereal_3[0].LoadBMP((char*)"3DS\\armchair\\Armchair Madison Formdecor N030720\\HorlyWht.bmp");
		matereal_3[1].LoadBMP((char*)"3DS\\armchair\\Armchair Madison Formdecor N030720\\W1234sml.bmp");
		models[4]->scale = 0.01;
		//6:Armchair
		models[5]->Load((char*)"3DS\\armchair\\Armchair Madison Formdecor N030720\\Armchair Madison Formdecor N030720.3ds");
		//GLTexture matereal_3[2];
		matereal_3[0].LoadBMP((char*)"3DS\\armchair\\Armchair Madison Formdecor N030720\\HorlyWht.bmp");
		matereal_3[1].LoadBMP((char*)"3DS\\armchair\\Armchair Madison Formdecor N030720\\W1234sml.bmp");
		models[5]->scale = 0.01;
		//7:Armchair
		models[6]->Load((char*)"3DS\\armchair\\Armchair Madison Formdecor N030720\\Armchair Madison Formdecor N030720.3ds");
		//GLTexture matereal_3[2];
		matereal_3[0].LoadBMP((char*)"3DS\\armchair\\Armchair Madison Formdecor N030720\\HorlyWht.bmp");
		matereal_3[1].LoadBMP((char*)"3DS\\armchair\\Armchair Madison Formdecor N030720\\W1234sml.bmp");
		models[6]->scale = 0.01;
		//8:Armchair
		models[7]->Load((char*)"3DS\\armchair\\Armchair Madison Formdecor N030720\\Armchair Madison Formdecor N030720.3ds");
		//GLTexture matereal_3[2];
		matereal_3[0].LoadBMP((char*)"3DS\\armchair\\Armchair Madison Formdecor N030720\\HorlyWht.bmp");
		matereal_3[1].LoadBMP((char*)"3DS\\armchair\\Armchair Madison Formdecor N030720\\W1234sml.bmp");
		models[7]->scale = 0.008;
		//9:Armchair
		models[8]->Load((char*)"3DS\\armchair\\Armchair Madison Formdecor N030720\\Armchair Madison Formdecor N030720.3ds");
		//GLTexture matereal_3[2];
		matereal_3[0].LoadBMP((char*)"3DS\\armchair\\Armchair Madison Formdecor N030720\\HorlyWht.bmp");
		matereal_3[1].LoadBMP((char*)"3DS\\armchair\\Armchair Madison Formdecor N030720\\W1234sml.bmp");
		models[8]->scale = 0.008;
		//10:Armchair
		models[9]->Load((char*)"3DS\\armchair\\Armchair Madison Formdecor N030720\\Armchair Madison Formdecor N030720.3ds");
		//GLTexture matereal_3[2];
		matereal_3[0].LoadBMP((char*)"3DS\\armchair\\Armchair Madison Formdecor N030720\\HorlyWht.bmp");
		matereal_3[1].LoadBMP((char*)"3DS\\armchair\\Armchair Madison Formdecor N030720\\W1234sml.bmp");
		models[9]->scale = 0.008;
	}
	void initbed_rooms(Model_3DS * bed_room[], int narray) {

		for (int i = 0; i < 10; i++)
			bed_room[i] = new Model_3DS();
		//1:bed_1
		bed_room[0]->Load((char*)"3DS\\bed_room\\bed\\Bed.3ds");
		bed_room_0[0].LoadBMP((char*)"3DS\\bed_room\\bed\\1derevo.bmp");
		bed_room_0[1].LoadBMP((char*)"3DS\\bed_room\\bed\\8055.bmp");
		bed_room_0[2].LoadBMP((char*)"3DS\\bed_room\\bed\\Infinity 3881_2.bmp");
		bed_room_0[3].LoadBMP((char*)"3DS\\bed_room\\bed\\derevo.bmp");
		bed_room[0]->scale = 0.0009;
		//2,,,bed_side,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
		bed_room[1]->Load((char*)"3DS\\bed_room\\bed_side\\Bedsidetable.3DS");
		bed_room[1]->scale = 0.015;

		//3,stand
		bed_room[2]->Load((char*)"3DS\\bed_room\\stand\\Locker tv stand N071020\\Locker tv stand N071020.3ds");
		bed_room_2[0].LoadBMP((char*)"3DS\\bed_room\\stand\\Locker tv stand N071020\\Metal 6.bmp");
		bed_room_2[1].LoadBMP((char*)"3DS\\bed_room\\stand\\Locker tv stand N071020\\wood_9.bmp");
		bed_room[2]->scale = 0.000053;
		//4,table,,,,,,,,,
		bed_room[3]->Load((char*)"3DS\\bed_room\\BedcroomN141020\\Bed childroom N141020.3ds");
		bed_room_3[0].LoadBMP((char*)"3DS\\bed_room\\BedcroomN141020\\Wood1sml.bmp");
		bed_room_3[1].LoadBMP((char*)"3DS\\bed_room\\BedcroomN141020\\Tkan_pil.bmp");
		bed_room_3[2].LoadBMP((char*)"3DS\\bed_room\\table\\Table2\\metalbla.bmp");
		bed_room[3]->scale = 0.0003;

		//5 bed:2
		bed_room[4]->Load((char*)"3DS\\bed_room\\bed_ST1\\BedN220114.3DS");
		bed_room_4[0].LoadBMP((char*)"3DS\\bed_room\\bed_ST1\\Carpet1152x808px021213thiago.bmp");
		bed_room_4[1].LoadBMP((char*)"3DS\\bed_room\\bed_ST1\\tp200604031755358751762.bmp");

		bed_room[4]->scale = 0.1;


		//6 bed:3
		bed_room[5]->Load((char*)"3DS\\bed_room\\bed_3\\BedvivienDLSN180220\\BedvivienDLSN180220.3ds");
		bed_room_5[0].LoadBMP((char*)"3DS\\bed_room\\bed_3\\BedvivienDLSN180220\\4_greys.bmp");
		bed_room_5[1].LoadBMP((char*)"3DS\\bed_room\\bed_3\\BedvivienDLSN180220\\14_5_beg.bmp");
		bed_room_5[2].LoadBMP((char*)"3DS\\bed_room\\bed_3\\BedvivienDLSN180220\\cloth_07.bmp");
		bed_room_5[3].LoadBMP((char*)"3DS\\bed_room\\bed_3\\BedvivienDLSN180220\\Text_wht.bmp");

		bed_room[5]->scale = 0.01;
		glDisable(GL_TEXTURE_2D);

	}
	HOTEL() {

		imgH1 = LoadTexture((char*)"material_4.bmp", 255);
		imgH2 = LoadTexture((char*)"light wood.bmp", 255);
		imgH3 = LoadTexture((char*)"images\\window2.bmp", 255);
		imgH4 = LoadTexture((char*)"door.bmp", 255);
		imgH5 = LoadTexture((char*)"3DS\\building\\iron.bmp", 255);


		romBuilt[0] = LoadTexture((char*)"images\\marble b.bmp", 255);
		romBuilt[2] = LoadTexture((char*)"images\\pave005.bmp", 255);


		bigBuilt[0] = LoadTexture((char*)"images\\marble b.bmp", 255);
		bigBuilt[2] = LoadTexture((char*)"wall.bmp", 255);

		textures[0] = LoadTexture((char*)"images\\bricks\\232.bmp");
		textures[1] = LoadTexture((char*)"images\\bricks\\blue col.bmp");
		textures[2] = img2;
		textures[3] = img2;
		textures[4] = img2;
		textures[5] = img2;

		initmodels(models, 4);
		initbed_rooms(bed_room, 4);

	}
	void drow_models(Model_3DS * models[], double xpos, double ypos, double zpos, double xsize, double ysize, double zsize, int arde) {


		if (arde != 1) {
			models[1]->pos.x = xpos;
			models[1]->pos.y = ypos + (0.5 * ysize) - 0.48;
			models[1]->pos.z = zpos;
			//carpet->scale=
			models[1]->Draw();

			models[0]->pos.x = xpos;
			models[0]->pos.y = ypos + (0.5 * ysize);
			models[0]->pos.z = zpos - (0.49 * zsize);
			models[0]->Draw();



			models[2]->pos.x = xpos;
			models[2]->pos.y = ypos + (0.5 * ysize) - 0.38;
			models[2]->pos.z = zpos - (0.49 * zsize) + 0.2;//-0.2ÂÌ · ⁄œÌ· «·ﬂ—”Ì 
			models[2]->Draw();
			//............
			models[4]->pos.x = xpos - 0.5;
			models[4]->pos.y = ypos + (0.5 * ysize) - 0.38;
			models[4]->pos.z = zpos - (0.49 * zsize) + 0.2;//-0.2ÂÌ · ⁄œÌ· «·ﬂ—”Ì 
			models[4]->Draw();

			models[5]->pos.x = xpos + 0.5;
			models[5]->pos.y = ypos + (0.5 * ysize) - 0.38;
			models[5]->pos.z = zpos - (0.49 * zsize) + 0.2;//-0.2ÂÌ · ⁄œÌ· «·ﬂ—”Ì 
			models[5]->Draw();

			models[6]->rot.y = 180;
			models[6]->pos.x = xpos + 0.5;
			models[6]->pos.y = ypos + (0.5 * ysize) - 0.38;
			models[6]->pos.z = zpos + (0.49 * zsize) - 0.2;//-0.2ÂÌ · ⁄œÌ· «·ﬂ—”Ì 
			models[6]->Draw();

			models[7]->rot.y = 180;
			models[7]->pos.x = xpos - 0.5;
			models[7]->pos.y = ypos + (0.5 * ysize) - 0.38;
			models[7]->pos.z = zpos + (0.49 * zsize) - 0.2;//-0.2ÂÌ · ⁄œÌ· «·ﬂ—”Ì 
			models[7]->Draw();

			models[8]->rot.y = 180;
			models[8]->pos.x = xpos;
			models[8]->pos.y = ypos + (0.5 * ysize) - 0.38;
			models[8]->pos.z = zpos + (0.49 * zsize) - 0.2;//-0.2ÂÌ · ⁄œÌ· «·ﬂ—”Ì 
			models[8]->Draw();

			//.................
		}
		models[3]->pos.x = xpos;
		models[3]->pos.y = ypos;
		models[3]->pos.z = zpos;
		models[3]->Draw();

		/*wood_food->pos.x = xpos + 5;
		wood_food->pos.y = ypos;
		wood_food->pos.z = zpos;
		wood_food->Draw();


		sofa2->pos.x = xpos - 5;
		sofa2->pos.y = ypos;
		sofa2->pos.z = zpos;
		sofa2->Draw();



		Sconce->pos.x = xpos;
		Sconce->pos.y = ypos;
		Sconce->pos.z = zpos + 5;
		Sconce->Draw();



		Lavatory->pos.x = xpos;
		Lavatory->pos.y = ypos + 3;
		Lavatory->pos.z = zpos + 3;
		Lavatory->Draw();*/

	}


	void drow_bed_rooms(Model_3DS * bed_room[], double xpos, double ypos, double zpos, double xsize, double ysize, double zsize, bool arde) {


		if (arde != 1) {
			//bed
			bed_room[0]->rot.y = 90;
			bed_room[0]->pos.x = xpos - 0.4;
			bed_room[0]->pos.y = ypos + (0.5 * ysize) - 0.3;
			bed_room[0]->pos.z = zpos + 0.5;
			bed_room[0]->Materials[0].tex = bed_room_0[2];
			//bed_room[0]->Materials[1].tex = bed_room_0[0];
			//bed_room[0]->Materials[2].tex = bed_room_0[0];
			//bed_room[0]->Materials[3].tex = bed_room_0[0];
			//bed_room[0]->Draw();
			bed_room[0]->pos.x = xpos + 0.4;
			//bed_room[0]->Draw();

			//bed_room[1]->rot.y = 90;
			bed_room[1]->pos.x = xpos + 0.8;
			bed_room[1]->pos.y = ypos + (0.5 * ysize) - 0.45;
			bed_room[1]->pos.z = zpos + 0.8;
			bed_room[1]->Materials[0].tex = bed_room_1[0];
			bed_room[1]->Materials[1].tex = bed_room_1[1];
			bed_room[1]->Materials[2].tex = bed_room_1[2];
			bed_room[1]->Materials[3].tex = bed_room_1[3];
			//bed_room[1]->Draw();


			//stand
			bed_room[2]->pos.x = xpos + 0.5;
			bed_room[2]->pos.y = ypos + (0.5 * ysize) - 0.34;
			bed_room[2]->pos.z = zpos - 0.7;
			bed_room[2]->Materials[0].tex = bed_room_2[0];
			bed_room[2]->Materials[1].tex = bed_room_2[1];
			//bed_room[2]->Draw();

			//table
			bed_room[3]->rot.y = -90;
			bed_room[3]->pos.x = xpos + 0.3;
			bed_room[3]->pos.y = ypos + (0.5 * ysize) - 0.14;
			bed_room[3]->pos.z = zpos - 0.7;
			bed_room[3]->Materials[0].tex = bed_room_3[1];
			bed_room[3]->Materials[1].tex = bed_room_3[1];
			bed_room[3]->Materials[2].tex = bed_room_3[1];
			bed_room[3]->Materials[3].tex = bed_room_3[0];
			bed_room[3]->Materials[4].tex = bed_room_3[0];
			bed_room[3]->Materials[5].tex = bed_room_3[2];
			bed_room[3]->Materials[6].tex = bed_room_3[2];
			bed_room[3]->Draw();


			//armchar:

			models[2]->pos.x = xpos - 0.5;
			models[2]->pos.y = ypos + (0.5 * ysize) - 0.35;
			models[2]->pos.z = zpos - (0.49 * zsize) + 0.2;//-0.2ÂÌ · ⁄œÌ· «·ﬂ—”Ì 
			models[2]->Materials[0].tex = matereal_3[0];
			models[2]->Materials[1].tex = matereal_3[1];
			models[2]->Draw();


			models[6]->rot.y = 90;
			models[6]->pos.x = xpos - 0.77;
			models[6]->pos.y = ypos + (0.5 * ysize) - 0.35;
			models[6]->pos.z = zpos - (0.49 * zsize) + 0.55;//-0.2ÂÌ · ⁄œÌ· «·ﬂ—”Ì 
			models[6]->Materials[0].tex = matereal_3[0];
			models[6]->Materials[1].tex = matereal_3[1];
			models[6]->Draw();


			//4:bed_2
			bed_room[4]->rot.y = 90;
			bed_room[4]->pos.x = xpos - 0.4;
			bed_room[4]->pos.y = ypos + (0.5 * ysize) - 0.3;
			bed_room[4]->pos.z = zpos + 0.5;
			bed_room[4]->Materials[0].tex = bed_room_4[0];
			bed_room[4]->Materials[1].tex = bed_room_4[1];
			//bed_room[4]->Draw();



			//5:bed_3
			bed_room[5]->rot.y = 90;
			bed_room[5]->pos.x = xpos - 0.4;
			bed_room[5]->pos.y = ypos + (0.5 * ysize) - 0.3;
			bed_room[5]->pos.z = zpos + 0.5;
			bed_room[5]->Materials[0].tex = bed_room_5[0];
			bed_room[5]->Materials[1].tex = bed_room_5[1];
			bed_room[5]->Materials[2].tex = bed_room_5[2];
			bed_room[5]->Materials[3].tex = bed_room_5[3];
			bed_room[5]->Draw();
			bed_room[5]->pos.x = xpos + 0.45;
			bed_room[5]->Draw();


		}
	}


	bool open_door = false;
	double x_door = 0;
	void draw_door(int move) {
		double x_move = 0;
		if (move == 1)x_move = -0.2;
		glPushMatrix();
		if (move == 0) {
			glTranslated(x_door, 0, 0);
		}
		glBindTexture(GL_TEXTURE_2D, img4);
		glBegin(GL_QUADS);

		glTexCoord2d(0, 0); glVertex3d(-0.1 + x_move, -0.5, 0.501);//glVertex3d(-0.15, -0.5, 0.501);
		glTexCoord2d(1, 0); glVertex3d(0.1 + x_move, -0.5, 0.501);//glVertex3d(0.15, -0.5, 0.501);
		glTexCoord2d(1, 1); glVertex3d(0.1 + x_move, 0.1, 0.501);//glVertex3d(0.15, 0.1, 0.501);
		glTexCoord2d(0, 1); glVertex3d(-0.1 + x_move, 0.1, 0.501);//glVertex3d(-0.15, 0.1, 0.501);
		glEnd();
		glPopMatrix();
		if (move == 0) {

			if (open_door && x_door >= -0.2) x_door -= 0.001;
			if (!open_door && x_door < 0) x_door += 0.001;
		}
	}
	void draw_windo() {
		glEnable(GL_BLEND);
		glPushAttrib(GL_CURRENT_BIT | GL_COLOR_BUFFER_BIT | GL_LIGHTING_BIT);
		glColor4f(1.0, 1.0, 1.0, 0.5);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glDepthMask(GL_FALSE);
		glBindTexture(GL_TEXTURE_2D, img3);

		glPushMatrix();
		glBegin(GL_QUADS);

		glTexCoord2d(0, 0); glVertex3d(-0.15, -0.5, 0.501);
		glTexCoord2d(0, 1); glVertex3d(0.15, -0.5, 0.501);
		glTexCoord2d(1, 1); glVertex3d(0.15, 0.1, 0.501);
		glTexCoord2d(1, 0); glVertex3d(-0.15, 0.1, 0.501);
		/*glColor4d(0.3, 0.6, 0.1, 0.52);
		 glVertex3d(-0.15, -0.5, 0.501);
		 glVertex3d(0.15, -0.5, 0.501);
		 glVertex3d(0.15, 0.1, 0.501);
		 glVertex3d(-0.15, 0.1, 0.501);
		 glColor4d( 1, 1, 1, 0.52);*/
		glEnd();
		glPopMatrix();

		glDepthMask(GL_TRUE);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glPopAttrib();
		glDisable(GL_BLEND);

	}
	void first_built_222222(int texture[], int tiby) {



		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, img2);

		glPushMatrix();
		//glColor3ub(25, 50, 170);!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

		//up
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		double tx0 = 2, ty0 = 2;
		glBegin(GL_QUADS);
		glTexCoord2d(tx0, ty0);
		glVertex3d(0.5, 0.5, 0.5);

		glTexCoord2d(0, ty0);
		glVertex3d(0.5, 0.5, -0.5);

		glTexCoord2d(0, 0);
		glVertex3d(-0.5, 0.5, -0.5);

		glTexCoord2d(tx0, 0);
		glVertex3d(-0.5, 0.5, 0.5);
		glEnd();

		//down:
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		double tx1 = 2, ty1 = 2;
		glBegin(GL_QUADS);
		glTexCoord2d(tx1, ty1);
		glVertex3d(0.5, -0.5, 0.5);
		glTexCoord2d(0, ty1);
		glVertex3d(0.5, -0.5, -0.5);
		glTexCoord2d(0, 0);
		glVertex3d(-0.5, -0.5, -0.5);
		glTexCoord2d(tx1, 0);
		glVertex3d(-0.5, -0.5, 0.5);
		glEnd();

		//right
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		double tx2 = 2, ty2 = 2;
		glBegin(GL_QUADS);
		glTexCoord2d(tx2, ty2);
		glVertex3d(0.5, 0.5, 0.5);

		glTexCoord2d(0, ty2);
		glVertex3d(0.5, 0.5, -0.5);

		glTexCoord2d(0, 0);
		glVertex3d(0.5, -0.5, -0.5);

		glTexCoord2d(tx2, 0);
		glVertex3d(0.5, -0.5, 0.5);
		glEnd();
		//left
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		double tx3 = 2, ty3 = 2;
		glBegin(GL_QUADS);
		glTexCoord2d(tx3, ty3);
		glVertex3d(-0.5, 0.5, 0.5);

		glTexCoord2d(0, ty3);
		glVertex3d(-0.5, 0.5, -0.5);

		glTexCoord2d(0, 0);
		glVertex3d(-0.5, -0.5, -0.5);

		glTexCoord2d(tx3, 0);
		glVertex3d(-0.5, -0.5, 0.5);
		glEnd();
		glPopMatrix();


		glColor3d(1, 1, 1);

		if (tiby == 1) {

			//front
			glBindTexture(GL_TEXTURE_2D, texture[2]);
			glBegin(GL_QUADS);
			//«·⁄ »…
			double tx5 = 3, ty5 = 0.5;
			glTexCoord2d(tx5, ty5);
			glVertex3d(0.5, 0.5, -0.5);

			glTexCoord2d(0, ty5);
			glVertex3d(-0.5, 0.5, -0.5);

			glTexCoord2d(0, 0);
			glVertex3d(-0.5, 0.1, -0.5);

			glTexCoord2d(tx5, 0);
			glVertex3d(0.5, 0.1, -0.5);
			//Ì„Ì‰
			double tx6 = 1, ty6 = 0.7;
			glTexCoord2d(tx6, ty6);
			glVertex3d(0.5, 0.1, -0.5);

			glTexCoord2d(0, ty6);
			glVertex3d(0.1, 0.1, -0.5);//glVertex3d(0.15, 0.1, 0.5);

			glTexCoord2d(0, 0);
			glVertex3d(0.1, -0.5, -0.5);//glVertex3d(0.15, -0.5, 0.5);

			glTexCoord2d(tx6, 0);
			glVertex3d(0.5, -0.5, -0.5);
			//Ì”«—
			double tx7 = 3, ty7 = 5;
			glTexCoord2d(tx7, ty7);
			glVertex3d(-0.1, 0.1, -0.5);//glVertex3d(-0.15, 0.1, 0.5);

			glTexCoord2d(0, ty7);
			glVertex3d(-0.5, 0.1, -0.5);//glVertex3d(-0.5, 0.1, 0.5);

			glTexCoord2d(0, 0);
			glVertex3d(-0.5, -0.5, -0.5);//glVertex3d(-0.5, -0.5, 0.5);

			glTexCoord2d(tx7, 0);
			glVertex3d(-0.1, -0.5, -0.5);//glVertex3d(-0.15, -0.5, 0.5);


			glEnd();
		}
		else {
			//back
			glBindTexture(GL_TEXTURE_2D, texture[2]);
			double tx4 = 3, ty4 = 5;
			glBegin(GL_QUADS);
			glTexCoord2d(0, ty4);
			glVertex3d(0.5, 0.5, -0.5);

			glTexCoord2d(tx4, ty4);
			glVertex3d(-0.5, 0.5, -0.5);

			glTexCoord2d(tx4, 0);
			glVertex3d(-0.5, -0.5, -0.5);

			glTexCoord2d(0, 0);
			glVertex3d(0.5, -0.5, -0.5);

			glEnd();
		}

		//front
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glBegin(GL_QUADS);
		//«·⁄ »…
		double tx5 = 3, ty5 = 0.5;
		glTexCoord2d(tx5, ty5);
		glVertex3d(0.5, 0.5, 0.5);

		glTexCoord2d(0, ty5);
		glVertex3d(-0.5, 0.5, 0.5);

		glTexCoord2d(0, 0);
		glVertex3d(-0.5, 0.1, 0.5);

		glTexCoord2d(tx5, 0);
		glVertex3d(0.5, 0.1, 0.5);
		//Ì„Ì‰
		double tx6 = 1, ty6 = 0.7;
		glTexCoord2d(tx6, ty6);
		glVertex3d(0.5, 0.1, 0.5);

		glTexCoord2d(0, ty6);
		glVertex3d(0.1, 0.1, 0.5);//glVertex3d(0.15, 0.1, 0.5);

		glTexCoord2d(0, 0);
		glVertex3d(0.1, -0.5, 0.5);//glVertex3d(0.15, -0.5, 0.5);

		glTexCoord2d(tx6, 0);
		glVertex3d(0.5, -0.5, 0.5);
		//Ì”«—
		double tx7 = 3, ty7 = 5;
		glTexCoord2d(tx7, ty7);
		glVertex3d(-0.1, 0.1, 0.5);//glVertex3d(-0.15, 0.1, 0.5);

		glTexCoord2d(0, ty7);
		glVertex3d(-0.5, 0.1, 0.5);//glVertex3d(-0.5, 0.1, 0.5);

		glTexCoord2d(0, 0);
		glVertex3d(-0.5, -0.5, 0.5);//glVertex3d(-0.5, -0.5, 0.5);

		glTexCoord2d(tx7, 0);
		glVertex3d(-0.1, -0.5, 0.5);//glVertex3d(-0.15, -0.5, 0.5);


		glEnd();


	}
	bool turn_up_0 = false;
	bool turn_up_1 = false;
	bool turn_up_2 = false;
	bool turn_up_3 = false;
	bool turn = false;
	double updown = 0;
	double updown_2;
	void first_built_msad(int texture[], int tiby) {
		updown_2 = updown;

		if (tiby == 0 || tiby == 1 || tiby == 2)updown = 0;

		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, img2);

		glPushMatrix();
		//glColor3ub(25, 50, 170);!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

		if (tiby == 2 || tiby == 5) {
			//up
			glBindTexture(GL_TEXTURE_2D, texture[0]);
			double tx0 = 2, ty0 = 2;
			glBegin(GL_QUADS);
			glTexCoord2d(tx0, ty0);
			glVertex3d(0.5, 0.5 + updown, 0.5);

			glTexCoord2d(0, ty0);
			glVertex3d(0.5, 0.5 + updown, -0.5);

			glTexCoord2d(0, 0);
			glVertex3d(-0.5, 0.5 + updown, -0.5);

			glTexCoord2d(tx0, 0);
			glVertex3d(-0.5, 0.5 + updown, 0.5);
			glEnd();
		}

		if (tiby == 0 || tiby == 5) {
			//down:
			glBindTexture(GL_TEXTURE_2D, texture[1]);
			double tx1 = 2, ty1 = 2;
			glBegin(GL_QUADS);
			glTexCoord2d(tx1, ty1);
			glVertex3d(0.5, -0.5 + updown, 0.5);
			glTexCoord2d(0, ty1);
			glVertex3d(0.5, -0.5 + updown, -0.5);
			glTexCoord2d(0, 0);
			glVertex3d(-0.5, -0.5 + updown, -0.5);
			glTexCoord2d(tx1, 0);
			glVertex3d(-0.5, -0.5 + updown, 0.5);
			glEnd();
		}
		//right
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		double tx2 = 2, ty2 = 2;
		glBegin(GL_QUADS);
		glTexCoord2d(tx2, ty2);
		glVertex3d(0.5, 0.5 + updown, 0.5);

		glTexCoord2d(0, ty2);
		glVertex3d(0.5, 0.5 + updown, -0.5);

		glTexCoord2d(0, 0);
		glVertex3d(0.5, -0.5 + updown, -0.5);

		glTexCoord2d(tx2, 0);
		glVertex3d(0.5, -0.5 + updown, 0.5);
		glEnd();
		//left
		glBindTexture(GL_TEXTURE_2D, texture[3]);
		double tx3 = 2, ty3 = 2;
		glBegin(GL_QUADS);
		glTexCoord2d(tx3, ty3);
		glVertex3d(-0.5, 0.5 + updown, 0.5);

		glTexCoord2d(0, ty3);
		glVertex3d(-0.5, 0.5 + updown, -0.5);

		glTexCoord2d(0, 0);
		glVertex3d(-0.5, -0.5 + updown, -0.5);

		glTexCoord2d(tx3, 0);
		glVertex3d(-0.5, -0.5 + updown, 0.5);
		glEnd();
		glPopMatrix();


		glColor3d(1, 1, 1);





		//back
		glBindTexture(GL_TEXTURE_2D, texture[4]);
		double tx4 = 3, ty4 = 5;
		glBegin(GL_QUADS);
		glTexCoord2d(0, ty4);
		glVertex3d(0.5, 0.5 + updown, -0.5);

		glTexCoord2d(tx4, ty4);
		glVertex3d(-0.5, 0.5 + updown, -0.5);

		glTexCoord2d(tx4, 0);
		glVertex3d(-0.5, -0.5 + updown, -0.5);

		glTexCoord2d(0, 0);
		glVertex3d(0.5, -0.5 + updown, -0.5);

		glEnd();

		if (tiby == 5)return;
		//front
		glBindTexture(GL_TEXTURE_2D, texture[5]);
		glBegin(GL_QUADS);
		//«·⁄ »…
		double tx5 = 3, ty5 = 0.5;
		glTexCoord2d(tx5, ty5);
		glVertex3d(0.5, 0.5, 0.5);

		glTexCoord2d(0, ty5);
		glVertex3d(-0.5, 0.5, 0.5);

		glTexCoord2d(0, 0);
		glVertex3d(-0.5, 0.1, 0.5);

		glTexCoord2d(tx5, 0);
		glVertex3d(0.5, 0.1, 0.5);
		//Ì„Ì‰
		double tx6 = 1, ty6 = 0.7;
		glTexCoord2d(tx6, ty6);
		glVertex3d(0.5, 0.1, 0.5);

		glTexCoord2d(0, ty6);
		glVertex3d(0.1, 0.1, 0.5);//glVertex3d(0.15, 0.1, 0.5);

		glTexCoord2d(0, 0);
		glVertex3d(0.1, -0.5, 0.5);//glVertex3d(0.15, -0.5, 0.5);

		glTexCoord2d(tx6, 0);
		glVertex3d(0.5, -0.5, 0.5);
		//Ì”«—
		double tx7 = 3, ty7 = 5;
		glTexCoord2d(tx7, ty7);
		glVertex3d(-0.1, 0.1, 0.5);//glVertex3d(-0.15, 0.1, 0.5);

		glTexCoord2d(0, ty7);
		glVertex3d(-0.5, 0.1, 0.5);//glVertex3d(-0.5, 0.1, 0.5);

		glTexCoord2d(0, 0);
		glVertex3d(-0.5, -0.5, 0.5);//glVertex3d(-0.5, -0.5, 0.5);

		glTexCoord2d(tx7, 0);
		glVertex3d(-0.1, -0.5, 0.5);//glVertex3d(-0.15, -0.5, 0.5);


		glEnd();
		updown = updown_2;
		if (turn_up_0)
		{
			if (updown < 0)
				updown += 0.01;
			else if (updown > 0.01)
				updown -= 0.01;
		}
		if (turn_up_1)
		{
			if (updown < 1)
				updown += 0.01;
			else if (updown > 1.01)
				updown -= 0.01;
		}
		if (turn_up_2) {
			if (updown < 2)
				updown += 0.01;
			else if (updown > 2.01)
				updown -= 0.01;
		}
		if (turn_up_3) {
			if (updown < 3)
				updown += 0.01;
			else if (updown > 3.01)
				updown -= 0.01;
		}
	}
	void second_built(double xpos, double ypos, double zpos, double xsize, double ysize, double zsize, double eng, double front_Texture, int arde, int texture[]) {

		glPushMatrix();
		glTranslated(xpos, ypos + (0.5 * ysize), zpos);//the adding on ypos to be on the ground
		glScaled(xsize, ysize, zsize);
		glRotated(eng, 0, 2, 0);



		first_built_222222(texture, arde);
		int x_door = 1;
		if (arde == 1)x_door = 0;

		if (ypos == 0 || xsize < 3)
		{
			draw_door(x_door);

		}
		else draw_windo();




		glPopMatrix();

		drow_bed_rooms(bed_room, xpos, ypos, zpos, xsize, ysize, zsize, arde);

		//drow_models(models, xpos, ypos, zpos, xsize, ysize, zsize, arde);





	}
	void second_built_msad(double xpos, double ypos, double zpos, double xsize, double ysize, double zsize, double eng, double front_Texture, int arde) {

		glPushMatrix();
		glTranslated(xpos, ypos + (0.5 * ysize), zpos);//the adding on ypos to be on the ground
		glScaled(xsize, ysize, zsize);
		glRotated(eng, 0, 2, 0);



		first_built_msad(textures, arde);


		if (ypos == 0 || xsize < 3)
		{
			draw_door(0);

		}
		else draw_windo();




		glPopMatrix();







	}
	void second_built_hotel(double xpos, double ypos, double zpos, double xsize, double ysize, double zsize, double eng, double front_Texture, bool arde) {

		glPushMatrix();
		glTranslated(xpos, ypos + (0.5 * ysize), zpos);//the adding on ypos to be on the ground
		glScaled(xsize, ysize, zsize);
		glRotated(eng, 0, 2, 0);



		first_built_222222(textures, 0);


		if (ypos == 0 || xsize < 3)
		{
			draw_door(0);

		}
		else draw_windo();




		glPopMatrix();

		drow_bed_rooms(bed_room, xpos, ypos, zpos, xsize, ysize, zsize, arde);

		//drow_models(models, xpos, ypos, zpos, xsize, ysize, zsize, arde);





	}













	void rooms_add_2(double x, double room_number, double q, double x2, double hight, bool the_tallest_side) {
		double j;
		double k = 0;

		if (!the_tallest_side)k = 1;

		j = (room_number)-1;//  j = (double)(room_number / 2) - 0.51- 0.5*2
		////j = 5;
		//	k = 0;							/*    do some thing with this second_built   Ÿ»Ìÿ ⁄—÷ «·’› «·«Ì”— „‰ «·€—›       */
		for (double i = j + k; i >= -j + k; i = i - 2) {
			//loooooooooox2oooooooooook....->down
			second_built(x2, hight, i, 2, 0.99, 1.9970, q, 1, 0, romBuilt);//second_built(x2, hight, i, 0.5, 1, 1, q, 1);

		}


	}

	void extra_built_2(double room_number, double hight, int floor) {
		double right_room_number;
		double left_room_number = room_number;
		bool is_tallest_side = true;


		int arde = 0;
		if (hight > 0 && hight < floor)arde = 1;
		else if (hight == floor)arde = 2;


		int iz1 = (int)room_number / 2;
		right_room_number = (double)iz1;


		if ((int)room_number % 2 != 0) {
			left_room_number = right_room_number + 1;
			is_tallest_side = false;
		}
		else
			left_room_number = right_room_number;

		//looooooooooooooooooooooo2oooooooooooook....->down
		second_built(0, hight, 0, 5, 1, 2 * (left_room_number), 0, 0, 1, romBuilt);//room_number2+0.1Ã⁄·  «·€—› œ«Œ· «·»Ì  
		second_built(0, hight, 0 + 1, 5.1, 1, 2 * (left_room_number + 1) + 0.1, 0, 0, 1, bigBuilt);

		second_built_msad(0, hight, -(room_number / 2) - 0.25, 1, 1, 0.5, 0, 0, arde);

		if (hight == 0)second_built_msad(0, hight, -(room_number / 2) - 0.25, 1, 1, 0.5, 0, 0, 5);


		double x;
		double y;
		double z;

		x = 2;
		z = 5;
		rooms_add_2(x, right_room_number, -90, 1.5, hight, is_tallest_side);
		rooms_add_2(x, left_room_number, 90, -1.5, hight, true);




	}
	double ex = 0;
	double ey = 0;
	double ez = 0;
	double cx = 0;
	double cy = 0;
	double cz = -15;
	double q = 90;
	void camera()
	{

		if (keys['9'])
		{
			turn_up_1 = true;
			turn_up_0 = false;
			turn_up_2 = false;
			turn_up_3 = false;
		}


		if (keys['8'])
		{
			turn_up_2 = true;
			turn_up_0 = false;
			turn_up_1 = false;
			turn_up_3 = false;
		}

		if (keys['7'])
		{
			turn_up_3 = true;
			turn_up_2 = false;
			turn_up_1 = false;
			turn_up_0 = false;
		}

		if (keys['6'])
		{
			turn_up_0 = true;
			turn_up_1 = false;
			turn_up_2 = false;
			turn_up_3 = false;
		}







		if (keys['O']) { open_door = true; }
		if (keys['P']) { open_door = false; }

		if (keys['W']) { ez -= 0.1; cz -= 0.1; }
		if (keys['S']) { ez += 0.1;  cz += 0.1; }

		if (keys['D']) { ex += 0.1; cx += 0.1; }
		if (keys['A']) { ex -= 0.1; cx -= 0.1; }

		if (keys['R']) { ey += 0.1; cy += 0.1; }
		if (keys['F']) { ey -= 0.1; cy -= 0.1; }

		if (keys['I']) { cy += 0.1; }
		if (keys['K']) { cy -= 0.1; }

		if (keys['Y']) {
			q -= 0.01;
			cx = 10 * cos(q);
			cz = -10 * sin(q);
		}
		if (keys['H']) {
			q += 0.01;
			cx = cx * cos(q);
			cz = cz * sin(q);
		}

		if (keys['L']) { cx += 0.4; }
		if (keys['J']) { cx -= 0.4; }



	}
	void drowHotel(double room_number, double flour_numberdouble, double xpos, double ypos, double zpos, double xsize, double ysize, double zsize, double eng) {
		glPushMatrix();
		glTranslated(xpos, ypos, zpos);
		glScaled(xsize, ysize, zsize);
		glRotated(eng, 0, 10, 0);
		for (double i = 0; i < flour_numberdouble; i++)
			extra_built_2(room_number, i, flour_numberdouble - 1);

		glPopMatrix();


	}

};

HOTEL* mk;
/******************************************************************************************************************************************/

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

void drawMyRiver() {

	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	//glRotated(90, 0, 1, 0);


	glTranslatef(-riverWidth / 2.0, 0, -riverDepth / 2.0);

	glScaled(1, 0.05, 3);
	glBindTexture(GL_TEXTURE_2D, riverTexture);
	for (int i = 5; i < riverDepth - 5; i++) {
		glBegin(GL_TRIANGLE_STRIP);
		for (int j = 5; j < riverWidth - 5; j++) {

			glTexCoord2d(j * riverSStep + 5, i * riverTStep);
			glVertex3f(j, riverData[j + i * riverDepth] -60, i);

			glTexCoord2d(j * texSStep, (i + 1) + 5 * texTStep);
			glVertex3f(j, riverData[j + (i + 1) * riverDepth] - 60, i + 1);

			glTexCoord2d((j + 1) * riverSStep + 5, i * riverTStep);
			glVertex3f(j + 1, riverData[(j + 1) + i * riverDepth] - 60, i);

			glTexCoord2d((j + 1) * riverSStep + 5, (i + 1) * riverTStep);
			glVertex3f(j + 1, riverData[(j + 1) + (i + 1) * riverDepth] - 60, i + 1);

		}
		glEnd();
	}

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

}


int InitGL(GLvoid)								// All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading  window
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glEnable(GL_TEXTURE_2D);
	
	//// Loop Sound
	//PlaySound("audio\\starting.wav", NULL, SND_LOOP | SND_ASYNC);  

	//Terrain
	heightData = new GLubyte[terrainWidth * terrainDepth];
	heightData = LoadHeightMap((char*)"images\\Islands.bmp");
	terrainTexture = LoadTexture((char*)"images\\grass.bmp");
	////river
	//riverData = new GLubyte[terrainWidth * terrainDepth];
	//riverData = LoadHeightMap((char*)"images\\RiverBed.bmp");
	//riverTexture = LoadTexture((char*)"images\\water2.bmp");
	// 
	////****TEST
	//heightData1 = new GLubyte[terrainWidth * terrainDepth];
	//heightData1 = LoadHeightMap((char*)"images\\heightsmap.bmp");
	//terrainTexture = LoadTexture((char*)"images\\grass.bmp");

	// Skybox
	SKYFRONT = LoadTexture((char*)"skybox\\front_2.bmp");
	SKYBACK = LoadTexture((char*)"skybox\\back_2.bmp");
	SKYLEFT = LoadTexture((char*)"skybox\\left_2.bmp");
	SKYRIGHT = LoadTexture((char*)"skybox\\right_2.bmp");
	SKYUP = LoadTexture((char*)"skybox\\up_2.bmp");
	SKYDOWN = LoadTexture((char*)"skybox\\down_2.bmp");

	// Road
	ROAD = LoadTexture((char*)"images\\road1.bmp");

	// Camera
	MyCamera = Camera();

	

	// Grass Ground
	grassGround = LoadTexture((char*)"images\\grass.bmp");
	sandGround = LoadTexture((char*)"images\\sand.bmp");

	// Building
	//buildingTexture = LoadTexture((char*)"images\\wall.bmp");
	//doorTexture = LoadTexture((char*)"images\\door.bmp");
	//windowTexture = LoadTexture((char*)"images\\window.bmp");



	////tree
	//image = LoadTexture((char*)"images\\back.bmp");

	//image2 = LoadTexture((char*)"data\\DU icon.bmp");
	//m1.LoadBMP((char*)"3DS\\tree\\bark_loo.bmp");

	//image2 = LoadTexture((char*)"data\\DU icon.bmp");
	//m2.LoadBMP((char*)"images\\grass.bmp");

	//image2 = LoadTexture((char*)"data\\DU icon.bmp");
	//m3.LoadBMP((char*)"3DS\\car\\blackColor.bmp"); 

	//image2 = LoadTexture((char*)"data\\DU icon.bmp");
	//m4.LoadBMP((char*)"images\\water2.bmp");


	//image2 = LoadTexture((char*)"data\\DU icon.bmp");
	//m5.LoadBMP((char*)"images\\road.bmp");


	//tree[0] = new Model_3DS();
	//tree[0]->Load((char*)"3DS\\tree\\M_TREE5.3ds");
	//tree[0]->scale=0.05;
	//tree[1] = new Model_3DS();
	//tree[1]->Load((char*)"3DS\\tree\\Tree1.3ds");
	//tree[1]->scale = 0.05;

	//// fountain
	//image = LoadTexture((char*)"images\\back.bmp");
	//image2 = LoadTexture((char*)"data\\DU icon.bmp");
	//f1.LoadBMP((char*)"images\\ground005.bmp");

	//image2 = LoadTexture((char*)"data\\DU icon.bmp");
	//f2.LoadBMP((char*)"3DS\\fountain\\grass_as2.bmp");

	//image2 = LoadTexture((char*)"data\\DU icon.bmp");
	//f3.LoadBMP((char*)"images\\water2.bmp");


	//terrainImage = LoadTexture((char*)"material_4.bmp", 255);
	//img2 = LoadTexture((char*)"light wood.bmp", 255);
	//img3 = LoadTexture((char*)"window.bmp", 255);
	//img4 = LoadTexture((char*)"door.bmp", 255);
	//img7.LoadBMP((char*)"light wood.bmp");
	//
	//garbageTex.LoadBMP((char*)"3DS\\building\\iron.bmp");
	//
	//stair= new Model_3DS();
	//stair->Load((char*)"Stairs.3ds");
	//stair->pos.x = 0;
	//stair->pos.y = 0;
	//stair->pos.z = 7;

	///**************  House  ****************/
	//b[0].LoadBMP((char*)"3DS\\building\\window2.bmp");
	//b[1].LoadBMP((char*)"3DS\\building\\door2.bmp");
	//b[2].LoadBMP((char*)"3DS\\building\\iron.bmp");
	//b[3].LoadBMP((char*)"3DS\\building\\window2.bmp");
	//b[4].LoadBMP((char*)"images\\grass.bmp");
	//b[5].LoadBMP((char*)"3DS\\building\\w2.bmp");
	//b[6].LoadBMP((char*)"3DS\\building\\AC.bmp");
	//b[7].LoadBMP((char*)"3DS\\building\\door3.bmp");
	//b[8].LoadBMP((char*)"3DS\\building\\store.bmp");
	//b[9].LoadBMP((char*)"3DS\\building\\window3.bmp");
	//b[10].LoadBMP((char*)"3DS\\building\\brack.bmp");
	//b[11].LoadBMP((char*)"3DS\\building\\top.bmp");
	//b[12].LoadBMP((char*)"3DS\\building\\w2.bmp");
	////b[13].LoadBMP((char*)"3DS\\taxi\\Taxi.bmp");
	//
	////catTex[0].LoadBMP((char*)"3DS\\cat\\cat_AO.bmp");
	//catTex[1].LoadBMP((char*)"3DS\\cat\\cat_C.bmp");
	///*catTex[2].LoadBMP((char*)"3DS\\cat\\cat_D.bmp");
	//catTex[3].LoadBMP((char*)"3DS\\cat\\cat_N.bmp");
	//catTex[4].LoadBMP((char*)"3DS\\cat\\cat_S.bmp");*/
	//catTex[5].LoadBMP((char*)"3DS\\cat\\catEyes_S.bmp");

	//house = new Model_3DS[20];
	//
	//for (int i = 0; i < 20; i++) {
	//
	//	house[i].Load((char*)"3DS\\building\\building.3DS");
	//	//home 
	//	house[i].Materials[0].tex = b[7];// back door
	//	house[i].Materials[1].tex = b[0]; // windows
	//	house[i].Materials[2].tex = b[1]; // door
	//	house[i].Materials[3].tex = b[6]; // Ãÿ⁄… «·”ÿÕ
	//	house[i].Materials[4].tex = b[3]; // „ﬂÌ›
	//	house[i].Materials[5].tex = b[4]; // ground
	//	house[i].Materials[6].tex = b[10]; // ground
	//	house[i].Materials[7].tex = b[12]; // edges of roof
	//	house[i].Materials[8].tex = b[7];
	//	house[i].Materials[9].tex = b[8]; // back wall
	//	house[i].Materials[10].tex = b[9]; // back windows
	//	house[i].Materials[11].tex = b[10]; // wall of building
	//	house[i].Materials[12].tex = b[11]; // roof of building
	//	house[i].Materials[13].tex = b[12]; // stair and frame of window and doors
	//}
	//sofa = new Model_3DS();
	//sofa->Load((char*)"3DS\\taxi\\taxi.3DS");
	//sofa->pos.x = -5;
	//sofa->pos.y = 0;
	//sofa->pos.z = 11;
	//sofa->scale = 0.01;
	//sofa->Materials[1].tex= b[1];

	//car = new Model_3DS();
	//car->Load((char*)"3DS\\car\\Lamborghini.3DS");
	//car->scale = 0.2;
	//car->pos.x = 0;
	//car->pos.y = 3;
	//car->pos.z = 0;
	//car->rot.y = 270;

	//for (int i = 0; i < 2; i++) {
	//	streetLamp[i] = new Model_3DS();
	//	streetLamp[i]->Load((char*)"3DS\\StreetLamp\\StreetLamp.3DS");
	//	streetLamp[i]->Materials[1].tex = sl2;
	//	streetLamp[i]->Materials[2].tex = sl3;
	//	streetLamp[i]->Materials[3].tex = m2;
	//	streetLamp[i]->Materials[4].tex = sl1;
	//}

	////sofa->scale = 1;
	//
	//table = new Model_3DS();
	//table->Load((char*)"3DS\\objects\\roundTable.3ds");
	//table->pos.x = 0;
	//table->pos.y = 0;
	//table->pos.z = 11;
	//table->Materials->tex = b[2];
	//table->scale = 0.5;
	//
	//garbage = new Model_3DS();
	//garbage->Load((char*)"3DS\\objects\\garbageContainer.3ds");
	//garbage->pos.x = 5;
	//garbage->pos.y = 0;
	//garbage->pos.z = 11;
	//garbage->Materials->tex = garbageTex;
	//garbage->scale = 0.1;

	//cat = new Model_3DS();
	//cat->Load((char*)"3DS\\cat\\cat.3ds");
	//cat->pos.x = 2;
	//cat->pos.y = 0;
	//cat->pos.z = 11;
	//cat->Materials[0].tex = catTex[1]; // eyes
	//cat->Materials[1].tex = catTex[1]; // skin
	//cat->scale = 1;


	//bridge = new Model_3DS();
	//bridge->Load((char*)"3DS\\bridge\\Bridge5.3ds");
	//bridge->pos.x = 14.5;
	//bridge->pos.y = -1.7;
	//bridge->pos.z = -4;
	//bridge->Materials[0].tex = m5;
	//bridge->Materials[1].tex = m5;
	//bridge->Materials[2].tex = m5;
	//bridge->Materials[3].tex = m5;
	//bridge->Materials[4].tex = m5;
	//bridge->Materials[5].tex = m5;
	//bridge->Materials[6].tex = m5;
	//bridge->rot.y = 90;
	//bridge->scale = 0.4;

	//fountain = new Model_3DS();
	//fountain->Load((char*)"3DS\\fountain\\FountainN290510.3DS");
	//fountain->scale = 0.013;

	//grass = LoadTGA((char*)"images\\grass.tga");


	//img[0]= LoadTexture((char*)"images\\greuyWhite.bmp");
	//img[1]= LoadTexture((char*)"images\\gray_dark_bricks.bmp");
	//img[2]= LoadTexture((char*)"images\\Mercurey01_c.bmp");
	//img[3]= LoadTexture((char*)"images\\face_jp_pave02.bmp");
	//img[4]= LoadTexture((char*)"images\\wall.bmp");


	////****************hotel
	//mk = new HOTEL();


	////shipp

	//ship= new Model_3DS();
	//ship->Load((char*)"3DS\\ship\\ship.3ds");
	//ship->pos.x = 30.5;
	//ship->pos.y = -1.7;
	//ship->pos.z = -10;
	//ship->scale = 0.0005;
	//ship->Materials[0].tex = m5;
	//ship->Materials[1].tex = m5;





	// Fog
	glEnable(GL_FOG);
	glFogfv(GL_FOG_COLOR, color);
	glFogf(GL_FOG_START, 20);
	glFogf(GL_FOG_END, 40);
	glFogi(GL_FOG_MODE, GL_EXP);
	//glFogf(GL_FOG_DENSITY, 0.0);



	return TRUE;										// Initialization Went OK
}
void first_built(double front_Texture) {

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, img2);

	glPushMatrix();
	glColor3ub(25, 50, 170);
	//down:
	glBegin(GL_QUADS);
	//glTexcoord2d();
	glVertex3d(0.5, -0.5, 0.5);
	//glTexcoord2d();
	glVertex3d(0.5, -0.5, -0.5);
	//glTexcoord2d();
	glVertex3d(-0.5, -0.5, -0.5);
	//glTexcoord2d();
	glVertex3d(-0.5, -0.5, 0.5);
	glEnd();
	//up
	glBegin(GL_QUADS);
	glVertex3d(0.5, 0.5, 0.5);
	glVertex3d(0.5, 0.5, -0.5);
	glVertex3d(-0.5, 0.5, -0.5);
	glVertex3d(-0.5, 0.5, 0.5);
	glEnd();

	//right
	glBegin(GL_QUADS);
	glVertex3d(0.5, 0.5, 0.5);
	glVertex3d(0.5, 0.5, -0.5);
	glVertex3d(0.5, -0.5, -0.5);
	glVertex3d(0.5, -0.5, 0.5);
	glEnd();
	//left
	glBegin(GL_QUADS);
	glVertex3d(-0.5, 0.5, 0.5);
	glVertex3d(-0.5, 0.5, -0.5);
	glVertex3d(-0.5, -0.5, -0.5);
	glVertex3d(-0.5, -0.5, 0.5);
	glEnd();
	glPopMatrix();
	glColor3d(1, 1, 1);

	//back

	glBegin(GL_QUADS);
	glTexCoord2d(0, 5);
	glVertex3d(0.5, 0.5, -0.5);
	glTexCoord2d(3, 5);
	glVertex3d(-0.5, 0.5, -0.5);
	glTexCoord2d(3, 0);
	glVertex3d(-0.5, -0.5, -0.5);
	glTexCoord2d(0, 0);
	glVertex3d(0.5, -0.5, -0.5);
	glEnd();
	//front
	int img6;
	if (front_Texture == 0) img6 = terrainImage;
	else img6 = img2;
	glBindTexture(GL_TEXTURE_2D, img6);
	glBegin(GL_QUADS);
	//«·⁄ »…
	glTexCoord2d(3, 0.5);
	glVertex3d(0.5, 0.5, 0.5);
	glTexCoord2d(0, 0.5);
	glVertex3d(-0.5, 0.5, 0.5);
	glTexCoord2d(0, 0);
	glVertex3d(-0.5, 0.1, 0.5);
	glTexCoord2d(3, 0);
	glVertex3d(0.5, 0.1, 0.5);
	//Ì„Ì‰
	glTexCoord2d(1, 0.7);
	glVertex3d(0.5, 0.1, 0.5);
	glTexCoord2d(0, 0.7);
	glVertex3d(0.1, 0.1, 0.5);//glVertex3d(0.15, 0.1, 0.5);
	glTexCoord2d(0, 0);
	glVertex3d(0.1, -0.5, 0.5);//glVertex3d(0.15, -0.5, 0.5);
	glTexCoord2d(1, 0);
	glVertex3d(0.5, -0.5, 0.5);

	glTexCoord2d(3, 5);
	glVertex3d(-0.1, 0.1, 0.5);//glVertex3d(-0.15, 0.1, 0.5);
	glTexCoord2d(0, 5);
	glVertex3d(-0.5, 0.1, 0.5);//glVertex3d(-0.5, 0.1, 0.5);
	glTexCoord2d(0, 0);
	glVertex3d(-0.5, -0.5, 0.5);//glVertex3d(-0.5, -0.5, 0.5);
	glTexCoord2d(3, 0);
	glVertex3d(-0.1, -0.5, 0.5);//glVertex3d(-0.15, -0.5, 0.5);


	glEnd();


	//glPushMatrix();
	//glRotated(90, 1, 0, 0);
	//glRotated(180, 0, 1, 0);
	//glColor3ub(0, 0, 255);
	////down:
	//glBegin(GL_QUADS);
	//glVertex3d(0.5, -0.5, 0.5);
	//glVertex3d(0.5, -0.5, -0.5);
	//glVertex3d(-0.5, -0.5, -0.5);
	//glVertex3d(-0.5, -0.5, 0.5);
	//glEnd();
	////up
	//glBegin(GL_QUADS);
	//glVertex3d(0.5, 0.5, 0.5);
	//glVertex3d(0.5, 0.5, -0.5);
	//glVertex3d(-0.5, 0.5, -0.5);
	//glVertex3d(-0.5, 0.5, 0.5);
	//glEnd();

	//
	//glBegin(GL_QUADS);
	//glVertex3d(0.5, 0.5, 0.5);
	//glVertex3d(0.5, 0.5, -0.5);
	//glVertex3d(0.5, -0.5, -0.5);
	//glVertex3d(0.5, -0.5, 0.5);
	//glEnd();
	//glPopMatrix();
	//
	//glPopMatrix();





	










}
bool open_door = false;
double x_door = 0;
void draw_door() {
	glPushMatrix();
	glTranslated(x_door, 0, 0);
	glBindTexture(GL_TEXTURE_2D, img4);
	glBegin(GL_QUADS);

	glTexCoord2d(0, 0); glVertex3d(-0.1, -0.5, 0.501);//glVertex3d(-0.15, -0.5, 0.501);
	glTexCoord2d(1, 0); glVertex3d(0.1, -0.5, 0.501);//glVertex3d(0.15, -0.5, 0.501);
	glTexCoord2d(1, 1); glVertex3d(0.1, 0.1, 0.501);//glVertex3d(0.15, 0.1, 0.501);
	glTexCoord2d(0, 1); glVertex3d(-0.1, 0.1, 0.501);//glVertex3d(-0.15, 0.1, 0.501);
	glEnd();
	glPopMatrix();
	if (open_door && x_door >= -0.3) x_door -= 0.001;
	if (!open_door && x_door < 0) x_door += 0.001;

}

void draw_windo() {
	glEnable(GL_BLEND);
	glPushAttrib(GL_CURRENT_BIT | GL_COLOR_BUFFER_BIT | GL_LIGHTING_BIT);
	glColor4f(1.0, 1.0, 1.0, 0.5);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glDepthMask(GL_FALSE);
	glBindTexture(GL_TEXTURE_2D, img3);

	glPushMatrix();
	glBegin(GL_QUADS);

	glTexCoord2d(0, 0); glVertex3d(-0.15, -0.5, 0.501);
	glTexCoord2d(0, 1); glVertex3d(0.15, -0.5, 0.501);
	glTexCoord2d(1, 1); glVertex3d(0.15, 0.1, 0.501);
	glTexCoord2d(1, 0); glVertex3d(-0.15, 0.1, 0.501);
	
	glEnd();
	glPopMatrix();

	glDepthMask(GL_TRUE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPopAttrib();
	glDisable(GL_BLEND);

}

void second_built(double xpos, double ypos, double zpos, double xsize, double ysize, double zsize, double eng, double front_Texture) {

	glPushMatrix();
	glTranslated(xpos, ypos + (0.5 * ysize), zpos);
	glScaled(xsize, ysize, zsize);
	glRotated(eng, 0, 2, 0);
	first_built(front_Texture);
	/*cat->Draw();*/
	//table->Draw();
	//table->scale = 0.01;
	/*sofa->Draw();
	cat->Draw(); cat->pos.x = 0;
	cat->pos.y = 0;
	cat->pos.z = 0;*/
	if (ypos == 0 || xsize < 2)
	{
		draw_door();

	}
	else draw_windo();

	glPopMatrix();





}


/******************************* new    ********************************/
GLfloat posX = 0.0f, posY = 0.0f, posZ = 0.0f; // for light
bool open = false, lp = false;
void Key(bool* keys, float speed)
{
	/***** Eye Direction *****/
	if (keys['S'])
		MyCamera.RotateX(-4.0 * speed);
	if (keys['W'])
		MyCamera.RotateX(4.0 * speed);
	if (keys['D'])
		MyCamera.RotateY(-4.0 * speed);
	if (keys['A'])
		MyCamera.RotateY(4.0 * speed);
	 
	/***** Camera Movemnet *****/
	if (keys[VK_UP]) { MyCamera.MoveForward(0.8 * speed); }
	if (keys[VK_DOWN]) MyCamera.MoveForward(-0.8 * speed);
	if (keys[VK_RIGHT]) MyCamera.MoveRight(0.8 * speed);
	if (keys[VK_LEFT]) MyCamera.MoveRight(-0.8 * speed);

	
	/***** Car Movemnet *****/
	if (keys['8']) // move tank forward
	{
		MyCamera.MoveUpward(0.4 * speed);
	}
	if (keys['5']) // move tank back
	{
		MyCamera.MoveUpward(-0.4 * speed);
	}
	if (keys['6']) // move tank up
	{
		car->pos.x++;
	}if (keys['4'])
	{
		car->pos.x--; // move tank down
	}

	/***** Door State *****/
	if (keys['O']) {  open_door = true; }
	if (keys['P']) { open_door = false; }


	/***** Fog Control *****/
	if (keys['F'])
		fog += 0.001f;
	if (keys['G'])
		fog -= 0.001f;
	glFogf(GL_FOG_DENSITY, fog);


	/***** Lighting Control *****/
	/*
	glLightfv(GL_LIGHT1, GL_POSITION, Lightpos);
	if (keys['J'])
		posX += 0.1f;
	if (keys['L'])
		posX -= 0.1f;
	if (keys['I'])
		posY += 0.1f;
	if (keys['K'])
		posY -= 0.1f;
	if (keys['M'])
		posZ += 0.1f;
	if (keys['N'])
		posZ -= 0.1f;

	Lightpos[0] = posX;
	Lightpos[1] = posY;
	Lightpos[2] = posZ;*/
}

void drawRoad(float x, float y, float z,
	float width, float length,
	float ar, float xr, float yr, float zr) {

	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, ROAD);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);

	glRotated(ar, xr, yr, zr);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z);
	glEnd();

	glPopMatrix();
}




GLfloat xBall = 0, zBall=0, xline=0, height = 3, time = sqrt(2 * height / 9.8);
void moveBall(float speed) {

	if (time > 0) {
		xBall =100 * time;
		height = 0.5 * 9.8 * time * time;

	}
	else
	{
		xline = xBall;

	}
	
}


/*float angle = 0;


double ex = 0;
double ey = 0;
double ez = 0;
double cx = 0;
double cy = 0;
double cz = -15;
double q = 90;
void camera()
{
	if (keys['O']) { open_door = true; }
	if (keys['P']) { open_door = false; }

	if (keys['W']) { ez -= 0.1; cz -= 0.1; }
	if (keys['S']) { ez += 0.1;  cz += 0.1; }

	if (keys['D']) { ex += 0.1; cx += 0.1; }
	if (keys['A']) { ex -= 0.1; cx -= 0.1; }

	if (keys['R']) { ey += 0.1; cy += 0.1; }
	if (keys['F']) { ey -= 0.1; cy -= 0.1; }

	if (keys['I']) { cy += 0.1; }
	if (keys['K']) { cy -= 0.1; }

	if (keys['Y']) {
		q -= 0.01;
		cx = 10 * cos(q);
		cz = -10 * sin(q);
	}
	if (keys['H']) {
		q += 0.01;
		cx = cx * cos(q);
		cz = cz * sin(q);
	}

	if (keys['L']) { cx += 0.4; }
	if (keys['J']) { cx -= 0.4; }



}*/

void rooms_add(double x,double room_number, double q, double hight, bool the_tallest_side) {
	double j;
	double k = 0;
	if (!the_tallest_side)k = 0.5;
	j = (double)(room_number / 2) - 0.5;//  j = (double)(room_number / 2) - 0.51;
	/*    do some thing with this second_built   Ÿ»Ìÿ ⁄—÷ «·’› «·«Ì”— „‰ «·€—›       */
	for (double i = j + k; i >= -j + k; i--) {
		second_built(x+5, hight, i+5, 0.7, 1, 1, q, 1);//second_built(x2, hight, i, 0.5, 1, 1, q, 1);

	}


}

void extra_built(double room_number, double hight) {
	double room_number2;
	double room_number3 = room_number;
	bool the_tallest_side = true;

	int iz1 = (int)room_number / 2;
	room_number = (double)iz1;
	if ((int)room_number3 % 2 != 0) {
		room_number2 = (double)iz1 + 1;
		the_tallest_side = false;
	}
	else
		room_number2 = (double)iz1;


	second_built(5, hight, 5, 2, 1, room_number2, 0, 0);//room_number2+0.1Ã⁄·  «·€—› œ«Œ· «·»Ì  
	double x;
	double y;
	double z;

	x = 0.65;
	z = 5;
	rooms_add(x, room_number, -90, hight, the_tallest_side);//new  //rooms_add(x, room_number, -90, 0.75, hight, the_tallest_side);
	rooms_add(-x, room_number2, 90, hight, true);//new //rooms_add(x, room_number2, 90, -0.75, hight,true);//new



}
/*********************************************         new           ****************************************/


void Draw_Skybox(float x, float y, float z, float width, float height, float length)
{
	//gluPerspective(50, 1, 0.5, 700.0);
	// Center the Skybox around the given x,y,z position
	x = x - width / 2;
	y = y - height / 2;
	z = z - length / 2;
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);

	// Draw Front side
	glBindTexture(GL_TEXTURE_2D, SKYFRONT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glEnd();

	// Draw Back side
	glBindTexture(GL_TEXTURE_2D, SKYBACK);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glEnd();

	// Draw Left side
	glBindTexture(GL_TEXTURE_2D, SKYLEFT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glEnd();

	// Draw Right side
	glBindTexture(GL_TEXTURE_2D, SKYRIGHT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glEnd();

	// Draw Up side
	glBindTexture(GL_TEXTURE_2D, SKYUP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glEnd();

	// Draw Down side
	glBindTexture(GL_TEXTURE_2D, SKYDOWN);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z);
	glEnd();

	glColor3f(1, 1, 1);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glPopMatrix();
}



/**********************************************************************************************************************/
void drawMyTerrain1(int terrainDepth,int terrainWidth,int terrainTexture,int texSStep,int texTStep, GLubyte* heightData) {

	glPushMatrix();

	glEnable(GL_TEXTURE_2D);

	glTranslatef(-terrainWidth / 2.0, 0, -terrainDepth / 2.0);
	glScaled(0.9, 0.0003, 0.9);
	glBindTexture(GL_TEXTURE_2D, terrainTexture);
	for (int i = 5; i < terrainDepth - 5; i++) {
		glBegin(GL_TRIANGLE_STRIP);
		for (int j = 5; j < terrainWidth - 5; j++) {

			glTexCoord2d(j * texSStep, i * texTStep);
			glVertex3f(j+70, heightData[j + i * terrainDepth]-10, i);

			glTexCoord2d(j * texSStep, (i + 1) * texTStep);
			glVertex3f(j+70, heightData[j + (i + 1) * terrainDepth]-10, i + 1);

			glTexCoord2d((j + 1) * texSStep, i * texTStep);
			glVertex3f(j + 1+70, heightData[(j + 1) + i * terrainDepth]-10, i);

			glTexCoord2d((j + 1) * texSStep, (i + 1) * texTStep);
			glVertex3f(j + 1+70, heightData[(j + 1) + (i + 1) * terrainDepth], i + 1);

		}
		glEnd();
	}

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

}





/**********************************************************************************************************************/


void drawMyTerrain() {

	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glRotated(90, 0, 1, 0);
		
	glTranslatef(-0.5 ,-0.09,-11.8 );
	glScaled(0.5, 0.0009, 0.5);
	glBindTexture(GL_TEXTURE_2D, terrainTexture);
	for (int i = 5; i < terrainDepth - 5; i++) {
		glBegin(GL_TRIANGLE_STRIP);
		for (int j = 5; j < terrainWidth - 5; j++) {

			glTexCoord2d(j * texSStep, i * texTStep);
			glVertex3f(j, heightData[j + i * terrainDepth]-2, i);

			glTexCoord2d(j * texSStep, (i + 1) * texTStep);
			glVertex3f(j, heightData[j + (i + 1) * terrainDepth]-2, i + 1);

			glTexCoord2d((j + 1) * texSStep, i * texTStep);
			glVertex3f(j + 1, heightData[(j + 1) + i * terrainDepth]-2, i);

			glTexCoord2d((j + 1) * texSStep, (i + 1) * texTStep);
			glVertex3f(j + 1, heightData[(j + 1) + (i + 1) * terrainDepth]-2, i + 1);

		}
		glEnd();
	}

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

}




void drawTerrain(float x, float y, float z, float width, float length) {

	// Center the Skybox around the given x,y,z position
	x = x - width / 2;
	y = y - 0 / 2;
	z = z - length / 2;
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);

	//glTranslatef(-width / 2.0, 0, -length / 2.0);
	//glScaled(0.78, 0.3, 0.66);
	//glTranslatef(0, 0,100);
	glBindTexture(GL_TEXTURE_2D, terrainImage);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z);
	glEnd();

	glPopMatrix();

}

//***********

int i = 0;
void drawUnitBuilding(int i) {
	  
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, img[i]);

	glBegin(GL_QUADS);

	//Front Face
	glNormal3f(0, 0, 1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2f(5.0f, 0.0f);
	glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2f(5.0f, 5.0f);
	glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(0.0f, 5.0f);
	glVertex3f(-0.5, 0.5, 0.5);

	//Back Face
	glNormal3f(0, 0, -1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5, -0.5, -0.5);
	glTexCoord2f(5.0f, 0.0f);
	glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(5.0f, 5.0f);
	glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2f(0.0f, 5.0f);
	glVertex3f(-0.5, 0.5, -0.5);

	//Right Face
	glNormal3f(1, 0, 0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(5.0f, 0.0f);
	glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2f(5.0f, 5.0f);
	glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(0.0f, 5.0f);
	glVertex3f(0.5, -0.5, 0.5);

	//Left Face
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5, -0.5, -0.5);
	glTexCoord2f(5.0f, 0.0f);
	glVertex3f(-0.5, 0.5, -0.5);
	glTexCoord2f(5.0f, 5.0f);
	glVertex3f(-0.5, 0.5, 0.5);
	glTexCoord2f(0.0f, 5.0f);
	glVertex3f(-0.5, -0.5, 0.5);

	//Top Face
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5, 0.5, -0.5);
	glTexCoord2f(5.0f, 0.0f);
	glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2f(5.0f, 5.0f);
	glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(0.0f, 5.0f);
	glVertex3f(-0.5, 0.5, 0.5);

	//Bottom Face
	glNormal3f(0, -1, 0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5, -0.5, -0.5);
	glTexCoord2f(5.0f, 0.0f);
	glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(5.0f, 5.0f);
	glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2f(0.0f, 5.0f);
	glVertex3f(-0.5, -0.5, 0.5);

	glEnd();

	glPopMatrix();
}

//********************

void drawDoor() {

	glBindTexture(GL_TEXTURE_2D, img4);

	glPushMatrix();
	glScaled(1, 0.4, 0.9);
	glTranslated(0, -0.75, 0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5, -0.5, -0.23);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5, 0.3, -0.23);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5, 0.3, 0.23);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5, -0.5, 0.23);
	glEnd();
	glPopMatrix();
}

void drawWindow() {

	glBindTexture(GL_TEXTURE_2D, img3);

	glScaled(1, 0.6, 0.9);

	glPushMatrix();
	glTranslated(0, 0, -0.2);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5, -0.1, -0.15);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5, 0.1, -0.15);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5, 0.1, 0.15);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5, -0.1, 0.15);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, 0.2);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5, -0.1, -0.15);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5, 0.1, -0.15);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5, 0.1, 0.15);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5, -0.1, 0.15);
	glEnd();
	glPopMatrix();

	glTranslated(0, 0.30, 0);

	glPushMatrix();
	glTranslated(0, 0, -0.2);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5, -0.1, -0.15);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5, 0.1, -0.15);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5, 0.1, 0.15);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5, -0.1, 0.15);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, 0.2);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5, -0.1, -0.15);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5, 0.1, -0.15);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5, 0.1, 0.15);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5, -0.1, 0.15);
	glEnd();
	glPopMatrix();

	glTranslated(0, 0.30, 0);

	glPushMatrix();
	glTranslated(0, 0, -0.2);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5, -0.1, -0.15);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5, 0.1, -0.15);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5, 0.1, 0.15);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5, -0.1, 0.15);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, 0.2);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5, -0.1, -0.15);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5, 0.1, -0.15);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5, 0.1, 0.15);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5, -0.1, 0.15);
	glEnd();
	glPopMatrix();
}
//************************************************

void drawGound() {
	glBegin(GL_POLYGON);
	glVertex3f(-0.5, -0.48, -0.5);
	glVertex3f(0.5, -0.48, -0.5);
	glVertex3f(0.5, -0.48, 0.5);
	glVertex3f(-0.5, -0.48, 0.5);
	glEnd();
}

void drawBuilding(float xPos, float yPos, float zPos,
	float xSize, float ySize, float zSize,
	float xRot, float yRot, float zRot,int i) {

	glPushMatrix();

	glTranslatef(xPos, yPos, zPos);
	glRotatef(xRot, 1, 0, 0);
	glRotatef(yRot, 0, 1, 0);
	glRotatef(zRot, 0, 0, 1);
	glScalef(xSize, ySize, zSize);
	drawUnitBuilding(i);
	drawDoor();
	drawGound();
	drawWindow();
	i++;
	glPopMatrix();

}

//***********************************************
struct Point {
	float x, y, z;

	Point(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
};
float RoadWidth = 0.5;

void drawERoad(Point startRoad, Point endRoad, float roadWidth, float hor ) {

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, ROAD);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3d(startRoad.x, startRoad.y, startRoad.z);
	glTexCoord2f(0.0f, 1.0f); glVertex3d(endRoad.x, endRoad.y, endRoad.z);
	glTexCoord2f(1.0f, 1.0f); glVertex3d(endRoad.x + roadWidth, endRoad.y, endRoad.z + hor);
	glTexCoord2f(1.0f, 0.0f); glVertex3d(startRoad.x + roadWidth, startRoad.y, startRoad.z + hor);
	glEnd();
	glPopMatrix();
}


void drawEnvironment(Point startingPoint, Point endArea, float areaWidth, int n, int i, int ii, int first, int end, int tre, int ground, int ang,int nn) {

	glPushMatrix();
	
	glTranslated(0, 0, i);
	if (ii == 5 || ii == 6) {
		glRotated(90, 0, 1, 0);
		glTranslated(+0.5, 0, -0.5);
	}

	if (ii == 100) {
		glRotated(ang, 0, 1, 0);
		glTranslated(2, 0, -0.5);
	}


	glBindTexture(GL_TEXTURE_2D, ground);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3d(startingPoint.x, startingPoint.y, startingPoint.z);
	glTexCoord2f(0.0f, 1.0f); glVertex3d(endArea.x, endArea.y, endArea.z);
	glTexCoord2f(1.0f, 1.0f); glVertex3d(endArea.x + areaWidth, endArea.y, endArea.z);
	glTexCoord2f(1.0f, 0.0f); glVertex3d(startingPoint.x + areaWidth, startingPoint.y, startingPoint.z);
	glEnd();

	Point tsp = Point(startingPoint.x + areaWidth, startingPoint.y, startingPoint.z);
	Point tep = Point(endArea.x + areaWidth, endArea.y, endArea.z);

	drawERoad(startingPoint, endArea, -RoadWidth, 0);

	if (n != 0)
		drawERoad(Point(startingPoint.x + areaWidth, startingPoint.y, startingPoint.z),
			Point(endArea.x + areaWidth, endArea.y, endArea.z),
			RoadWidth, 0);
	if (first == 1)
		drawERoad(startingPoint, Point(startingPoint.x + areaWidth, startingPoint.y, startingPoint.z), 0, -RoadWidth);
	


	if (ii == 44) {

		mk->drowHotel(3, 2, startingPoint.x + areaWidth / 2, 0, endArea.z + areaWidth / 2, 0.9, 0.9, 0.9, 90);


	}
	else {


		if (end == 1)
			drawERoad(endArea, Point(endArea.x + areaWidth, endArea.y, endArea.z), 0, RoadWidth);


		if (ii == 7) {
			glPushMatrix();

			glScaled(0.5, 0.5, 0.5);
			//extra_built(3, 0);
			glPopMatrix();
		}

		if (tre == 1)
		{


			tree[0]->Materials[0].tex = m1;
			tree[0]->Materials[1].tex = m2;
			tree[1]->Materials[0].tex = m1;
			tree[1]->Materials[1].tex = m1;
			tree[1]->Materials[2].tex = m1;
			tree[1]->Materials[3].tex = m1;
			tree[1]->Materials[4].tex = m2;

			int ang = 0;
			for (double i = 0.0; i < areaWidth / 2; i += 0.3)
			{

				tree[0]->pos.x = startingPoint.x + areaWidth / 2 + i * cos(ang);
				tree[0]->pos.z = endArea.z + areaWidth / 2 + i;


				tree[1]->pos.x = startingPoint.x + areaWidth / 2 + i * cos(ang);
				tree[1]->pos.z = endArea.z + areaWidth / 2 + i;

				tree[0]->Draw();
				//tree[1]->Draw();

				tree[0]->pos.x = startingPoint.x + areaWidth / 2 + i * cos(ang) * -1;
				tree[0]->pos.z = endArea.z + areaWidth / 2 + i;
				tree[1]->pos.x = startingPoint.x + areaWidth / 2 + i * cos(ang) * -1;
				tree[1]->pos.z = endArea.z + areaWidth / 2 + i;

				tree[0]->Draw();
				//tree[1]->Draw();
				ang += 20;

			}
		}
		if (ii != 6 && ii != 7)
		{
			if (ii >= 0)
			{


				house[i].pos.x = startingPoint.x + 1.3;
				house[i].pos.y = 0.1;
				house[i].pos.z = startingPoint.z - 1;
				house[i].scale = 0.15;
				house[i].Draw();

			}
			else
			{

				drawBuilding(startingPoint.x - 0.2 + areaWidth / 2 - 0.1, 0.47, endArea.z + 0.5, 0.3, 1, 0.7, 0, 0, 0, end);

				//extra_built(1, 0);
				//drawBuilding(startingPoint.x-0.2 + areaWidth / 2 , 0.47, endArea.z +0.5, 0.3, 1, 0.7, 0, 0, 0);
				if (n != 0)
					drawBuilding(startingPoint.x + areaWidth / 2 + 0.8, 0.47, endArea.z + 0.5, 0.3, 1, 0.7, 0, 180, 0, end);
			}
		}
	}
	glPopMatrix();

	/*tree[0]->Materials[0].tex = m1;
	tree[0]->Materials[1].tex = m2;
	tree[0]->pos.x = startingPoint.x + areaWidth / 2 + 5;
	tree[0]->pos.z = endArea.z + 25 + 10;

	tree[1]->Materials[0].tex = m1;
	tree[1]->Materials[1].tex = m1;
	tree[1]->Materials[2].tex = m1;
	tree[1]->Materials[3].tex = m1;
	tree[1]->Materials[4].tex = m2;
	tree[1]->pos.x = startingPoint.x + areaWidth / 2 + 5;
	tree[1]->pos.z = endArea.z + 25 - 10;

	streetLamp[0]->pos.x = startingPoint.x + areaWidth / 2 + 47;
	streetLamp[0]->pos.z = endArea.z / 2;
	streetLamp[0]->pos.y = -0.2;

	tree[0]->Draw();
	tree[1]->Draw();
	streetLamp[0]->Draw();*/

	/**
	tree[0]->Materials[0].tex = m1;
	tree[0]->Materials[1].tex = m2;
	tree[0]->pos.x = startingPoint.x + areaWidth / 2 + 5;
	tree[0]->pos.z = endArea.z + 25 + 10;

	tree[1]->Materials[0].tex = m1;
	tree[1]->Materials[1].tex = m1;
	tree[1]->Materials[2].tex = m1;
	tree[1]->Materials[3].tex = m1;
	tree[1]->Materials[4].tex = m2;
	tree[1]->pos.x = startingPoint.x + areaWidth / 2 + 5;
	tree[1]->pos.z = endArea.z + 25 - 10;

	tree[0]->Draw();
	tree[1]->Draw();*/
}


void bb(int total ,int ang) {

	int m = 2.98;
	int m3 = 2.98, mm3 = total / 2, n3 = mm3, ii3 = 0, nnn3 = 0, oo3 = 1;
	for (int i = 1; i < mm3; i++)
	{

		if (n3 / 2 >= 0 && n3 != 0)
		{
			drawEnvironment(Point(0 - 1 * oo3, 0, nnn3), Point(0 - 1 * oo3, 0, nnn3 - 2), 2, 0, 0, 100, 0, 0, 0, ground,ang,0);


			if (n3 / 2 == 0)
				n3--;
			else n3 -= 2;
		}

		nnn3 += -2;
		ii3--;

	}




}


void dd(int h, int total,int nn  ) {


	glTranslated(h, 0, 0);
	bool a = false;
		int m = 2.98, mm = total / 2, n = mm + 2, ii = 0, nnn = 0, oo = 1, first = 1, end = 0;
	// 1/2- 4 OR 3
	for (int i = 1; i < mm-15; i++) {

		//if (total%2!=0) { mm -= 1; }
		if (n / 2 >= 0 && n != 0) {
			drawEnvironment(Point(0 - 1 * oo, 0, nnn), Point(0 - 1 * oo, 0, nnn - 2), 2, n / 2, i, ii, first, end, 0, ground, 0,nn);

			if (n / 2 == 0)
				n--;
			else n -= 2;

		}


		if (n / 2 >= 0 && n != 0) {
			drawEnvironment(Point(m * oo, 0, nnn), Point(m * oo, 0, nnn - 2), 2, n / 2, i, ii, first, end, 0, ground, 0,0);

			if (n / 2 == 0)
				n--;
			else n = n - 2;


		}
		if (n == 0 && a == 0)
		{
			//mm -= 20;

			a = true;
		}
		if (a) {

			drawEnvironment(Point(0 - 1 * oo, 0, nnn), Point(0 - 1 * oo, 0, nnn - 2), 2, 1, i, 7, 0, 0, 0, ground, 0,0);

			drawEnvironment(Point(m * oo, 0, nnn), Point(m * oo, 0, nnn - 2), 2, 1, i, 7, 0, 0, 0, ground, 0,0);

		}
	


		//if (n ==1) { end = 1; }
		nnn += -2;
		ii--;
		first = 5;
		end++;
		if (end > 4)
			end = 0;
	}
	if(nn!=0) 
		mk->drowHotel(baseBuildingRooms, baseBuildingFloors, 1.3 + 6, 0, -1, 0.5, 0.5, 0.5, -90);
	//drawEnvironment(Point(0, 0, nnn+20), Point(0 , 0, nnn+30), 30, 1, i, 555, 0, 0, 0,sandGround, 0, 0);


	//bb(10, 180);

	




}


void buildCity(int total,int nn) {



	int	m = 2.98, mm = total / 2, n = mm + 2, ii = 0, nnn = 0, oo = 1, first = 1, end = 0;

	dd(0, total,nn);



	//  1/4 total

	int m2 = 2.98, mm2 = total / 4, n2 = mm2, ii2 = 0, nnn2 = 0, oo2 = 1;
	for (int i = 1; i < mm2; i++)
	{

		if (n2 / 2 >= 0 && n2 != 0)
		{
			drawEnvironment(Point(0 - 1 * oo2, 0, nnn2), Point(0 - 1 * oo2, 0, nnn2 - 2), 2, 0, 0, 5, 0, 0, 0, ground, 0,nn);
			if (n2 / 2 == 0) {
				n2--;
				nn--;
			}
			else {
				n2 -= 2; nn--;
			}

		}

		nnn2 += -2;
		ii2--;

	}

	int m3 = 2.98, mm3 = total / 8, n3 = mm3, ii3 = 0, nnn3 = 0, oo3 = 1;
	for (int i = 1; i < mm3; i++)
	{

		if (n3 / 2 >= 0 && n3 != 0)
		{
			drawEnvironment(Point(0 - 1 * oo3, 0, nnn3), Point(0 - 1 * oo3, 0, nnn3 - 2), 2, 0, 0, 100, 0, 0, 0,ground, -90,nn);


			if (n3 / 2 == 0) {
				n2--; nn--;
			}
			else { n3 -= 2; nn--; }
		}

		nnn3 += -2;
		ii3--;

	}



	bridge->Draw();

	bb(total / 4, -180);


	
	//sea
	drawMyRiver();
	//car->Draw();
}


void NightMode() {
	glEnable(GL_LIGHTING); // Enable lighting
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiff);
	glEnable(GL_LIGHT1);
	M3DVector4f vPlaneEquation;
	m3dGetPlaneEquation(vPlaneEquation, points[0], points[1], points[2]);
	m3dMakePlanarShadowMatrix(shadowMat, vPlaneEquation, lightPos);
}



int w = 1000, h = 1000, l = 1000;
int nn = 1;
float angle = 0.0f;
void DrawGLScene(GLvoid) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, 1.333, 0.008, 10000.0);
	// Reset The Current Modelview Matrix

	gluLookAt(0, 0, 0, 0, 0, -100, 0, 1, 0);
	//glTranslated(0, 0, -15);

	/*********** Camera ***********/
	MyCamera.Render();
	MyCamera.Position.y = (float)((int)(MyCamera.Position.x + TerrainSize / 2.0), (int)(MyCamera.Position.z + TerrainSize / 2.0)) * scaley;

	/*********** Keyboard Control ***********/
	Key(keys, 0.09);

	/*********** Skybox ***********/
	Draw_Skybox(0, 0, 0, w, h, l);

	glColor3f(0, 0, 0);

	/*********** ball ***********/
	glPushMatrix();
	glTranslated(xBall, height, 1);
	glColor3f(1, 0, 0);

	auxSolidSphere(3);
	glColor3f(0, 0, 0);
	glPopMatrix();

	if (open_door) {
		moveBall(10);
		time -= 0.0005;
	}
	if (time <= 0) {
		glBegin(GL_LINES);
		glColor3f(1, 1, 0);
		glLineWidth(500);
		glVertex2d(0, 30);
		glVertex2d(xline, 0);
		glColor3f(0, 0, 0);
		glEnd();
	}


//	mk->camera();
//
//
//	/*********** Draw Base Ground ***********/
//	//drawTerrain(0, 0, 0, w, l);
//
//
//	//extra_built(3, 0);
//	bool a = false;
//	int total = buildingNum;
//
//
//	if (total <= 100)
//		buildCity(total, 1);
//
//
//	if (angle <= (15.0f * 3.14f / 2))
//		angle += 0.001f;
//
//	//	float x = 2.0f * cos(angle);
//	//	float y = 2.0f * sin(angle);
//
//
//	for (int i = 1; i < shipsNum; i++){
//
//		ship->pos.x = -40.5 * cos(angle)+i*2;
//	ship->pos.y = -1.7;
//	ship->pos.z = -20 * sin(angle);
//	//ship->scale = 0.0005;
//
//	ship->Draw();
//}
//	
//	//ship->scale = 0.0005;
//
//
//
//	//------------------park------------------------------- 
//	drawEnvironment(Point(1.3, 0, -1), Point(1.3, 0, -11), 10, 0, 0, 6, 0, 0, 1, ground, 0, 0);
//	drawMyTerrain();
//
//	//drawEnvironment(Point(5, 0, -5), Point(5, 0, -10), 10, 0, 0, 6, 0, 0, 0, grassGround, 0);
//
//
//
//	//s
//	//drawMyTerrain1(25,25,sandGround,1/25,1/25,heightData1);
//		
//
//	    dd(40, total / 2,0);
//		glRotated(180, 0, 1, 0);
	//drawEnvironment(Point(1.3, 0, -1), Point(1.3, 0, -11), 10, 0, 0, 6, 0, 0, 1, grassGround, 0,0);



	//------------------river----------------------------------------------------

	//drawEnvironment(Point(1.3, 0, -1), Point(1.3, 0, -11), 10, 0, 0, 6, 0, 0, 1);
	
	/**
	stair->Draw();
	house->Draw();
	sofa->Draw();
	table->Draw();
	garbage->Draw();
	cat->Draw();


	/*****************************new  *********************************/
/*
	//glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, img1);
	glColor3ub(255, 255, 255);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3d(-20, 0, 20);
	glTexCoord2d(10, 0);
	glVertex3d(20, 0, 20);
	glTexCoord2d(10, 10);
	glVertex3d(20, 0, -20);
	glTexCoord2d(0, 10);
	glVertex3d(-20, 0, -20);
	glEnd();
	*/

	/*glBindTexture(GL_TEXTURE_2D, img3);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 1);
	glVertex3d(-2, 4, 2);
	glTexCoord2d(1, 1);
	glVertex3d(-2, 4, 6);
	glTexCoord2d(1, 0);
	glVertex3d(-2, 1, 6);
	glTexCoord2d(0, 0);
	glVertex3d(-2, 1, 2);

	glVertex3d(2, 4, 2);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);   glVertex3d(2, 1, 2);
	glTexCoord2d(1, 0);   glVertex3d(2, 4, 2);
	glTexCoord2d(1, 1);   glVertex3d(2, 4, 6);
	glTexCoord2d(0, 1);   glVertex3d(2, 1, 6);


	glEnd();
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5, -0.1, -0.15);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5, 0.1, -0.15);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5, 0.1, 0.15);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5, -0.1, 0.15);


	glEnd();*/

	if (turnMode == 0) {
		NightMode();
	}


	glFlush();											// Done Drawing The Quad	

	//DO NOT REMOVE THIS
	SwapBuffers(hDC);
}


GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL, 0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL, NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd, hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL", hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*
 *	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
 *	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/

BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;			// Set Left Value To 0
	WindowRect.right = (long)width;		// Set Right Value To Requested Width
	WindowRect.top = (long)0;				// Set Top Value To 0
	WindowRect.bottom = (long)height;		// Set Bottom Value To Requested Height

	fullscreen = fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance = GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = (WNDPROC)WndProc;					// WndProc Handles Messages
	wc.cbClsExtra = 0;									// No Extra Window Data
	wc.cbWndExtra = 0;									// No Extra Window Data
	wc.hInstance = hInstance;							// Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground = NULL;									// No Background Required For GL
	wc.lpszMenuName = NULL;									// We Don't Want A Menu
	wc.lpszClassName = "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth = width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight = height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel = bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", "NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle = WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle = WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle = WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd = CreateWindowEx(dwExStyle,							// Extended Style For The Window
		"OpenGL",							// Class Name
		"fffff",								// Window Title
		dwStyle |							// Defined Window Style
		WS_CLIPSIBLINGS |					// Required Window Style
		WS_CLIPCHILDREN,					// Required Window Style
		0, 0,								// Window Position
		WindowRect.right - WindowRect.left,	// Calculate Window Width
		WindowRect.bottom - WindowRect.top,	// Calculate Window Height
		NULL,								// No Parent Window
		NULL,								// No Menu
		hInstance,							// Instance
		NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(hDC = GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC = wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!wglMakeCurrent(hDC, hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd, SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}

LRESULT CALLBACK WndProc(HWND	hWnd,			// Handle For This Window
	UINT	uMsg,			// Message For This Window
	WPARAM	wParam,			// Additional Message Information
	LPARAM	lParam)			// Additional Message Information
{
	static PAINTSTRUCT ps;

	switch (uMsg)									// Check For Windows Messages
	{
	case WM_PAINT:
		DrawGLScene();
		BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		return 0;

	case WM_TIMER:
		DrawGLScene();
		return 0;

	case WM_ACTIVATE:							// Watch For Window Activate Message
	{
		if (!HIWORD(wParam))					// Check Minimization State
		{
			active = TRUE;						// Program Is Active
		}
		else
		{
			active = FALSE;						// Program Is No Longer Active
		}

		return 0;								// Return To The Message Loop
	}

	case WM_SYSCOMMAND:							// Intercept System Commands
	{
		switch (wParam)							// Check System Calls
		{
		case SC_SCREENSAVE:					// Screensaver Trying To Start?
		case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
			return 0;							// Prevent From Happening
		}
		break;									// Exit
	}

	case WM_CLOSE:								// Did We Receive A Close Message?
	{
		PostQuitMessage(0);						// Send A Quit Message
		return 0;								// Jump Back
	}

	case WM_KEYDOWN:							// Is A Key Being Held Down?
	{
		keys[wParam] = TRUE;					// If So, Mark It As TRUE
		return 0;								// Jump Back
	}

	case WM_KEYUP:								// Has A Key Been Released?
	{
		keys[wParam] = FALSE;					// If So, Mark It As FALSE
		return 0;								// Jump Back
	}

	case WM_SIZE:								// Resize The OpenGL Window
	{
		ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));  // LoWord=Width, HiWord=Height
		return 0;								// Jump Back
	}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE	hInstance,			// Instance
	HINSTANCE	hPrevInstance,		// Previous Instance
	LPSTR		lpCmdLine,			// Command Line Parameters
	int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done = FALSE;								// Bool Variable To Exit Loop

	// Ask The User Which Screen Mode They Prefer
	//if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen = FALSE;							// Windowed Mode
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow((char*)"Madhat NeHe Template", 640, 480, 16, fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}


	//Set drawing timer to 20 frame per second
	UINT timer = SetTimer(hWnd, 0, 50, (TIMERPROC)NULL);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;

}

int choiceGround;
int main(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	cout << "*********** Basic Environment Component ***********" << endl;
	cout << "Enter num of trees : ";
	cin >> treesNum;

	cout << "Enter num of Buildings : ";
	cin >> buildingNum;

	/*cout << "Enter num of Cars : ";
	cin >> carsNum;*/

	cout << "Enter num of ships : ";
	cin >> shipsNum;

	
	cout << "-------------------------------------------------------" << endl;
	cout << "*********** Ground Type ***********" << endl;
	cout << "1. Grass " << endl;
	cout << "2. Sand " << endl;
	cout << "Your Choice: ";
	cin >> choiceGround;
	switch (choiceGround) {
		case 1:
			ground = grassGround;
			break;
		case 2:
			ground = sandGround;
			break;
	}

	cout << "-------------------------------------------------------" << endl;
	cout << "*********** Base Building Info ***********" << endl;
	cout << "Enter num of base Building Floors : ";
	cin >> baseBuildingFloors;

	cout << "Enter num of base Building Rooms : ";
	cin >> baseBuildingRooms;

	cout << "(0) for Night Mode / (1) for Light Mode : ";
	cin >> turnMode;


	return WinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}