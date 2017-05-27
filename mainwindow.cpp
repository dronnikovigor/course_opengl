#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "drawopengl.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->x_slider_rotate->setValue(0);
    ui->y_slider_rotate->setValue(0);
    ui->z_slider_rotate->setValue(0);
    on_x_slider_rotate_valueChanged(0);

    ui->light_0_check->setChecked(true);
    ui->light_1_check->setChecked(true);

    ui->x_slider_look->setValue(105);
    ui->y_slider_look->setValue(105);
    ui->z_slider_look->setValue(55);
    on_x_slider_look_valueChanged(0);


    on_comboBox_currentTextChanged("PERSPECTIVE");
    ui->comboBox->setCurrentIndex(1);

    last_zoom_slider_look = 100;
    ui->zoom_slider_look->setValue(last_zoom_slider_look);
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::on_zoom_slider_look_valueChanged(int value)
{
    ui->OpenGLWidget->setLook((ui->zoom_slider_look->value()-last_zoom_slider_look+ui->x_slider_look->value())*0.01,
                              (ui->zoom_slider_look->value()-last_zoom_slider_look+ui->y_slider_look->value())*0.01,
                              (ui->zoom_slider_look->value()-last_zoom_slider_look+ui->z_slider_look->value())*0.01);
    ui->x_slider_look->setValue(ui->zoom_slider_look->value()-last_zoom_slider_look+ui->x_slider_look->value());
    ui->y_slider_look->setValue(ui->zoom_slider_look->value()-last_zoom_slider_look+ui->y_slider_look->value());
    ui->z_slider_look->setValue(ui->zoom_slider_look->value()-last_zoom_slider_look+ui->z_slider_look->value());
    ui->OpenGLWidget->update();
    last_zoom_slider_look = ui->zoom_slider_look->value();
}

void MainWindow::on_light_0_check_toggled(bool checked)
{
    ui->OpenGLWidget->setLightCheck(checked, 0);
    ui->OpenGLWidget->update();
}

void MainWindow::on_light_1_check_toggled(bool checked)
{
    ui->OpenGLWidget->setLightCheck(checked, 1);
    ui->OpenGLWidget->update();
}
