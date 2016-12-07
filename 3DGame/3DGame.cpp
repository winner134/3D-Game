/* Sami Mohammed
CS 5472
3D Game in OpenGL

3DGame.cpp
Lines of Code: 793
*/

#include <stdlib.h>
#include <glut.h>
#include <math.h>
#include <stdio.h>
#include "3DGame.h"
#include "linklist.h"
#include "LinkList.c"

void init()
{
 
  /* attributes */

  glClearColor(1.0, 1.0, 1.0, 0.0); /* white background */
  
  qobj = gluNewQuadric();
  
  player1_bullets = CreateList();
  player2_bullets = CreateList();

  glEnable(GL_NORMALIZE);
  glEnable(GL_DEPTH_TEST);
	
}

void reshape (int w, int h)
{
   /* set up viewing */

   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt (0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

   float width_resize_ratio = w/(WINDOW_WIDTH + 0.0);
   float length_resize_ratio = h/(WINDOW_LENGTH + 0.0);

   MIN_X = MIN_X * width_resize_ratio;
   MIN_Y = MIN_Y * length_resize_ratio;
   edge_collision_factor_player2 = edge_collision_factor_player2 * length_resize_ratio;
   edge_collision_factor1_player2 = edge_collision_factor1_player2 * width_resize_ratio;
   edge_collision_factor_player1 = edge_collision_factor_player1 * width_resize_ratio;
   
   WINDOW_WIDTH = w;
   WINDOW_LENGTH = h;
 
}

void display() {

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f (0.0, 0.0, 1.0);
	
	keyEventHandler();
	arrowKeyEventHandler();

	drawPlayer1();
	drawPlayer2();

	updateBulletPosition(player1_bullets, &player1_bullet_count, 1);
	updateBulletPosition(player2_bullets, &player2_bullet_count, 2);

	glPushMatrix();
		drawBullets(player1_bullets, &player1_bullet_count, 1);
	glPopMatrix();

	glPushMatrix();
		drawBullets(player2_bullets, &player2_bullet_count, 2);
	glPopMatrix();

	readLight1Parameters();
	readLight2Parameters();
	readMaterialParameters();

	/* enable light 1 */
	if (enable_light1)
		glEnable(GL_LIGHT1);

	/* enable light 2 */
	if(enable_light2)
		glEnable(GL_LIGHT2);

	/* enable lighting */

	if(enable_lighting) {

		glEnable(GL_LIGHTING);
		glShadeModel(GL_SMOOTH);

		/* update ambient, diffuse, specular, and position of light 1 parameters */
		glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
		glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

		/* update ambient, diffuse, specular, and position of light 2 parameters */
		glLightfv(GL_LIGHT2, GL_AMBIENT, light2_ambient);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
		glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
		glLightfv(GL_LIGHT2, GL_POSITION, light2_position);

		/* update material properties */
		glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, material_shininess);
	}

	else {
		glDisable(GL_LIGHTING);
	}
	
	glutSwapBuffers();
}

void drawPlayer1() {

	glPushMatrix();

	if(enable_light1 == 0 && enable_light2 == 0) {

		glScalef(0.45, 0.45, 0.45);
		glTranslatef(translate_player1_x, translate_player1_y, translate_player1_z);
		glTranslatef(-2.0, 0.0, 0.0);
		setPlayerRotation(rotation_mode_player1, rotate_player1);
		drawHalfCylinder(RED, player1_cylinder_radius, player1_cylinder_height);
		glScalef(0.85, 0.85, 0.85);
		glTranslatef(0.0, 0.0, 2.8);
		drawCube(1.0, DARK_GREEN);
		glTranslatef(0.0, 0.0, 0.57);
		drawCircle(0.25, BLACK);
		/*setColour(DARK_GREEN);
		glTranslatef(-4.5, 0.0, -3.4);
		glRotatef(-90, 0.0, 1.0, 0.0);
		glutSolidCone(2, 3, 40, 32);
		drawCube(3, DARK_GREEN);*/
		glPopMatrix();

		glPushMatrix();
		glScalef(0.45, 0.45, 0.45);
		glTranslatef(translate_player1_x, translate_player1_y, translate_player1_z);
		glTranslatef(-2.0, 0.0, 0.0);
		setPlayerRotation(rotation_mode_player1, rotate_player1);
		glRotatef(180, 1.0, 0.0, 0.0);
		drawHalfCylinder(LIGHT_BLUE, player1_cylinder_radius, player1_cylinder_height);
	}
	
	else {
		
		glScalef(0.45, 0.45, 0.45);
		glTranslatef(translate_player1_x, translate_player1_y, translate_player1_z);
		setPlayerRotation(rotation_mode_player1, rotate_player1);
		glRotatef(-90, 0.0, 1.0, 0.0);
		drawCylinder(RED, player1_cylinder_radius, player1_cylinder_height);
		drawCircle(player1_cylinder_radius, RED);
		glTranslatef(0.0,0.0, 5.0);
		drawCircle(player1_cylinder_radius, RED);
		glScalef(0.85, 0.85, 0.85);
		glTranslatef(-2.7, 0.0, -3.0);
		glRotatef(-90, 0.0, 1.0, 0.0);
		drawCube(1.0, DARK_GREEN);
		glTranslatef(0.0, 0.0, 0.57);
		drawCircle(0.25, BLACK);
	}
	
	glPopMatrix();
	
}

