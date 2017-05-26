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
    float vertex[4][3] = {{0.27, 0.5, 0.0},
                          {0.03, 0.35, 0.0},
                          {0.03, 0.1, 0.0},
                          {0.1, 0.0, 0.0}};
    float x_0,
            y_0,
            z_0;

    int verticalLines;
    int x_angle;
    int y_angle;
    int z_angle;

    float x_look;
    float y_look;
    float z_look;
    bool xyz_check;

    int light_sample;
public:
    DrawOpenGL(QWidget *parent = 0);
    ~DrawOpenGL();


    void setLight();
    void paintXYZ();
    void paintWalls();
    void setVerticalLines(int value);
    void setAngle(int x, int y, int z);
    void setMove(float x, float y, float z);
    void setView(QString value);
    void setLook(float x, float y, float z);
    void setXyzCheck(bool flag);
    void paintBall(float x_0, float y_0, float z_0, float R);
protected:
    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();
};

#endif // DRAWOPENGL_H
