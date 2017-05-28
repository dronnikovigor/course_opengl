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
    //glEnableClientState(GL_VERTEX_ARRAY);
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
        glOrtho(-3.0, 3.0, -3.0, 3.0, -3.0, 3.0);
        break;
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x_look, y_look, z_look, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glRotated(x_angle,1,0,0);
    glRotated(y_angle,0,1,0);
    glRotated(z_angle,0,0,1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    // Сглаживание точек
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    // Сглаживание линий
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    // Сглаживание полигонов
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

    setLight();
    paintWalls();
    //if (xyz_check)
    //    paintXYZ();
    if (ball_check)
        paintBall(-0.2, 0.1, -0.5, 0.15);
    if (shelf_check)
    {
        light_pos[2][0] = 0.3;
        light_pos[2][1] = 0.14;
        light_pos[2][2] = 0.3;
        light_check[2] = true;
        paintShelf(0.4, 0.0, 0.4, 0.15, 0.5, 0.4);
        paintShelf(0.4, 0.15, 0.4, 0.15, 0.4, 0.4);
        paintShelf(0.4, 0.3, 0.4, 0.15, 0.3, 0.4);
    }
    else
        light_check[2] = false;
    //setShadow();

    offLight();

    glDisable(GL_BLEND);
    glDisable(GL_POINT_SMOOTH);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_POLYGON_SMOOTH);
}
void DrawOpenGL::setLight()
{
    // свойства материала
    GLfloat material_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    for (int i = 0; i < lightNum; i++){
        if (light_check[i] == true)
        {
            glEnable(GL_LIGHTING);
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
    //2
    if (light_check[2] == true)
    {
        GLfloat light2_diffuse[] = {0.95, 0.98, 0.84};
        GLfloat light2_position[] = {light_pos[2][0], light_pos[2][1], light_pos[2][2], 1.0};
        glEnable(GL_LIGHT2);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
        glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
        glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.0);
        glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.6);
        glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.6);
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
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT2);
}

void DrawOpenGL::setShadow()
{

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

void DrawOpenGL::drawPolygon(float xA, float yA, float zA, float xB, float yB, float zB, float xC, float yC, float zC, float xD, float yD, float zD, int xN, int yN, int zN)
{
    glBegin(GL_POLYGON);
    glNormal3f(xN, yN, zN);
    glVertex3d(xA, yA, zA);
    glVertex3d(xB, yB, zB);
    glVertex3d(xC, yC, zC);
    glVertex3d(xD, yD, zD);
    glEnd();
}

void DrawOpenGL::paintShelf(float x_0, float y_0, float z_0, float h, float w, float d)
{
    float step = 0.02;
    glColor4d(0.72,0.81,0.80,1.0);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    GLfloat front_color[] = {0.72,0.81,0.80,1};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, front_color);

    //inside
    drawPolygon(x_0-d,y_0+h-step,z_0-step, x_0,y_0+h-step,z_0-step, x_0,y_0+h-step,z_0-w+step, x_0-d,y_0+h-step,z_0-w+step, 0,-1,0);
    drawPolygon(x_0-d,y_0,z_0-w+step, x_0-d,y_0+h-step,z_0-w+step, x_0,y_0+h-step,z_0-w+step, x_0,y_0,z_0-w+step, 0,0,1);
    drawPolygon(x_0,y_0,z_0-step, x_0,y_0+h-step,z_0-step, x_0-d,y_0+h-step,z_0-step, x_0-d,y_0,z_0-step, 0,0,-1);
    //outside
    drawPolygon(x_0,y_0+h,z_0, x_0-d,y_0+h,z_0, x_0-d,y_0+h,z_0-w, x_0,y_0+h,z_0-w, 0,1,0);
    drawPolygon(x_0,y_0,z_0-w, x_0,y_0+h,z_0-w, x_0-d,y_0+h,z_0-w, x_0-d,y_0,z_0-w, 0,0,-1);
    drawPolygon(x_0-d,y_0,z_0, x_0-d,y_0+h,z_0, x_0,y_0+h,z_0, x_0,y_0,z_0, 0,0,1);

    drawPolygon(x_0,y_0+h-step,z_0, x_0,y_0+h,z_0, x_0,y_0+h,z_0-w, x_0,y_0+h-step,z_0-w, 1,0,0);
    drawPolygon(x_0,y_0,z_0, x_0,y_0+h-step,z_0, x_0,y_0+h-step,z_0-step, x_0,y_0,z_0-step, 1,0,0);
    drawPolygon(x_0,y_0,z_0-w+step, x_0,y_0+h-step,z_0-w+step, x_0,y_0+h-step,z_0-w, x_0,y_0,z_0-w, 1,0,0);

    drawPolygon(x_0-d,y_0+h-step,z_0-w, x_0-d,y_0+h,z_0-w, x_0-d,y_0+h,z_0,  x_0-d,y_0+h-step,z_0, -1,0,0);
    drawPolygon(x_0-d,y_0,z_0-step, x_0-d,y_0+h-step,z_0-step, x_0-d,y_0+h-step,z_0, x_0-d,y_0,z_0, -1,0,0);
    drawPolygon(x_0-d,y_0,z_0-w, x_0-d,y_0+h-step,z_0-w, x_0-d,y_0+h-step,z_0-w+step, x_0-d,y_0,z_0-w+step, -1,0,0);
}


