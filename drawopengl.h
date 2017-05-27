#ifndef DRAWOPENGL_H
#define DRAWOPENGL_H

#include <QWidget>
#include <QOpenGLWidget>
#include <gl/GLU.h>
#include <gl/GL.h>
#include <gl/GLAUX.h>

class DrawOpenGL : public QOpenGLWidget
{
private:
    int wWidth, wHeight;

    enum myView {PERSPECTIVE,ORTHO};
    myView currentView;
    const static int lightNum = 2;
    bool light_check[lightNum];
    float light_pos[lightNum][3];

    int x_angle;
    int y_angle;
    int z_angle;

    float x_look;
    float y_look;
    float z_look;
    bool ball_check;

public:
    DrawOpenGL(QWidget *parent = 0);
    ~DrawOpenGL();

    void setLight();
    void offLight();
    void paintXYZ();
    void paintWalls();
    void paintBall(float x_0, float y_0, float z_0, float R);

    void setAngle(int x, int y, int z);
    void setView(QString value);
    void setLook(float x, float y, float z);
    void setLightCheck(bool flag, int i);
    void setBallCheck(bool flag);
    void setLightPos(float x, float y, float z, int i);
protected:
    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();
};

#endif // DRAWOPENGL_H