void drawPlayer2() {
	
	glPushMatrix();
	glScalef(0.90, 0.90, 0.90);
	glTranslatef(translate_player2_x, translate_player2_y, translate_player2_z);
	glTranslatef(4.0, 0.0, 0.0);
	setPlayerRotation(rotation_mode_player2, rotate_player2);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -0.8, 0.0);
	drawHalfTorus(player2_torus_inner_radius, player2_torus_outer_radius, COLOUR2);
	glRotatef(180, 1.0, 0.0, 0.0);
	drawHalfTorus(player2_torus_inner_radius, player2_torus_outer_radius, DARK_BLUE);
	drawHalfSphere(player2_sphere_radius, DARK_BLUE);
	glRotatef(180, 1.0, 0.0, 0.0);
	drawHalfSphere(player2_sphere_radius, YELLOW);
	glScalef(0.450, 0.450, 0.450);
	glTranslatef(0.0, 3.9, 0.0);
	drawCube(0.9, DARK_GREEN);
	glTranslatef(0.0, 0.5, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	drawCircle(0.22, BLACK);
	glPopMatrix();
}

void drawHalfSphere(float radius, int colour) {

	setColour(colour);

	double clip_plane1[]={0.0,1.0,0.0,0.0};
	glClipPlane(GL_CLIP_PLANE1,clip_plane1);
	glEnable(GL_CLIP_PLANE1);
	glutSolidSphere(radius, 40, 32);
	glDisable(GL_CLIP_PLANE1);
}

void drawSphere(float radius, int colour) {

	setColour(colour);
	glutSolidSphere(radius, 40, 32);
}

void drawHalfTorus(float innerRadius, float outerRadius, int colour) {

	setColour(colour);

	double clip_plane1[]={0.0,1.0,0.0,0.0};
	glClipPlane(GL_CLIP_PLANE1,clip_plane1);
	glEnable(GL_CLIP_PLANE1);
	glutSolidTorus(innerRadius, outerRadius, 40, 32);
	glDisable(GL_CLIP_PLANE1);
}

void drawCube(float size, int colour) {
	
	setColour(DARK_GREEN);
	glutSolidCube(size);
}

void setPlayerRotation(int rotation_mode, float rotation_angle) {

	switch(rotation_mode) {
		
		case Y_ROTATION:
			glRotatef(rotation_angle, 0.0, 1.0, 0.0);
			break;

		case X_ROTATION:
			glRotatef(rotation_angle, 1.0, 0.0, 0.0);
			break;

		case Z_ROTATION:
			glRotatef(rotation_angle, 0.0, 0.0, 1.0);
			break;

		case XY_ROTATION:
			glRotatef(rotation_angle, 1.0, 1.0, 0.0);
			break;

		case XYZ_ROTATION:
			glRotatef(rotation_angle, 1.0, 1.0, 1.0);
			break;

		case YZ_ROTATION:
			glRotatef(rotation_angle, 0.0, 1.0, 1.0);
			break;

		case XZ_ROTATION:
			glRotatef(rotation_angle, 1.0, 0.0, 1.0);
			break;

	}
}