void DrawOpenGL::paintWalls()
{
    //wall
    glColor4d(0.88,0.87,0.88,1.0);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    GLfloat front_color[] = {0.88,0.87,0.88,1};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, front_color);
    drawPolygon(-1.0,0.0,-1.0, -1.0,1.0,-1.0, 0.5,1.0,-1.0, 0.5,0.0,-1.0, 0,0,1);

    //plinth
    glColor4d(0.80,0.79,0.80,1.0);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    front_color[0] =0.75;
    front_color[1] =0.79;
    front_color[2] =0.90;
    glMaterialfv(GL_FRONT, GL_DIFFUSE, front_color);
    drawPolygon(-1.0,0.0,-0.99, -1.0,0.1,-0.99, 0.5,0.1,-0.99, 0.5,0.0,-0.99, 0,0,1);
    drawPolygon(-1.0,0.1,-0.99, -1.0,0.1,-1.0, 0.5,0.1,-1.0, 0.5,0.1,-0.99, 0,1,0);

    //wall
    glColor4d(0.88,0.87,0.88,1.0);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    front_color[0] =0.88;
    front_color[1] =0.87;
    front_color[2] =0.88;
    glMaterialfv(GL_FRONT, GL_DIFFUSE, front_color);
    drawPolygon(-1.0,0.0,0.5, -1.0,1.0,0.5, -1.0,1.0,-1.0, -1.0,0.0,-1.0, 1,0,0);

    //windows
    glColor4d(0.0,0.0,0.0,1.0);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    front_color[0] =0.1;
    front_color[1] =0.1;
    front_color[2] =0.2;
    glMaterialfv(GL_FRONT, GL_DIFFUSE, front_color);
    drawPolygon(-1.0,0.2,0.45, -1.0,0.8,0.45, -1.0,0.8,0.05, -1.0,0.2,0.05, 1,0,0);
    drawPolygon(-1.0,0.2,-0.0, -1.0,0.8,-0.0, -1.0,0.8,-0.45, -1.0,0.2,-0.45, 1,0,0);
    drawPolygon(-1.0,0.2,-0.5, -1.0,0.8,-0.5, -1.0,0.8,-0.95, -1.0,0.2,-0.95, 1,0,0);

    //over windows
    glColor4d(0.88,0.87,0.88,1.0);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    front_color[0] =0.88;
    front_color[1] =0.87;
    front_color[2] =0.88;
    glMaterialfv(GL_FRONT, GL_DIFFUSE, front_color);
    drawPolygon(-1.0,0.8,0.5, -0.8,0.8,0.5, -0.8,0.8,-1.0, -1.0,0.8,-1.0, 0,-1,0);
    drawPolygon(-0.8,0.8,0.5, -0.8,1.0,0.5, -0.8,1.0,-1.0, -0.8,0.8,-1.0, 1,0,0);


    //plinth
    glColor4d(0.80,0.79,0.80,1.0);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    front_color[0] =0.75;
    front_color[1] =0.79;
    front_color[2] =0.90;
    glMaterialfv(GL_FRONT, GL_DIFFUSE, front_color);
    drawPolygon(-0.99,0.0,0.5, -0.99,0.1,0.5, -0.99,0.1,-1.0, -0.99,0.0,-1.0, 1,0,0);
    drawPolygon(-0.99,0.1,0.5, -1.0,0.1,0.5, -1.0,0.1,-1.0, -0.99,0.1,-1.0, 0,1,0);

    //wall
    glColor4d(0.88,0.87,0.88,1.0);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    front_color[0] =0.88;
    front_color[1] =0.87;
    front_color[2] =0.88;
    glMaterialfv(GL_FRONT, GL_DIFFUSE, front_color);
    drawPolygon(0.5,0.0,-1.0, 0.5,1.0,-1.0, 0.5,1.0,0.5, 0.5,0.0,0.5, 0,0,1);

    //plinth
    glColor4d(0.80,0.79,0.80,1.0);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    front_color[0] =0.75;
    front_color[1] =0.79;
    front_color[2] =0.90;
    glMaterialfv(GL_FRONT, GL_DIFFUSE, front_color);
    drawPolygon(0.49,0.0,-1.0, 0.49,0.1,-1.0, 0.49,0.1,0.5, 0.49,0.0,0.5, 0,0,1);
    drawPolygon(0.49,0.1,-1.0, 0.5,0.1,-1.0, 0.5,0.1,0.5, 0.49,0.1,0.5, 0,1,0);

    //wall
    glColor4d(0.88,0.87,0.88,1.0);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    front_color[0] =0.88;
    front_color[1] =0.87;
    front_color[2] =0.88;
    glMaterialfv(GL_FRONT, GL_DIFFUSE, front_color);
    drawPolygon(0.5,0.0,0.5, 0.5,1.0,0.5, -1.0,1.0,0.5, -1.0,0.0,0.5, 1,0,0);

    //plinth
    glColor4d(0.80,0.79,0.80,1.0);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    front_color[0] =0.75;
    front_color[1] =0.79;
    front_color[2] =0.90;
    glMaterialfv(GL_FRONT, GL_DIFFUSE, front_color);
    drawPolygon(0.5,0.0,0.49, 0.5,0.1,0.49, -1.0,0.1,0.49, -1.0,0.0,0.49, 1,0,0);
    drawPolygon(0.5,0.1,0.49, 0.5,0.1,0.5, -1.0,0.1,0.5, -1.0,0.1,0.49, 0,1,0);

    //floor
    glColor4d(0.80,0.79,0.80,1.0);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    front_color[0] =0.75;
    front_color[1] =0.79;
    front_color[2] =0.90;
    glMaterialfv(GL_FRONT, GL_DIFFUSE, front_color);
    glDisable(GL_CULL_FACE);
    drawPolygon(0.5,0.0,0.5, -1.0,0.0,0.5, -1.0,0.0,-1.0, 0.5,0.0,-1.0, 0,1,0);
    glEnable(GL_CULL_FACE);
}

