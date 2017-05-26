#include <QtGui>
#include "mainscene.h"
#include <math.h>
#include <gl/glext.h>
#include <gl/gl.h>

MainScene::MainScene(QWidget *parent):QGLWidget(parent)
{

}

MainScene::~MainScene()
{

}

void MainScene::initializeGL()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void MainScene::resizeGL(int nWidth, int nHeight)
{
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
}

void MainScene::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.25, 0.87, 0.81);
    glBegin(GL_TRIANGLES);

    glVertex2f(0.0, 1.0);
    glVertex2f(0.0, 0.0);
    glVertex2f(1.0, 0.5);

    glEnd();

    /*glColor3f(0.13, 0.56, 0.13);
    glBegin(GL_QUADS);

    glVertex2f(0.0, 0.5);
    glVertex2f(0.0, 1.0);
    glVertex2f(0.5, 1.0);
    glVertex2f(0.5, 0.5);

    glEnd();

    glLineWidth(2.0);
    glColor3f(0.65, 0.16, 0.16);
    glBegin(GL_LINE_STRIP);

    glVertex2f(0.0, 0.5);
    glVertex2f(0.5, 1.0);
    glVertex2f(1.0, 0.5);
    glVertex2f(0.5, 0);
    glVertex2f(0.0, 0.5);

    glEnd();*/
}