void drawHalfCylinder(int colour, float radius, float height) {

	int STEPS = 20;
	float DELTA = PI/STEPS;
	float angle = 0;

	setColour(colour);

	glBegin(GL_POLYGON);
		
	for(int step=0; step<=STEPS; ++step) {
		angle = step*DELTA;
		glVertex3f(height/2.0,radius*cos(angle),radius*sin(angle));
	}
	
	glEnd();

	glBegin(GL_POLYGON);
	
	for(int step=0; step<=STEPS; ++step) {
		angle = step*DELTA;
		glVertex3f(-height/2.0,radius*cos(angle),radius*sin(angle));
	}
	
	glEnd();

	glBegin(GL_QUADS);
		
    for(int step=0; step<STEPS; ++step) {
		
		float angle1 = step*DELTA; // at this angle the quad starts
		float angle2 = (step+1)*DELTA; // look ahead of next angle: at this angle the quad ends
		float rsine1 = radius*sin(angle1);
		float rcosine1 = radius*cos(angle1);
		float rsine2 = radius*sin(angle2);
		float rcosine2 = radius*cos(angle2);
		glVertex3f(height/2,rcosine1,rsine1);
		glVertex3f(height/2,rcosine2,rsine2);
		glVertex3f(-height/2,rcosine2,rsine2);
		glVertex3f(-height/2,rcosine1,rsine1);
	}
	
	glEnd();

}

void drawCylinder(int colour, float radius, float height) {

	setColour(colour);

	gluCylinder(qobj, radius, radius, height, 40, 32);
}

void drawCircle(float radius, int colour) {

	setColour(colour);

	glBegin(GL_POLYGON);

	for(int angle = 0; angle <=360; angle = angle + 5) {

		glVertex3f(radius*cos(angle * PI/180), radius * sin(angle * PI/180), 0);
	}

	glEnd();
}

