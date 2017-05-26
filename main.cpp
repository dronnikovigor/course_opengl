#include <QApplication>
#include "mainwindow.h"
#include "mainscene.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow scene;

    scene.setWindowTitle("COURSE WORK | OpenGL | Дронников Игорь, Люшнина Елена | ФКТИ 4383");
    scene.show();
    
    return a.exec();
}
