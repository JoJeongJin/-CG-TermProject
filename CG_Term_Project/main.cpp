/*
201402436_JoJeongJin
*/
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <glut.h>
#include <glu.h> 
#include <glaux.h>
#include <math.h>
#pragma comment(lib, "glaux.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")

#define INIT_MOVESPEED 0.004
#define CLEAR_HEIGHT 200
#define GRAVITY 0.0005

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
int view_z = 7;
//ī�޶� �����ǵ�


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


int bounce = 0; //���� bounce�� 1�� �ȴٸ� Ƣ������� ���·� ����� �ָ� �ȴ�. ó������ �ϰ��ϴ� ���±� ������ bounce�� 0�̴�.
double move_speed = 0.008; //������ �ӵ��� �������� �����ȴ�. �߷� ���ӵ��� �������־�� �Ѵ�.
double jump_height = 10; //�ʱ⿡�� 10�̴ٰ� ���� Ʈ���޸��� �� ������ �Ÿ��� �þ

double move_star_x = 0;
double move_star_y = 0;
double move_star_z = 0;

double ob_x[10] = {-30, 30, -20, 20, -10, 10, -5, 5 , 0, 0 }; //10���� ��ֹ� x��ġ �� ����
double ob_y[10] = { 10, 9 ,8, 7, 6, 5, 4, 3, 2, 1 }; //10���� ��ֹ� y��ġ �� ����
double ob_z[10] = { 10, 30, 50, 70, 90, 110, 130 , 150, 170, 190 };//10���� ��ֹ� z��ġ �� ����
int go_left_x[10] = { 0,1,0,1,0,1,0,1,0,1 }; //1�̸� �������� ���� ���̰� 0�̸� ���������� ���� �ִ� ��
int go_bottom_y[10] = { 0,1,0,1,0,1,0,1,0,1 }; //1�̸� �Ʒ������� ���� ���̰� 0�̸� �������� ���� �ִٴ� ��

double move_planet_speed = 0.05;//�� �ӵ��� �ʱ�ȭ


void crash();
void move_planet();
void star_move();//���� �Ϸ�
void display();
void keyboard(unsigned char key, int x, int y);//�����Ϸ�
void reshape(int w, int h);//���� �Ϸ�
//����� ��� ������ ��

//Ű���� �Լ� (�̰� ��ü�� �̵����� �����ϰ� ��������� �Ѵ�
void keyboard(unsigned char key, int x, int y) {
		if (key == 'd') {
			if (move_star_x <= 25) 
			move_star_x+=1;
		}
		else if (key == 's') {
			if (move_star_y >= -15) 
			move_star_y-=1;
		}
		else if (key == 'a') {
			if (move_star_x >= -25) 
			move_star_x-=1;
		}
		else if (key == 'w') {
			if (move_star_y <= 15) 
			move_star_y+=1;
		}
		else if (key == '2') { //2D�� ���
			view_x = 0;
			view_y = 1;
			view_z = 100;
		}
		else if (key == '1') {//3D�� ���
			view_x = 0;
			view_y = -70;
			view_z = 7;
		}
	}
			


void crash() {
	for (int i = 0; i < 10; i++) {
		if ( ((fabs(5-ob_z[i]+move_star_z)) <= 6 )) { //���� ���̰� ������ �̳��� ��������
			double x = (ob_x[i] - move_star_x) * (ob_x[i] - move_star_x);
			double y = (ob_y[i] - move_star_y) * (ob_y[i] - move_star_y);
			double z = (ob_z[i] - move_star_z - 5) * (ob_z[i] - move_star_z - 5);
			double distance = (x + y + z);
			if (distance <= 32) {
				MessageBox(NULL, "��! Ż���ϴ� ���� �浹�� �߻��Ͽ����ϴ�... ���� �ڿ� �༺���� ���������ڿ� �ٽ� Ż���� �õ��غ���.", "�浹 �߻�!", MB_OK);
				exit(0);
			}
		}
	}
	//�� ��ü�� �߽ɰ� 3���� �Ÿ��� ���� �� ��ü�� �������� �պ��� ������ �浹�� �Ǻ��ϴ� ��
}


