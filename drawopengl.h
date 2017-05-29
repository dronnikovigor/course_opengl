#ifndef DRAWOPENGL_H
#define DRAWOPENGL_H

#include <QWidget>
#include <QOpenGLWidget>
#include <gl/GLU.h>
#include <gl/GL.h>
#include <gl/GLAUX.h>
#include <QMatrix4x4>

class DrawOpenGL : public QOpenGLWidget
{
private:
    int wWidth, wHeight;

    enum myView {PERSPECTIVE,ORTHO};
    myView currentView;
    const static int lightNum = 4;
    bool light_check[lightNum];
    float light_pos[lightNum][4];
    QMatrix4x4 ShadowMatrix;

    int x_angle;
    int y_angle;
    int z_angle;

    float x_look;
    float y_look;
    float z_look;
    bool ball_check;
    bool shelf_check;
    bool roundShelf_check;

public:
    DrawOpenGL(QWidget *parent = 0);
    ~DrawOpenGL();

    void setLight();
    void offLight();
    void setShadow();
    void paintXYZ();
    void drawPolygon(float xA, float yA, float zA, float xB, float yB, float zB, float xC, float yC, float zC, float xD, float yD, float zD, int xN, int yN, int zN);
    void drawTrgl(float xA, float yA, float zA, float xB, float yB, float zB, float xC, float yC, float zD, int xN, int yN, int zN);
    void paintShelf(float x_0, float y_0, float z_0, float h, float w, float d);
    void paintTrgl(float x_0, float y_0, float z_0, float w, float k);
    void paintRoundShelf(float x_0, float y_0, float z_0, float h, float r);
    void paintWalls();
    void paintBall(float x_0, float y_0, float z_0, float R);

    void setAngle(int x, int y, int z);
    void setView(QString value);
    void setLook(float x, float y, float z);
    void setLightCheck(bool flag, int i);
    void setBallCheck(bool flag);
    void setShelfCheck(bool flag);
    void setRoundShelfCheck(bool flag);
    void setLightPos(float x, float y, float z, int i);
protected:
    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();
};

#endif // DRAWOPENGL_H
