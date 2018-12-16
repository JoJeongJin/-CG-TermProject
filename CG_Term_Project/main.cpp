/*
201402436_JoJeongJin
*/
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <glut.h>
#include <glu.h> 
#include <glaux.h>
#pragma comment(lib, "glaux.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")
#define INIT_MOVESPEED 0.004

using namespace std;

//전역 변수로 입체 오브젝트 생성
unsigned int ids[17];
AUX_RGBImageRec *tex[17]; /* structure to contain a texture image */
GLUquadric *sphere;
/*텍스쳐 관련*/
/* 장애물 15개 3x5*/
/* star 1개*/
/* 트램펄린 1개*/

//사용할 모든 변수 모음
int view_x = 0;
int view_y = -70;
int view_z = 1;
//카메라 포지션들


/*물체의 이동*/
double star = 0;
double planet_1 = 0;
double planet_2 = 0;
double planet_3 = 0;
double planet_4 = 0;
double planet_5 = 0;

double planet_6 = 0;
double planet_7 = 0;
double planet_8 = 0;
double planet_9 = 0;
double planet_10= 0;

double planet_11= 0;
double planet_12= 0;
double planet_13= 0;
double planet_14= 0;
double planet_15= 0;


/* Star 및 장애물 1, 2, 3을 표현하기 위해 정의한 변수들*/
GLfloat ambient0[] = { 0.2, 0.0, 0.0, 1.0 };
GLfloat diffuse0[] = { 1.0, 0.9, 0.6, 1.0 };
GLfloat specular0[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light0_pos[] = { 0.0, 0.0, 0.0, 1.0 };

GLfloat ambient1[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat diffuse1[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat specular1[] = { 0.2, 0.4, 0.7, 1.0 };

GLfloat ambient2[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat diffuse2[] = { 0.8, 0.8, 0.3, 1.0 };
GLfloat specular2[] = { 0.1, 0.2, 0.3, 1.0 };

GLfloat ambient3[] = { 0.0, 0.8, 0.1, 1.0 };
GLfloat diffuse3[] = { 0.3, 0.4, 0.9, 1.0 };
GLfloat specular3[] = { 0.1, 0.2, 0.3, 1.0 };

GLfloat shine = 100.0;

int D3 = 1;//초기에는 3D로 보인다. //만약 이 값이 0이 되면 2D로 게임 한다는것

int bounce = 0; //만약 bounce가 1이 된다면 튀어오르는 상태로 만들어 주면 된다. 처음에는 하강하는 상태기 때문에 bounce는 0이다.
double move_speed = 0.004; //움직임 속도는 이정도로 고정된다. 중력 가속도를 구현해주어야 한다.
double jump_height = 10; //초기에는 10이다가 점점 트램펄린을 뛸 때마다 거리가 늘어남

double move_star_x = 0;
double move_star_y = 0;
double move_star_z = 0;

void crash();
void star_move();//구현 완료
void display();
void keyboard(unsigned char key, int x, int y);
void reshape(int w, int h);
//사용할 모든 변수의 끝

//키보드 함수 (이건 물체의 이동에만 관여하게 수정해줘야 한다
void keyboard(unsigned char key, int x, int y) {
	if (D3 == 1) {
		if (key == 'q') {
			view_z += 1; //zoom in
		}
		else if (key == 'e') {
			view_z -= 1; // zoom out
		}
		else if (key == 'd') {
			move_star_x+=0.5;
		}
		else if (key == 's') {
			move_star_y-=1;
		}
		else if (key == 'a') {
			move_star_x-=0.5;
		}
		else if (key == 'w') {
			move_star_y+=1;
		}
		else if (key == '2') {
			view_x = 0;
			view_y = -70;
			view_z = 1;
		}
	}
	else {
		//2D의 경우 따로 처리해줘야함
	}
	
	/* 중요!! 무조건 이동할 수 있는 범위내에서 이동하여야 함! 이것을 정해주지 않으면 물체가 사라지는 현상 발생!*/
}
void crash() {
	//두 물체의 중심간 3차원 거리의 합이 두 물체의 반지름의 합보다 작으면 충돌로 판별하는 것
}

void star_move() {

	if (bounce == 0) {
		if (move_star_z > -18) {
			move_star_z -= move_speed; //속도가 증가하다가 특정 위치에 오면 0으로 만든다음 다시 튀어 오르게 한다.
			move_speed += 0.00005;
		}
		else {
			move_speed = INIT_MOVESPEED;
			Sleep(100);
			bounce = 1;
		}
	}
	else {//튀어 오르는 상태로 변화 했을 때, 즉 bounce가 1일 때
		if (move_star_z < jump_height) {
			if (jump_height == 200) {
				//클리어 조건
			}
			move_star_z += move_speed;
			move_speed += 0.00005;
		}
		else {
			jump_height += 10;
			move_speed = INIT_MOVESPEED;
			Sleep(200);
			bounce = 0;
		}
	}

}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(view_x, view_y, view_z, 0, 0, 0, 0, 1, 0);
	star_move();
	//연산의 시작


	//연산의 끝


	//별 정의
	glPushMatrix();
	glEnable(GL_LIGHTING);  //Lighting을 사용함
	glEnable(GL_LIGHT0); //Light 0를 사용함 (0번째 조명)
	glEnable(GL_TEXTURE_2D); //텍스쳐를 사용함
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);



	GLfloat emission_light[] = { 1.0, 1.0, 0.3, 1.0 }; //노란색을 반사
	glMaterialfv(GL_FRONT, GL_EMISSION, emission_light);

	glTranslatef(0+move_star_x, 10+move_star_y, move_star_z);
	glBindTexture(GL_TEXTURE_2D, ids[0]);
	gluSphere(sphere, 3, 100, 100);

	glPopMatrix();
	//별의 끝

	//트램펄린 정의
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular1);
	glMaterialf(GL_FRONT, GL_SHININESS, shine);

	GLfloat emission_material[] = { 0.0, 0.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_EMISSION, emission_material);
	glTranslatef(0, 0, -15);
	glBindTexture(GL_TEXTURE_2D, ids[1]);
	GLUquadricObj *donut = gluNewQuadric(); //이것이 고리
	gluDisk(donut, 0.2, 50, 100, 20);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient3);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse3);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular1);

	glMaterialfv(GL_FRONT, GL_EMISSION, emission_material);
	glTranslatef(0, 8, -25);
	GLUquadricObj *foot = gluNewQuadric(); //이것이 다리
	gluCylinder(foot, 2, 2, 10, 20, 5);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(6, 0, -25);
	GLUquadricObj *foot2 = gluNewQuadric(); //이것이 다리
	gluCylinder(foot2, 2, 2, 10, 20, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-6, 0, -25);
	GLUquadricObj *foot3 = gluNewQuadric(); //이것이 다리
	gluCylinder(foot3, 2, 2, 10, 20, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -6, -25);
	GLUquadricObj *foot4 = gluNewQuadric(); //이것이 다리
	gluCylinder(foot4, 2, 2, 10, 20, 5);
	glPopMatrix();
	//트램펄린 끝

	//행성 정의 (장애물)
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular1);
	glMaterialf(GL_FRONT, GL_SHININESS, shine);

	glMaterialfv(GL_FRONT, GL_EMISSION, emission_material);
	glTranslatef(30, 20, 0);
	glBindTexture(GL_TEXTURE_2D, ids[2]);
	gluSphere(sphere, 3, 100, 100);

	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular1);
	glMaterialf(GL_FRONT, GL_SHININESS, shine);

	glMaterialfv(GL_FRONT, GL_EMISSION, emission_material);
	glTranslatef(-30, 30, 0);
	glBindTexture(GL_TEXTURE_2D, ids[2]);
	gluSphere(sphere, 3, 100, 100);

	glPopMatrix();
	//행성 끝