void star_move() {

	if (bounce == 0) {
		if (move_star_z > -18) {
			move_star_z -= move_speed; //�ӵ��� �����ϴٰ� Ư�� ��ġ�� ���� 0���� ������� �ٽ� Ƣ�� ������ �Ѵ�.
			move_speed += GRAVITY;
		}
		else {
			move_speed = INIT_MOVESPEED;
			//Sleep(100);
			bounce = 1;
		}
	}
	else {//Ƣ�� ������ ���·� ��ȭ ���� ��, �� bounce�� 1�� ��
		if (move_star_z < jump_height) {
			move_star_z += move_speed;
			move_speed += GRAVITY;
		}
		else {
			jump_height += 10;
			move_speed = INIT_MOVESPEED;
			//Sleep(100);
			bounce = 0;
			if (jump_height == CLEAR_HEIGHT && bounce == 0) {
				MessageBox(NULL, "�༺ Ż�⿡ �����Ͽ����ϴ�!! -��-", "���� Ŭ����!", MB_OK);
				exit(0);
			}//Ŭ���� ���� �޼���
		}
	}

}

void move_planet() {
	for (int i = 1; i <= 10; ++i) {
		if (go_left_x[i-1] == 0) {//���������� ���� ������ ��
			if (ob_x[i-1] < 43) {
				ob_x[i-1] += (move_planet_speed*i);
			}
			else {
				go_left_x[i-1] = 1;
			}
		}
		else {//�������� ���� ������ ��
			if (ob_x[i-1] > -40) {
				ob_x[i-1] -= (move_planet_speed*i);
			}
			else {
				go_left_x[i-1] = 0;
			}
		}
		if (go_bottom_y[i-1] == 0) {//���� (y������)
			if (ob_y[i-1] < 20) {
				ob_y[i-1] += (move_planet_speed*i);
			}
			else {
				go_bottom_y[i-1] = 1;
			}
		}
		else {//�Ʒ��� (-y������)
			if (ob_y[i-1] > -23) {
				ob_y[i-1] -= (move_planet_speed*i);
			}
			else {
				go_bottom_y[i-1] = 0;
			}
		}
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(view_x, view_y, view_z, 0, 0, 0, 0, 1, 0);
	star_move();
	move_planet();
	crash();
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

	glTranslatef(move_star_x, move_star_y, 5);
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

	GLfloat emission_material[] = { 0.2, 0.2, 0.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_EMISSION, emission_material);
	glTranslatef(0, 0, -15 - move_star_z);
	glBindTexture(GL_TEXTURE_2D, ids[1]);
	GLUquadricObj *donut = gluNewQuadric(); //�̰��� ��
	gluDisk(donut, 0.2, 50, 100, 20);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient3);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse3);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular1);

	glMaterialfv(GL_FRONT, GL_EMISSION, emission_material);
	glTranslatef(0, 8, -25 - move_star_z);
	GLUquadricObj *foot = gluNewQuadric(); //�̰��� �ٸ�
	gluCylinder(foot, 2, 2, 10, 20, 5);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(6, 0, -25-move_star_z);
	GLUquadricObj *foot2 = gluNewQuadric(); //�̰��� �ٸ�
	gluCylinder(foot2, 2, 2, 10, 20, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-6, 0, -25 - move_star_z);
	GLUquadricObj *foot3 = gluNewQuadric(); //�̰��� �ٸ�
	gluCylinder(foot3, 2, 2, 10, 20, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -6, -25-move_star_z);
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
	glTranslatef(ob_x[0], ob_y[0], ob_z[0]-move_star_z);
	glBindTexture(GL_TEXTURE_2D, ids[3]);
	gluSphere(sphere, 3, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular1);
	glMaterialf(GL_FRONT, GL_SHININESS, shine);
	glMaterialfv(GL_FRONT, GL_EMISSION, emission_material);
	glTranslatef(ob_x[1], ob_y[1], ob_z[1] -move_star_z);
	glBindTexture(GL_TEXTURE_2D, ids[2]);
	gluSphere(sphere, 3, 100, 100);
	glPopMatrix();
	
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular1);
	glMaterialf(GL_FRONT, GL_SHININESS, shine);
	glMaterialfv(GL_FRONT, GL_EMISSION, emission_material);
	glTranslatef(ob_x[2], ob_y[2], ob_z[2]-move_star_z);
	glBindTexture(GL_TEXTURE_2D, ids[2]);
	gluSphere(sphere, 3, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular1);
	glMaterialf(GL_FRONT, GL_SHININESS, shine);
	glMaterialfv(GL_FRONT, GL_EMISSION, emission_material);
	glTranslatef(ob_x[3], ob_y[3], ob_z[3] - move_star_z);
	glBindTexture(GL_TEXTURE_2D, ids[3]);
	gluSphere(sphere, 3, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular1);
	glMaterialf(GL_FRONT, GL_SHININESS, shine);
	glMaterialfv(GL_FRONT, GL_EMISSION, emission_material);
	glTranslatef(ob_x[4], ob_y[4], ob_z[4] - move_star_z);
	glBindTexture(GL_TEXTURE_2D, ids[2]);
	gluSphere(sphere, 3, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular1);
	glMaterialf(GL_FRONT, GL_SHININESS, shine);
	glMaterialfv(GL_FRONT, GL_EMISSION, emission_material);
	glTranslatef(ob_x[5], ob_y[5], ob_z[5] - move_star_z);
	glBindTexture(GL_TEXTURE_2D, ids[3]);
	gluSphere(sphere, 3, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular1);
	glMaterialf(GL_FRONT, GL_SHININESS, shine);
	glMaterialfv(GL_FRONT, GL_EMISSION, emission_material);
	glTranslatef(ob_x[6], ob_y[6], ob_z[6] - move_star_z);
	glBindTexture(GL_TEXTURE_2D, ids[3]);
	gluSphere(sphere, 3, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular1);
	glMaterialf(GL_FRONT, GL_SHININESS, shine);
	glMaterialfv(GL_FRONT, GL_EMISSION, emission_material);
	glTranslatef(ob_x[7], ob_y[7], ob_z[7] - move_star_z);
	glBindTexture(GL_TEXTURE_2D, ids[3]);
	gluSphere(sphere, 3, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular1);
	glMaterialf(GL_FRONT, GL_SHININESS, shine);
	glMaterialfv(GL_FRONT, GL_EMISSION, emission_material);
	glTranslatef(ob_x[8], ob_y[8], ob_z[8] - move_star_z);
	glBindTexture(GL_TEXTURE_2D, ids[4]);
	gluSphere(sphere, 3, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular1);
	glMaterialf(GL_FRONT, GL_SHININESS, shine);
	glMaterialfv(GL_FRONT, GL_EMISSION, emission_material);
	glTranslatef(ob_x[9], ob_y[9], ob_z[9] - move_star_z);
	glBindTexture(GL_TEXTURE_2D, ids[4]);
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
	gluPerspective(45, ratio, 1, 1000);
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
	
	tex[3] = auxDIBImageLoad("planet_2.bmp");
	glGenTextures(3, &ids[3]); 
	glBindTexture(GL_TEXTURE_2D, ids[3]); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, tex[3]->sizeX, tex[3]->sizeY, 0, GL_RGB,
		GL_UNSIGNED_BYTE, tex[3]->data); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
	

	
	//��ֹ� 3 �ؽ���
	
	tex[4] = auxDIBImageLoad("planet_3.bmp");
	glGenTextures(3, &ids[4]); 
	glBindTexture(GL_TEXTURE_2D, ids[4]); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, tex[4]->sizeX, tex[4]->sizeY, 0, GL_RGB,
		GL_UNSIGNED_BYTE, tex[4]->data); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
    
	

	glClearColor(0, 1, 1, 0); //���� ���� G+B
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	
	glutIdleFunc(display);//Idle�ð��� ����ؼ� �۵��ϴ� �Լ�
	glutKeyboardFunc(keyboard);

	glutMainLoop();
}