void moveCamera() {

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt (0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   glRotatef(eye_x, 1.0, 0.0, 0.0);
   glRotatef(eye_y, 0.0, 1.0, 0.0);
}

int detectPlayerCollision() {
	
	if(player1_x_initial_position + translate_player1_x >= player2_x_initial_position + translate_player2_x - player2_scale_radius &&
		player1_x_initial_position + translate_player1_x <= player2_x_initial_position + translate_player2_x + player2_scale_radius &&
		player1_y_initial_position + translate_player1_y >= player2_y_initial_position + translate_player2_y - player2_scale_radius &&
		player1_y_initial_position + translate_player1_y <= player2_y_initial_position + translate_player2_y + player2_scale_radius &&
		translate_player1_z == translate_player2_z) {
	   return 1;
	}

	return 0;
}

void seperatePlayers() {
	
	translate_player1_x = translate_player1_x - 0.7;
}

void arrowKeyEventHandler() {
	
	if(specialKeys[GLUT_KEY_UP]) {
		
		if(translate_player2_y + edge_collision_factor_player2 <= -MIN_Y) {
			translate_player2_y = translate_player2_y + player2_displacement;
		}
	}

	if (specialKeys[GLUT_KEY_DOWN]) {
		
		if(translate_player2_y - edge_collision_factor_player2 >= MIN_Y) {
			translate_player2_y = translate_player2_y - player2_displacement;
		}
	}

	if(specialKeys[GLUT_KEY_LEFT]) {
		
		if (translate_player2_x >= MIN_X) {
			translate_player2_x = translate_player2_x - player2_displacement;
		}
	}

	if(specialKeys[GLUT_KEY_RIGHT]) {
		
		if (translate_player2_x + edge_collision_factor1_player2 <= -MIN_X) {
			translate_player2_x = translate_player2_x + player2_displacement;
		}
	}

	if(detectPlayerCollision())
		seperatePlayers();

}

void keyEventHandler() {

	if(keys[KEY_CODE_X] || keys[KEY_CODE_x]) {

		rotate_player1 = rotate_player1 + 3;

		if(rotate_player1 >= 180)
			rotate_player1 = -180;
	}

	if(keys[KEY_CODE_P] || keys[KEY_CODE_p]) {
		
		rotate_player2 = rotate_player2 + 3;

		if(rotate_player2 >= 180)
			rotate_player2 = -180;
	}

	if(keys[KEY_CODE_A] || keys[KEY_CODE_a]) {
		
		if (translate_player1_x >= MIN_X) {
			translate_player1_x = translate_player1_x - player1_displacement;
		}
	}

	if(keys[KEY_CODE_S] || keys[KEY_CODE_s]) {
		
		if(translate_player1_y >= MIN_Y) {
			translate_player1_y = translate_player1_y - player1_displacement;
		}
	}

	if(keys[KEY_CODE_W] || keys[KEY_CODE_w]) {
		
		if(translate_player1_y <= -MIN_Y) {
			translate_player1_y = translate_player1_y + player1_displacement;
		}
	}

	if(keys[KEY_CODE_D] || keys[KEY_CODE_d]) {
		
		if (translate_player1_x - edge_collision_factor_player1 <= -MIN_X) {
			translate_player1_x = translate_player1_x + player1_displacement;
		}
	}

	if(keys[KEY_CODE_R] || keys[KEY_CODE_r]) {

	}

	if(keys[KEY_CODE_I] || keys[KEY_CODE_i]) {

		translate_player2_z = translate_player2_z + player2_displacement;
	}

	if(keys[KEY_CODE_O] || keys[KEY_CODE_o]) {

		translate_player2_z = translate_player2_z - player2_displacement;
	}

	if(keys[KEY_CODE_C] || keys[KEY_CODE_c]) {

		translate_player1_z = translate_player1_z + player1_displacement;
	}

	if(keys[KEY_CODE_F] || keys[KEY_CODE_f]) {

		translate_player1_z = translate_player1_z - player1_displacement;
	}

	if(keys[KEY_CODE_SPACE]) {

		addBullet(player1_bullets, &player1_bullet_count, player1_x_initial_position + translate_player1_x,
			player1_y_initial_position + translate_player1_y, player1_z_initial_position + translate_player1_z, rotate_player1);
	}

	if(keys[KEY_CODE_ENTER]) {

		addBullet(player2_bullets, &player2_bullet_count, player2_x_initial_position + translate_player2_x,
			player2_y_initial_position + translate_player2_y, player2_z_initial_position + translate_player2_z, rotate_player2);
	}

	if(keys[KEY_CODE_1]) {

		eye_x = eye_x + camera_increment;
		moveCamera();
	}

	if(keys[KEY_CODE_2]) {

		eye_x = eye_x - camera_increment;
		moveCamera();
	}

	if(keys[KEY_CODE_3]) {

		eye_y = eye_y + camera_increment;
		moveCamera();
	}

	if(keys[KEY_CODE_4]) {

		eye_y = eye_y - camera_increment;
		moveCamera();
	}

	if(keys[KEY_CODE_5]) {

		eye_x = 0;
		eye_y = 0;
		reshape(WINDOW_WIDTH, WINDOW_LENGTH);
	}
}

void keyPressDown(unsigned char key, int x, int y) {

	keys[key]=1;
	glutPostRedisplay();
}

void keyPressUp(unsigned char key, int x, int y) {

	keys[key]=0;
	glutPostRedisplay();
}

void arrowKeyDown(int key, int x, int y) {	
										
	specialKeys[key] = 1;
	glutPostRedisplay();
}

void arrowKeyUp(int key, int x, int y) {

	specialKeys[key] = 0;
	glutPostRedisplay();
}

void readLight1Parameters() {
	
	FILE *pFile;

	pFile = fopen("c://lightParameters.txt", "r");

	if (pFile != NULL) {
		
		fscanf(pFile, "%d", &enable_lighting);
		fscanf(pFile, "%d", &enable_light1);
		fscanf(pFile, "%f", &light1_ambient[0]);
		fscanf(pFile, "%f", &light1_ambient[1]);
		fscanf(pFile, "%f", &light1_ambient[2]);
		fscanf(pFile, "%f", &light1_ambient[3]);
		fscanf(pFile, "%f", &light1_diffuse[0]);
		fscanf(pFile, "%f", &light1_diffuse[1]);
		fscanf(pFile, "%f", &light1_diffuse[2]);
		fscanf(pFile, "%f", &light1_diffuse[3]);
		fscanf(pFile, "%f", &light1_specular[0]);
		fscanf(pFile, "%f", &light1_specular[1]);
		fscanf(pFile, "%f", &light1_specular[2]);
		fscanf(pFile, "%f", &light1_specular[3]);
		fscanf(pFile, "%f", &light1_position[0]);
		fscanf(pFile, "%f", &light1_position[1]);
		fscanf(pFile, "%f", &light1_position[2]);
		fclose(pFile);
	}


}


void readLight2Parameters() {

	FILE *pFile;

	pFile = fopen("c://light2Parameters.txt", "r");

	if (pFile != NULL) {

		fscanf(pFile, "%d", &enable_light2);
		fscanf(pFile, "%f", &light2_ambient[0]);
		fscanf(pFile, "%f", &light2_ambient[1]);
		fscanf(pFile, "%f", &light2_ambient[2]);
		fscanf(pFile, "%f", &light2_ambient[3]);
		fscanf(pFile, "%f", &light2_diffuse[0]);
		fscanf(pFile, "%f", &light2_diffuse[1]);
		fscanf(pFile, "%f", &light2_diffuse[2]);
		fscanf(pFile, "%f", &light2_diffuse[3]);
		fscanf(pFile, "%f", &light2_specular[0]);
		fscanf(pFile, "%f", &light2_specular[1]);
		fscanf(pFile, "%f", &light2_specular[2]);
		fscanf(pFile, "%f", &light2_specular[3]);
		fscanf(pFile, "%f", &light2_position[0]);
		fscanf(pFile, "%f", &light2_position[1]);
		fscanf(pFile, "%f", &light2_position[2]);
		fclose(pFile);
	}
		
}

void readMaterialParameters() {

	FILE *pFile;

	pFile = fopen("c://materialParameters.txt", "r");

	if (pFile != NULL) {

		fscanf(pFile, "%f", &material_ambient[0]);
		fscanf(pFile, "%f", &material_ambient[1]);
		fscanf(pFile, "%f", &material_ambient[2]);
		fscanf(pFile, "%f", &material_ambient[3]);
		fscanf(pFile, "%f", &material_diffuse[0]);
		fscanf(pFile, "%f", &material_diffuse[1]);
		fscanf(pFile, "%f", &material_diffuse[2]);
		fscanf(pFile, "%f", &material_diffuse[3]);
		fscanf(pFile, "%f", &material_specular[0]);
		fscanf(pFile, "%f", &material_specular[1]);
		fscanf(pFile, "%f", &material_specular[2]);
		fscanf(pFile, "%f", &material_specular[3]);
		fclose(pFile);
	}
}

void addBullet(List bullets, int *player_bullet_count, float ibx, float iby, float ibz, float angle) {
	
	*player_bullet_count = *player_bullet_count + 1;

	int result = InsertInList(*player_bullet_count, ibx, iby, ibz, 0, 0, 0, angle - 90, angle - 90, angle, bullets);

}

void removeBullet(List bullets, int index, int *player_bullet_count) {

	DeleteInList(index, bullets);

	*player_bullet_count = *player_bullet_count - 1;
}

void updateBulletPosition(List bullets, int *player_bullet_count, int player) {
	
	for(int i = 1; i <= *player_bullet_count; i++) {
		
		Node bullet = SelectInList(i, bullets);

		if(bullet->initial_bullet_x + bullet->translate_bullet_x >= MIN_X && bullet->initial_bullet_x + bullet->translate_bullet_x <= -MIN_X &&
			bullet->initial_bullet_y + bullet->translate_bullet_y >= MIN_Y && bullet->initial_bullet_y + bullet->translate_bullet_y <= -MIN_Y) {
		
				if((player == 1 && bullet->initial_bullet_x + bullet->translate_bullet_x >= player2_x_initial_position + translate_player2_x - player2_scale_radius
					&& bullet->initial_bullet_x + bullet->translate_bullet_x <= player2_x_initial_position + translate_player2_x + player2_scale_radius
					&& bullet->initial_bullet_y + bullet->translate_bullet_y <= player2_y_initial_position + translate_player2_y - player2_scale_radius
					&& bullet->initial_bullet_y + bullet->translate_bullet_y >= player2_y_initial_position + translate_player2_y + player2_scale_radius) ||
					(player == 2 && bullet->initial_bullet_x + bullet->translate_bullet_x >= player1_x_initial_position + translate_player1_x - player1_cylinder_scale_radius
					&& bullet->initial_bullet_x + bullet->translate_bullet_x <= player1_x_initial_position + translate_player1_x + player1_cylinder_scale_radius
					&& bullet->initial_bullet_y + bullet->translate_bullet_y <= player1_y_initial_position + translate_player1_y - player1_cylinder_scale_radius
					&& bullet->initial_bullet_y + bullet->translate_bullet_y >= player1_y_initial_position + translate_player1_y + player1_cylinder_scale_radius))
				{
			
					removeBullet(bullets, i, player_bullet_count);
				}

				else {

					bullet->translate_bullet_x += cos(bullet->bullet_angle_x * PI/180) * player_bullet_pixel_speed;
					bullet->translate_bullet_y += sin(bullet->bullet_angle_y * PI/180) * player_bullet_pixel_speed;
					bullet->translate_bullet_z += cos(bullet->bullet_angle_z * PI/180) * player_bullet_pixel_speed;
					
				}
		}

		else {
			
			removeBullet(bullets, i, player_bullet_count);
		}
	}


}

void drawBullets(List bullets, int *player_bullet_count, int player) {

	for(int i = 1; i <= *player_bullet_count; i++) {

		Node bullet = SelectInList(i, bullets);

		glTranslatef(bullet->initial_bullet_x + bullet->translate_bullet_x, 0.0, 0.0);
		glTranslatef(0.0, bullet->initial_bullet_y + bullet->translate_bullet_y, 0.0);
		glTranslatef(0.0, 0.0, bullet->initial_bullet_z + bullet->translate_bullet_z);

		if(player == 1)
			drawSphere(0.2, LIGHT_BLUE);
		else if(player == 2)
			drawSphere(0.2, GREEN);
		
		glutPostRedisplay();
		/*glPointSize(3.0);
		glBegin(GL_POINTS);
			glVertex3f(0,0,0);
			glVertex3f(bullet->initial_bullet_x + bullet->translate_bullet_x,
				bullet->initial_bullet_y + bullet->translate_bullet_y,
				bullet->initial_bullet_z + bullet->translate_bullet_z);
		glEnd();*/ 
	}

}

void setColour(int colour) {

	switch(colour) {

	case RED:
		glColor3f(1.0, 0.0, 0.0);
		break;

	case GREEN:
		glColor3f(0.0, 1.0, 0.0);
		break;

	case LIGHT_BLUE:
		glColor3f(0.078, 0.102, 0.922);
		break;

	case YELLOW:
		glColor3f(1.0, 1.0, 0.0);
		break;

	case BLACK:
		glColor3f(0.0, 0.0, 0.0);
		break;

	case DARK_GREEN:
		glColor3f(0.0, 0.5, 0.0);
		break;

	case COLOUR1:
		glColor3f(0.465, 0.641, 0.781);
		break;

	case DARK_BLUE:
		glColor3f(0.137, 0.102, 0.848);
		break;

	case COLOUR2:
		glColor3f(0.926, 0.453, 0.926);
		break;
	}
}

void processMenuEvents(int mode) {
	
	rotation_mode_player1 = mode;
	rotation_mode_player2 = mode;
}

void createRotationModeMenu() {

	int menu,submenu;

	submenu = glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("X", X_ROTATION);
	glutAddMenuEntry("Y", Y_ROTATION);
	glutAddMenuEntry("Z", Z_ROTATION);
	glutAddMenuEntry("XY", XY_ROTATION);
	glutAddMenuEntry("XZ", XZ_ROTATION);
	glutAddMenuEntry("YZ", YZ_ROTATION);
	glutAddMenuEntry("XYZ", XYZ_ROTATION);

	menu = glutCreateMenu(processMenuEvents);
	glutAddSubMenu("Player Rotation",submenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (WINDOW_WIDTH, WINDOW_LENGTH); 
   glutInitWindowPosition (0, 0);
   glutCreateWindow ("OpenGL 3D Shooting Game");
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(arrowKeyDown);
   glutSpecialUpFunc(arrowKeyUp);
   glutKeyboardFunc(keyPressDown);
   glutKeyboardUpFunc(keyPressUp);
   createRotationModeMenu();
   glutMainLoop();

   return 0;
}