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

//���� ������ ��ü ������Ʈ ����
unsigned int ids[17];
AUX_RGBImageRec *tex[17]; /* structure to contain a texture image */
GLUquadric *sphere;
/*�ؽ��� ����*/
/* ��ֹ� 15�� 3x5*/
/* star 1��*/
/* Ʈ���޸� 1��*/

//����� ��� ���� ����
int view_x = 0;
int view_y = -70;
int view_z = 1;
//ī�޶� �����ǵ�


/*��ü�� �̵�*/
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


/* Star �� ��ֹ� 1, 2, 3�� ǥ���ϱ� ���� ������ ������*/
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

int D3 = 1;//�ʱ⿡�� 3D�� ���δ�. //���� �� ���� 0�� �Ǹ� 2D�� ���� �Ѵٴ°�

int bounce = 0; //���� bounce�� 1�� �ȴٸ� Ƣ������� ���·� ����� �ָ� �ȴ�. ó������ �ϰ��ϴ� ���±� ������ bounce�� 0�̴�.
double move_speed = 0.004; //������ �ӵ��� �������� �����ȴ�. �߷� ���ӵ��� �������־�� �Ѵ�.
double jump_height = 10; //�ʱ⿡�� 10�̴ٰ� ���� Ʈ���޸��� �� ������ �Ÿ��� �þ

double move_star_x = 0;
double move_star_y = 0;
double move_star_z = 0;

void crash();
void star_move();//���� �Ϸ�
void display();
void keyboard(unsigned char key, int x, int y);
void reshape(int w, int h);
//����� ��� ������ ��

//Ű���� �Լ� (�̰� ��ü�� �̵����� �����ϰ� ��������� �Ѵ�
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
		//2D�� ��� ���� ó���������
	}
	
	/* �߿�!! ������ �̵��� �� �ִ� ���������� �̵��Ͽ��� ��! �̰��� �������� ������ ��ü�� ������� ���� �߻�!*/
}
void crash() {
	//�� ��ü�� �߽ɰ� 3���� �Ÿ��� ���� �� ��ü�� �������� �պ��� ������ �浹�� �Ǻ��ϴ� ��
}

void star_move() {

	if (bounce == 0) {
		if (move_star_z > -18) {
			move_star_z -= move_speed; //�ӵ��� �����ϴٰ� Ư�� ��ġ�� ���� 0���� ������� �ٽ� Ƣ�� ������ �Ѵ�.
			move_speed += 0.00005;
		}
		else {
			move_speed = INIT_MOVESPEED;
			Sleep(100);
			bounce = 1;
		}
	}
	else {//Ƣ�� ������ ���·� ��ȭ ���� ��, �� bounce�� 1�� ��
		if (move_star_z < jump_height) {
			if (jump_height == 200) {
				//Ŭ���� ����
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
	//������ ����


	//������ ��


	//�� ����
	glPushMatrix();
	glEnable(GL_LIGHTING);  //Lighting�� �����
	glEnable(GL_LIGHT0); //Light 0�� ����� (0��° ����)
	glEnable(GL_TEXTURE_2D); //�ؽ��ĸ� �����
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);



	GLfloat emission_light[] = { 1.0, 1.0, 0.3, 1.0 }; //������� �ݻ�
	glMaterialfv(GL_FRONT, GL_EMISSION, emission_light);

	glTranslatef(0+move_star_x, 10+move_star_y, move_star_z);
	glBindTexture(GL_TEXTURE_2D, ids[0]);
	gluSphere(sphere, 3, 100, 100);

	glPopMatrix();
	//���� ��

	//Ʈ���޸� ����
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular1);
	glMaterialf(GL_FRONT, GL_SHININESS, shine);

	GLfloat emission_material[] = { 0.0, 0.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_EMISSION, emission_material);
	glTranslatef(0, 0, -15);
	glBindTexture(GL_TEXTURE_2D, ids[1]);
	GLUquadricObj *donut = gluNewQuadric(); //�̰��� ��
	gluDisk(donut, 0.2, 50, 100, 20);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient3);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse3);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular1);

	glMaterialfv(GL_FRONT, GL_EMISSION, emission_material);
	glTranslatef(0, 8, -25);
	GLUquadricObj *foot = gluNewQuadric(); //�̰��� �ٸ�
	gluCylinder(foot, 2, 2, 10, 20, 5);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(6, 0, -25);
	GLUquadricObj *foot2 = gluNewQuadric(); //�̰��� �ٸ�
	gluCylinder(foot2, 2, 2, 10, 20, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-6, 0, -25);
	GLUquadricObj *foot3 = gluNewQuadric(); //�̰��� �ٸ�
	gluCylinder(foot3, 2, 2, 10, 20, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -6, -25);
	GLUquadricObj *foot4 = gluNewQuadric(); //�̰��� �ٸ�
	gluCylinder(foot4, 2, 2, 10, 20, 5);
	glPopMatrix();
	//Ʈ���޸� ��

	//�༺ ���� (��ֹ�)
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
	//�༺ ��


/*	
    GLUquadricObj *donut = gluNewQuadric(); //�̰��� ��
	gluDisk(donut, 1.0, 1.5, 100, 40);
*/

	/*�ؽ��� */
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
	glutInitWindowSize(1280, 720);//��� �� ������ ������
	glutCreateWindow("5D Star");

	/*�ؽ��� �߰�*/
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
	// �߰� ����
	sphere = gluNewQuadric();
	gluQuadricTexture(sphere, GL_TRUE);

	//Star �ؽ���
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
	/*�ؽ��� �߰�*/

	//Ʈ���޸� �ؽ���
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
	/*�ؽ��� �߰�*/

	//��ֹ� 1 �ؽ���
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
	/*�ؽ��� �߰�*/

	//��ֹ� 2 �ؽ���
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

	
	//��ֹ� 3 �ؽ���
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
	

	glClearColor(0, 1, 1, 0); //���� ���� G+B
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	star_move();
	glutIdleFunc(display);//Idle�ð��� ����ؼ� �۵��ϴ� �Լ�
	glutKeyboardFunc(keyboard);

	glutMainLoop();
}