/* Osama Mohammed
CS 5472
3D Game in OpenGL

3DGame.h
Lines of Code: 175
*/

#include "LinkList.h"

#define RED 1
#define GREEN 2
#define YELLOW 3
#define LIGHT_BLUE 4
#define BLACK 5
#define DARK_GREEN 6
#define COLOUR1 7
#define DARK_BLUE 8
#define COLOUR2 9
#define PI 3.14159265
#define X_ROTATION 0
#define Y_ROTATION 1
#define XY_ROTATION 2
#define XYZ_ROTATION 3
#define YZ_ROTATION 4
#define XZ_ROTATION 5
#define Z_ROTATION 6
#define KEY_CODE_a 97
#define KEY_CODE_A 65
#define KEY_CODE_s 115
#define KEY_CODE_S 83
#define KEY_CODE_w 119
#define KEY_CODE_W 87
#define KEY_CODE_D 68
#define KEY_CODE_d 100
#define KEY_CODE_R 82
#define KEY_CODE_r 114
#define KEY_CODE_SPACE 32
#define KEY_CODE_ENTER 13
#define KEY_CODE_P 80
#define KEY_CODE_p 112
#define KEY_CODE_X 88
#define KEY_CODE_x 120
#define KEY_CODE_I 73
#define KEY_CODE_i 105
#define KEY_CODE_o 111
#define KEY_CODE_O 79
#define KEY_CODE_C 67
#define KEY_CODE_c 99
#define KEY_CODE_F 70
#define KEY_CODE_f 102
#define KEY_CODE_1 49
#define KEY_CODE_2 50
#define KEY_CODE_3 51
#define KEY_CODE_4 52
#define KEY_CODE_5 53

int WINDOW_WIDTH = 1100;
int WINDOW_LENGTH = 675;
float MIN_X = -14.00;
float MIN_Y = -9.72;
int rotation_mode_player1 = 1;
int rotation_mode_player2 = 1;
int keys[256];
int specialKeys[256];

float player1_displacement = 0.12;
float player2_displacement = 0.065;
float player1_cylinder_radius = 2.0;
float player1_cylinder_scale_radius = 0.45 * player1_cylinder_radius;
float player1_cylinder_height = 5.0;
float player1_scale_cylinder_height = 0.45 * player1_cylinder_height;
float player2_torus_inner_radius = 0.3; 
float player2_torus_outer_radius = 1.5;
float player2_sphere_radius = 1.0;
float player2_total_radius = player2_torus_inner_radius + player2_torus_outer_radius + player2_sphere_radius;
float player2_scale_radius = 0.90 * player2_total_radius;
float rotate_player1 = 0;
float rotate_player2 = 0;
float player1_x_initial_position = 0.0;
float player1_y_initial_position = 0.0;
float player1_z_initial_position = 0.0;
float player2_x_initial_position = 4.23;
float player2_y_initial_position = 0.0;
float player2_z_initial_position = 0.0;
float translate_player1_x = 0;
float translate_player1_y = 0;
float translate_player1_z = 0;
float translate_player2_x = 0;
float translate_player2_y = 0;
float translate_player2_z = 0;
float edge_collision_factor_player2 = 4.5;
float edge_collision_factor1_player2 = 9.0;
float edge_collision_factor_player1 = 5.0;

float eye_x = 0.0;
float eye_y = 0.0;
float eye_z = 0.0;
float camera_increment = 1.0;

GLUquadricObj *qobj;

/* Lighting parameters */

/* ambient, diffuse, and specular */

GLfloat light1_ambient[4] = {1.0, 0.0, 0.0, 1.0};
GLfloat light1_diffuse[4] = {1.0, 1.0, 1.0, 1.0};
GLfloat light1_specular[4] = {1.0, 0.0, 1.0, 1.0};

GLfloat light2_ambient[4] = {1.0, 0.0, 0.0, 1.0};
GLfloat light2_diffuse[4] = {1.0, 1.0, 1.0, 1.0};
GLfloat light2_specular[4] = {1.0, 0.0, 1.0, 1.0};

/* Light position */
GLfloat light1_position[4] = {-1.0, 0.0, 1.0, 0.0};
GLfloat light2_position[4] = {1.0, 0.0, 1.0, 0.0};

/* Material Parameters */

GLfloat material_ambient[4] = {1.0, 1.0, 1.0, 1.0};
GLfloat material_diffuse[4] = {1.0, 1.0, 1.0, 1.0};
GLfloat material_specular[4] = {1.0, 1.0, 1.0, 1.0};
GLfloat material_shininess = 100.0;

int enable_lighting = 0;
int enable_light1 = 0;
int enable_light2 = 0;


List player1_bullets;
List player2_bullets;

int player1_bullet_count = 0;
int player2_bullet_count = 0;
float player_bullet_pixel_speed = 0.05;

void display();
void init();
void reshape (int w, int h);
void moveCamera();
void drawPlayer1();
void drawPlayer2();
void drawCube(float size, int colour);
void drawSphere(float radius, int colour);
void drawHalfCylinder(int colour, float radius, float height);
void drawHalfSphere(float radius, int colour);
void drawHalfTorus(float innerRadius, float outerRadius, int colour);
void drawCylinder(int colour, float radius, float height);
void drawCircle(float radius, int colour);
void setPlayerRotation(int rotation_mode, float rotation_angle);
int detectPlayerCollision();
void seperatePlayers();
void updatePlayer1Position();
void updatePlayer2Position();

void setColour(int colour);
void keyEventHandler();
void arrowKeyEventHandler();
void keyPressDown(unsigned char key, int x, int y);
void keyPressUp(unsigned char key, int x, int y);
void arrowKeyDown(int key, int x, int y);
void arrowKeyUp(int key, int x, int y);

void readLight1Parameters();
void readLight2Parameters();
void readMaterialParameters();

void addBullet(List bullets, int *player_bullet_count, float ibx, float iby, float ibz, float angle);
void removeBullet(List bullets, int index, int *player_bullet_count);
void updateBulletPosition(List bullets, int *player_bullet_count, int player);
void drawBullets(List bullets, int *player_bullet_count, int player);

void createRotationModeMenu();
void processMenuEvents(int mode);