/*	
    GLUquadricObj *donut = gluNewQuadric(); //이것이 고리
	gluDisk(donut, 1.0, 1.5, 100, 40);
*/

	/*텍스쳐 */
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glFlush();
}

void reshape(int w, int h) {
	float ratio = w / (float)h;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, ratio, 10, 100);
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1280, 720);//띄울 때 윈도우 사이즈
	glutCreateWindow("5D Star");

	/*텍스쳐 추가*/
	// in init of main after create window
	/* Auto-generation of texture coordinates */
	GLfloat plane_coef_s[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat plane_coef_t[] = { 0.0, 1.0, 0.0, 1.0 };
	/* Define generation of s-coordinate */
	glEnable(GL_TEXTURE_GEN_S);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGenfv(GL_S, GL_OBJECT_PLANE, plane_coef_s);
	/* Define generation of t-coordinate */
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGenfv(GL_T, GL_OBJECT_PLANE, plane_coef_t);
	// 추가 사항
	sphere = gluNewQuadric();
	gluQuadricTexture(sphere, GL_TRUE);

	//Star 텍스쳐
	tex[0] = auxDIBImageLoad("star.bmp");
	glGenTextures(2, &ids[0]); /* generate texture id */
	glBindTexture(GL_TEXTURE_2D, ids[0]); /* specify tex_id to bind properties to */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); /* define how
	to map the texture */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, tex[0]->sizeX, tex[0]->sizeY, 0, GL_RGB,
		GL_UNSIGNED_BYTE, tex[0]->data); /* give the texture image to be used */
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); /* define texture
	blend mode */
	/*텍스쳐 추가*/

	//트램펄린 텍스쳐
	tex[1] = auxDIBImageLoad("tram.bmp");
	glGenTextures(3, &ids[1]); /* generate texture id */
	glBindTexture(GL_TEXTURE_2D, ids[1]); /* specify tex_id to bind properties to */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); /* define how
	to map the texture */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, tex[1]->sizeX, tex[1]->sizeY, 0, GL_RGB,
		GL_UNSIGNED_BYTE, tex[1]->data); /* give the texture image to be used */
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); /* define texture
	blend mode */
	/*텍스쳐 추가*/

	//장애물 1 텍스쳐
	tex[2] = auxDIBImageLoad("planet_1.bmp");
	glGenTextures(3, &ids[2]); /* generate texture id */
	glBindTexture(GL_TEXTURE_2D, ids[2]); /* specify tex_id to bind properties to */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); /* define how
	to map the texture */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, tex[2]->sizeX, tex[2]->sizeY, 0, GL_RGB,
		GL_UNSIGNED_BYTE, tex[2]->data); /* give the texture image to be used */
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); /* define texture
	blend mode */
	/*텍스쳐 추가*/

	//장애물 2 텍스쳐
	/*
	tex[3] = auxDIBImageLoad("planet_2.png");
	glGenTextures(3, &ids[3]); 
	glBindTexture(GL_TEXTURE_2D, ids[3]); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, tex[3]->sizeX, tex[3]->sizeY, 0, GL_RGB,
		GL_UNSIGNED_BYTE, tex[3]->data); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
	*/

	
	//장애물 3 텍스쳐
	/*
	tex[4] = auxDIBImageLoad("planet_3.png");
	glGenTextures(3, &ids[4]); 
	glBindTexture(GL_TEXTURE_2D, ids[4]); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, tex[4]->sizeX, tex[4]->sizeY, 0, GL_RGB,
		GL_UNSIGNED_BYTE, tex[4]->data); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
    */
	

	glClearColor(0, 1, 1, 0); //배경색 지정 G+B
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	star_move();
	glutIdleFunc(display);//Idle시간에 계속해서 작동하는 함수
	glutKeyboardFunc(keyboard);

	glutMainLoop();
}