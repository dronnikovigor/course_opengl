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
    void on_verticalLinesSlider_valueChanged(int value);


    void on_x_slider_rotate_valueChanged(int value);

    void on_y_slider_rotate_valueChanged(int value);

    void on_z_slider_rotate_valueChanged(int value);

    void on_x_slider_move_valueChanged(int value);

    void on_y_slider_move_valueChanged(int value);

    void on_z_slider_move_valueChanged(int value);

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_x_slider_look_valueChanged(int value);

    void on_y_slider_look_valueChanged(int value);

    void on_z_slider_look_valueChanged(int value);

    void on_checkBox_toggled(bool checked);

    void on_zoom_slider_look_valueChanged(int value);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
