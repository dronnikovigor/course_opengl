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
    ui->ball_check->setChecked(true);
    ui->shelf_check->setChecked(true);
    ui->round_shelf_check->setChecked(true);

    ui->x_slider_look->setValue(105);
    ui->y_slider_look->setValue(105);
    ui->z_slider_look->setValue(55);
    on_x_slider_look_valueChanged(0);

    ui->x_light0_move->setValue(100);
    ui->y_light0_move->setValue(100);
    ui->z_light0_move->setValue(-80);
    ui->x_light1_move->setValue(-90);
    ui->y_light1_move->setValue(80);
    ui->z_light1_move->setValue(30);

    on_comboBox_currentTextChanged("PERSPECTIVE");
    ui->comboBox->setCurrentIndex(1);

    last_zoom_slider_look = 100;
    ui->zoom_slider_look->setValue(last_zoom_slider_look);
    ui->zoom_ort_slider->setValue(100);
    ui->zoom_ort_slider->setEnabled(false);
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
    if (arg1 =="ORHTO")
        ui->zoom_ort_slider->setEnabled(true);
    else
        ui->zoom_ort_slider->setEnabled(false);
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

void MainWindow::on_ball_check_toggled(bool checked)
{
    ui->OpenGLWidget->setBallCheck(checked);
    ui->OpenGLWidget->update();
}

void MainWindow::on_x_light0_move_valueChanged(int value)
{
    ui->OpenGLWidget->setLightPos(ui->x_light0_move->value()*0.01, ui->y_light0_move->value()*0.01, ui->z_light0_move->value()*0.01, 0);
    ui->OpenGLWidget->update();
}

void MainWindow::on_y_light0_move_valueChanged(int value)
{
    on_x_light0_move_valueChanged(0);
}

void MainWindow::on_z_light0_move_valueChanged(int value)
{
    on_x_light0_move_valueChanged(0);
}

void MainWindow::on_x_light1_move_valueChanged(int value)
{
    ui->OpenGLWidget->setLightPos(ui->x_light1_move->value()*0.01, ui->y_light1_move->value()*0.01, ui->z_light1_move->value()*0.01, 1);
    ui->OpenGLWidget->update();
}

void MainWindow::on_y_light1_move_valueChanged(int value)
{
    on_x_light1_move_valueChanged(0);
}

void MainWindow::on_z_light1_move_valueChanged(int value)
{
    on_x_light1_move_valueChanged(0);
}

void MainWindow::on_shelf_check_toggled(bool checked)
{
    ui->OpenGLWidget->setShelfCheck(checked);
    ui->OpenGLWidget->update();
}

void MainWindow::on_round_shelf_check_toggled(bool checked)
{
    ui->OpenGLWidget->setRoundShelfCheck(checked);
    ui->OpenGLWidget->update();
}

void MainWindow::on_zoom_ort_slider_valueChanged(int value)
{
    ui->OpenGLWidget->setZoomOrt(value*0.01);
    ui->OpenGLWidget->update();
}
