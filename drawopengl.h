#ifndef DRAWOPENGL_H
#define DRAWOPENGL_H

#include <QWidget>
#include <QOpenGLWidget>
#include <gl/GLU.h>
#include <gl/GL.h>

class DrawOpenGL : public QOpenGLWidget
{
private:
    int wWidth, wHeight;

    enum myView {PERSPECTIVE,ORTHO};
    myView currentView;
    bool light_check[2];

    int x_angle;
    int y_angle;
    int z_angle;

    float x_look;
    float y_look;
    float z_look;
    bool xyz_check;

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
    void setXyzCheck(bool flag);
    void setLightCheck(bool flag, int i);
protected:
    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();
};

#endif // DRAWOPENGL_H
