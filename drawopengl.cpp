#include "drawopengl.h"

#define PI 3.14


DrawOpenGL::DrawOpenGL(QWidget *parent)
    : QOpenGLWidget(parent)
{
    verticalLines = 10;
    x_angle = 0;
    y_angle = 0;
    z_angle = 0;

    light_sample = 3;
}

DrawOpenGL::~DrawOpenGL()
{

}

void DrawOpenGL::initializeGL()
{
    glClearColor(0.1,0.1,0.2,1);
    glEnable(GL_LIGHTING);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    glEnable(GL_NORMALIZE);
    glEnableClientState(GL_VERTEX_ARRAY);
}

void DrawOpenGL::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    switch(currentView){
    case PERSPECTIVE:
        gluPerspective (100, 1, 50, 0);
        break;
    case ORTHO:
        glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
        break;
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x_look, y_look, z_look, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glRotated(x_angle,1,0,0);
    glRotated(y_angle,0,1,0);
    glRotated(z_angle,0,0,1);

    setLight();
    paintWalls();
    if (xyz_check)
        paintXYZ();
    paintBall(-0.2, 0, -1, 0.1);

}
void DrawOpenGL::setLight()
{
    // свойства материала
    GLfloat material_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
    // установка источников света
    if (light_sample == 1)
    {
          // направленный источник света
          GLfloat light0_diffuse[] = {0.4, 0.7, 0.2};
          GLfloat light0_direction[] = {0.0, 0.0, 1.0, 0.0};
          glEnable(GL_LIGHT0);
          glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
          glLightfv(GL_LIGHT0, GL_POSITION, light0_direction);
    }
    if (light_sample == 2)
    {
          // точечный источник света
          // убывание интенсивности с расстоянием
          // отключено (по умолчанию)
          GLfloat light1_diffuse[] = {0.4, 0.7, 0.2};
          GLfloat light1_position[] = {0.0, 0.0, 1.0, 1.0};
          glEnable(GL_LIGHT1);
          glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
          glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    }
    if (light_sample == 3)
    {
          // точечный источник света
          // убывание интенсивности с расстоянием
          // задано функцией f(d) = 1.0 / (0.4 * d * d + 0.2 * d)
          GLfloat light2_diffuse[] = {0.95, 0.98, 0.84};
          GLfloat light2_position[] = {0.0, 0.9, 0.8, 1.0};
          glEnable(GL_LIGHT2);
          glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
          glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
          glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.0);
          glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.2);
          glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.4);
    }
    if (light_sample == 4)
    {
          // прожектор
          // убывание интенсивности с расстоянием
          // отключено (по умолчанию)
          // половина угла при вершине 30 градусов
          // направление на центр плоскости
          GLfloat light3_diffuse[] = {0.4, 0.7, 0.2};
          GLfloat light3_position[] = {0.0, 0.0, 1.0, 1.0};
          GLfloat light3_spot_direction[] = {0.0, 0.0, -1.0};
          glEnable(GL_LIGHT3);
          glLightfv(GL_LIGHT3, GL_DIFFUSE, light3_diffuse);
          glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
          glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 30);
          glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light3_spot_direction);
    }
    if (light_sample == 5)
    {
          // прожектор
          // убывание интенсивности с расстоянием
          // отключено (по умолчанию)
          // половина угла при вершине 30 градусов
          // направление на центр плоскости
          // включен рассчет убывания интенсивности для прожектора
          GLfloat light4_diffuse[] = {0.4, 0.7, 0.2};
          GLfloat light4_position[] = {0.0, 0.0, 1.0, 1.0};
          GLfloat light4_spot_direction[] = {0.0, 0.0, -1.0};
          glEnable(GL_LIGHT4);
          glLightfv(GL_LIGHT4, GL_DIFFUSE, light4_diffuse);
          glLightfv(GL_LIGHT4, GL_POSITION, light4_position);
          glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 30);
          glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, light4_spot_direction);
          glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 15.0);
    }
    if (light_sample == 6)
    {
          // несколько источников света
          GLfloat light5_diffuse[] = {1.0, 0.0, 0.0};
          GLfloat light5_position[] = {0.5 * cos(0.0), 0.5 * sin(0.0), 1.0, 1.0};
          glEnable(GL_LIGHT5);
          glLightfv(GL_LIGHT5, GL_DIFFUSE, light5_diffuse);
          glLightfv(GL_LIGHT5, GL_POSITION, light5_position);
          glLightf(GL_LIGHT5, GL_CONSTANT_ATTENUATION, 0.0);
          glLightf(GL_LIGHT5, GL_LINEAR_ATTENUATION, 0.4);
          glLightf(GL_LIGHT5, GL_QUADRATIC_ATTENUATION, 0.8);
          GLfloat light6_diffuse[] = {0.0, 1.0, 0.0};
          GLfloat light6_position[] = {0.5 * cos(2 * PI / 3), 0.5 * sin(2 * PI / 3), 1.0, 1.0};
          glEnable(GL_LIGHT6);
          glLightfv(GL_LIGHT6, GL_DIFFUSE, light6_diffuse);
          glLightfv(GL_LIGHT6, GL_POSITION, light6_position);
          glLightf(GL_LIGHT6, GL_CONSTANT_ATTENUATION, 0.0);
          glLightf(GL_LIGHT6, GL_LINEAR_ATTENUATION, 0.4);
          glLightf(GL_LIGHT6, GL_QUADRATIC_ATTENUATION, 0.8);
          GLfloat light7_diffuse[] = {0.0, 0.0, 1.0};
          GLfloat light7_position[] = {0.5 * cos(4 * PI / 3), 0.5 * sin(4 * PI / 3), 1.0, 1.0};
          glEnable(GL_LIGHT7);
          glLightfv(GL_LIGHT7, GL_DIFFUSE, light7_diffuse);
          glLightfv(GL_LIGHT7, GL_POSITION, light7_position);
          glLightf(GL_LIGHT7, GL_CONSTANT_ATTENUATION, 0.0);
          glLightf(GL_LIGHT7, GL_LINEAR_ATTENUATION, 0.4);
          glLightf(GL_LIGHT7, GL_QUADRATIC_ATTENUATION, 0.8);
    }
}


