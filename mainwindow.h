#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_x_slider_rotate_valueChanged(int value);

    void on_y_slider_rotate_valueChanged(int value);

    void on_z_slider_rotate_valueChanged(int value);

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_x_slider_look_valueChanged(int value);

    void on_y_slider_look_valueChanged(int value);

    void on_z_slider_look_valueChanged(int value);

    void on_zoom_slider_look_valueChanged(int value);

    void on_light_0_check_toggled(bool checked);

    void on_light_1_check_toggled(bool checked);

    void on_ball_check_toggled(bool checked);

    void on_x_light0_move_valueChanged(int value);

    void on_y_light0_move_valueChanged(int value);

    void on_z_light0_move_valueChanged(int value);

    void on_x_light1_move_valueChanged(int value);

    void on_y_light1_move_valueChanged(int value);

    void on_z_light1_move_valueChanged(int value);

    void on_shelf_check_toggled(bool checked);

    void on_round_shelf_check_toggled(bool checked);

private:
    Ui::MainWindow *ui;

    int last_zoom_slider_look;
};

#endif // MAINWINDOW_H
