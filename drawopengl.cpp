#include "drawopengl.h"

#define PI 3.14


DrawOpenGL::DrawOpenGL(QWidget *parent)
    : QOpenGLWidget(parent)
{
}

DrawOpenGL::~DrawOpenGL()
{

}

void DrawOpenGL::initializeGL()
{
    glClearColor(0.1,0.1,0.2,1);

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
    //if (xyz_check)
    //    paintXYZ();
    if (ball_check)
        paintBall(-0.2, 0.1, -0.5, 0.1);
    offLight();

}
void DrawOpenGL::setLight()
{
    // свойства материала
    GLfloat material_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    for (int i = 0; i < 2; i++){
        if (light_check[i] == true)
        {
            glEnable(GL_LIGHTING);
            glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
            continue;
        }
    }
    // установка источников света
    // точечный источник света
    // убывание интенсивности с расстоянием
    // задано функцией f(d) = 1.0 / (0.4 * d * d + 0.2 * d)
    //0
    if (light_check[0] == true)
    {
        GLfloat light0_diffuse[] = {0.95, 0.98, 0.84};
        GLfloat light0_position[] = {light_pos[0][0], light_pos[0][1], light_pos[0][2], 1.0};
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
        glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.0);
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.2);
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.4);
    }
    //1
    if (light_check[1] == true)
    {
        GLfloat light1_diffuse[] = {0.95, 0.98, 0.84};
        GLfloat light1_position[] = {light_pos[1][0], light_pos[1][1], light_pos[1][2], 1.0};
        glEnable(GL_LIGHT1);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
        glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
        glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.0);
        glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.2);
        glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.4);
    }

}

void DrawOpenGL::offLight()
{
    if (light_check[0] == true)
    {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
    }
    if (light_check[1] == true)
    {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT1);
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
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    GLUquadricObj *quadObj;
    GLfloat front_color[] = {0,1,0,1};
    quadObj = gluNewQuadric();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, front_color);
    glPushMatrix();
    glColor3d(1,0,0);
    gluQuadricDrawStyle(quadObj, GLU_FILL);
    glTranslated(x_0,y_0,z_0);
    gluSphere(quadObj, R, 20, 20);
    glPopMatrix();
    gluDeleteQuadric(quadObj);
}

void DrawOpenGL::resizeGL(int nWidth, int nHeight)
{
      wWidth = nWidth; wHeight = nHeight;

      glViewport(0, 0, wWidth, wHeight);
}

void DrawOpenGL::setAngle(int x, int y, int z)
{
    x_angle = x;
    y_angle = y;
    z_angle = z;
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

void DrawOpenGL::setLightCheck(bool flag, int i)
{
    light_check[i] = flag;
}

void DrawOpenGL::setBallCheck(bool flag)
{
    ball_check = flag;
}

void DrawOpenGL::setLightPos(float x, float y, float z, int i)
{
    light_pos[i][0] = x;
    light_pos[i][1] = y;
    light_pos[i][2] = z;
}
