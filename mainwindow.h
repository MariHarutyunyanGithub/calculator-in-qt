#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setupUi();
    void setters();
    void on_pushButton_dot_clicked();
    void on_pushButton_equal_clicked();
    void on_pushButton_C_clicked();
    QString parse();
private slots:
    void digit_buttons();
    void math_operations();
    void operations();
private:
    Ui::MainWindow *ui;
    QPushButton ***pushButton;
    QPushButton **big_pushButton;
    QLabel *label;
    QString label_string{}; // for label_text()
};
#endif // MAINWINDOW_H