void DrawOpenGL::paintXYZ()
{
    glBegin(GL_LINES);
    glColor3d(1.0,1.0,1.0);
    glVertex3d(0.0,0.0,0.0);
    glVertex3d(1.0,0.0,0.0);
    glVertex3d(0.0,0.0,0.0);
    glVertex3d(0.0,1.0,0.0);
    glVertex3d(0.0,0.0,0.0);
    glVertex3d(0.0,0.0,1.0);
    glEnd();
}

void DrawOpenGL::paintWalls()
{
    glColor4d(0.5,1.0,1.0,1.0);
    glBegin(GL_QUADS);
    glVertex3d(-1.0,0.0,-1.0);
    glVertex3d(-1.0,1.0,-1.0);
    glVertex3d(0.5,1.0,-1.0);
    glVertex3d(0.5,0.0,-1.0);

    glVertex3d(-1.0,0.0,-1.0);
    glVertex3d(-1.0,1.0,-1.0);
    glVertex3d(-1.0,1.0,0.5);
    glVertex3d(-1.0,0.0,0.5);

    glVertex3d(-1.0,0.0,-1.0);
    glVertex3d(0.5,0.0,-1.0);
    glVertex3d(0.5,0.0,0.5);
    glVertex3d(-1.0,0.0,0.5);

    glVertex3d(-1.0,0.0,0.5);
    glVertex3d(-1.0,1.0,0.5);
    glVertex3d(0.5,1.0,0.5);
    glVertex3d(0.5,0.0,0.5);
    glEnd();

}

void DrawOpenGL::paintBall(float x_0, float y_0, float z_0, float R)
{
    //glColor3d(0.5,0.5,1.0);
    /*glBegin( GL_TRIANGLE_FAN );
    glVertex2f( 0.0f, 0.0f ); // вершина в центре круга
    for(int i = 0; i <= 50; i++ ) {
        float a = (float)i / 50.0f * 3.1415f * 2.0f;
        glVertex2f( cos( a ) * R, sin( a ) * R );
    }
    glEnd();*/
}

void DrawOpenGL::resizeGL(int nWidth, int nHeight)
{
      wWidth = nWidth; wHeight = nHeight;

      glViewport(0, 0, wWidth, wHeight);
}

void DrawOpenGL::setVerticalLines(int value)
{
    verticalLines = value;
}

void DrawOpenGL::setAngle(int x, int y, int z)
{
    x_angle = x;
    y_angle = y;
    z_angle = z;
}

void DrawOpenGL::setMove(float x, float y, float z)
{
    x_0 = x;
    y_0 = y;
    z_0 = z;
}

void DrawOpenGL::setView(QString value)
{
    if (value == "PERSPECTIVE")
        currentView = PERSPECTIVE;
    else
        currentView = ORTHO;
}

void DrawOpenGL::setLook(float x, float y, float z)
{
    x_look = x;
    y_look = y;
    z_look = z;
}

void DrawOpenGL::setXyzCheck(bool flag)
{
    xyz_check = flag;
}
