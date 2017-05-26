#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "drawopengl.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->verticalLinesSlider->setValue(100);

    ui->x_slider_rotate->setValue(0);
    ui->y_slider_rotate->setValue(0);
    ui->z_slider_rotate->setValue(0);
    on_x_slider_rotate_valueChanged(0);


    ui->x_slider_move->setValue(0);
    ui->y_slider_move->setValue(0);
    ui->z_slider_move->setValue(0);
    on_x_slider_move_valueChanged(0);

    ui->x_slider_look->setValue(5);
    ui->y_slider_look->setValue(5);
    ui->z_slider_look->setValue(5);
    on_x_slider_look_valueChanged(0);
    //ui->checkBox->setEnabled(false);
    on_checkBox_toggled(false);


    on_comboBox_currentTextChanged("PERSPECTIVE");
    ui->comboBox->setCurrentIndex(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_verticalLinesSlider_valueChanged(int value)
{
    ui->OpenGLWidget->setVerticalLines(value);
    ui->OpenGLWidget->update();
}


void MainWindow::on_x_slider_rotate_valueChanged(int value)
{
    ui->OpenGLWidget->setAngle(ui->x_slider_rotate->value(), ui->y_slider_rotate->value(), ui->z_slider_rotate->value());
    ui->OpenGLWidget->update();
}

void MainWindow::on_y_slider_rotate_valueChanged(int value)
{
    on_x_slider_rotate_valueChanged(0);
    ui->OpenGLWidget->update();
}

void MainWindow::on_z_slider_rotate_valueChanged(int value)
{
    on_x_slider_rotate_valueChanged(0);
    ui->OpenGLWidget->update();
}

void MainWindow::on_x_slider_move_valueChanged(int value)
{
    ui->OpenGLWidget->setMove(ui->x_slider_move->value()*0.01, ui->y_slider_move->value()*0.01, ui->z_slider_move->value()*0.01);
    ui->OpenGLWidget->update();
}

void MainWindow::on_y_slider_move_valueChanged(int value)
{
    on_x_slider_move_valueChanged(0);
    ui->OpenGLWidget->update();
}

void MainWindow::on_z_slider_move_valueChanged(int value)
{
    on_x_slider_move_valueChanged(0);
    ui->OpenGLWidget->update();
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    ui->OpenGLWidget->setView(arg1);
    ui->OpenGLWidget->update();
}

void MainWindow::on_x_slider_look_valueChanged(int value)
{
    ui->OpenGLWidget->setLook(ui->x_slider_look->value()*0.01, ui->y_slider_look->value()*0.01, ui->z_slider_look->value()*0.01);
    ui->OpenGLWidget->update();
}

void MainWindow::on_y_slider_look_valueChanged(int value)
{
    on_x_slider_look_valueChanged(0);
    ui->OpenGLWidget->update();
}

void MainWindow::on_z_slider_look_valueChanged(int value)
{
    on_x_slider_look_valueChanged(0);
    ui->OpenGLWidget->update();
}

void MainWindow::on_checkBox_toggled(bool checked)
{
    ui->OpenGLWidget->setXyzCheck(checked);
    ui->OpenGLWidget->update();
}

void MainWindow::on_zoom_slider_look_valueChanged(int value)
{
    ui->OpenGLWidget->setLook((ui->zoom_slider_look->value()+ui->x_slider_look->value())*0.01, (ui->zoom_slider_look->value()+ui->y_slider_look->value())*0.01, (ui->zoom_slider_look->value()+ui->z_slider_look->value())*0.01);
    ui->x_slider_look->setValue(ui->zoom_slider_look->value()+ui->x_slider_look->value());
    ui->y_slider_look->setValue(ui->zoom_slider_look->value()+ui->y_slider_look->value());
    ui->z_slider_look->setValue(ui->zoom_slider_look->value()+ui->z_slider_look->value());
    ui->OpenGLWidget->update();
}
