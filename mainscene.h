#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QTimer>
#include <QGLWidget>

class MainScene : public QGLWidget
{
    Q_OBJECT

private:

private slots:

protected:
    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();

public:
    MainScene(QWidget *parent = 0);
    ~MainScene();

};

#endif // MAINSCENE_H