void DrawOpenGL::paintBall(float x_0, float y_0, float z_0, float R)
{    
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    GLfloat front_color[] = {0.72,0.81,0.80,1};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, front_color);
    glPushMatrix();
    float step = 0.05;
    glColor3d(1,0,0);
    for (float alpha1 = -PI/2; alpha1 <= PI/2; alpha1+=step)
        for (float alpha2 = -PI; alpha2 <= PI; alpha2+=step)
        {
            glBegin(GL_POLYGON);
            glNormal3f(0,1,0);
            float x=x_0+R*cos(alpha2)*cos(alpha1);
            float y=y_0+R*sin(alpha2)*cos(alpha1);
            float z=z_0+R*sin(alpha1);
            glVertex3d(x, y, z);
            x=x_0+R*cos(alpha2+step)*cos(alpha1);
            y=y_0+R*sin(alpha2+step)*cos(alpha1);
            z=z_0+R*sin(alpha1);
            glVertex3d(x, y, z);
            x=x_0+R*cos(alpha2+step)*cos(alpha1+step);
            y=y_0+R*sin(alpha2+step)*cos(alpha1+step);
            z=z_0+R*sin(alpha1+step);
            glVertex3d(x, y, z);
            x=x_0+R*cos(alpha2)*cos(alpha1+step);
            y=y_0+R*sin(alpha2)*cos(alpha1+step);
            z=z_0+R*sin(alpha1+step);
            glVertex3d(x, y, z);
            glEnd();
        }
    glPopMatrix();
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
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

void DrawOpenGL::setShelfCheck(bool flag)
{
    shelf_check = flag;
}

void DrawOpenGL::setLightPos(float x, float y, float z, int i)
{
    light_pos[i][0] = x;
    light_pos[i][1] = y;
    light_pos[i][2] = z;
}
