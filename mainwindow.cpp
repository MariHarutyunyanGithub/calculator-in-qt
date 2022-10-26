#include <QDebug>
#include <QList>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    setupUi();
    pushButton[2][3]->setCheckable(true);
    big_pushButton[2]->setCheckable(true);
}
MainWindow::~MainWindow()
{
    for (int i{}; i < 5; ++i) {
       delete[]pushButton[i];
    }
    delete[] pushButton;
    delete[] big_pushButton;
    delete label;
    delete ui;
}

void MainWindow::setupUi()
{
    resize(290, 440);
    setStyleSheet("background-color: lightsteelblue");
    label = new QLabel(this);
    label->setGeometry(10, 10, 270, 70);
    big_pushButton = new QPushButton*[3];
    for (int i{}; i < 3; ++i) {
        big_pushButton[i] = new QPushButton(this);
        big_pushButton[i]->setGeometry(QRect(10 + 94 * i, 90, 82, 60));
    }
    pushButton = new QPushButton**[4];
    for (int i{}; i < 4; ++i) {
        pushButton[i] = new QPushButton*[4]();
        for (int j{}; j < 4; ++j) {
            pushButton[i][j] = new QPushButton(this);
            pushButton[i][j]->setGeometry(QRect(10 + 70 * i, 160 + 70 * j, 60, 60));
        }
    }
    setters();
}

void MainWindow::setters()
{
    QFont font = label->font();
    font.setPointSize(30);
    label->setFont(font);
    label->setText("0");
    label->setStyleSheet("background-color: white; color:black; qproperty-alignment: 'AlignVCenter | AlignRight';");

    big_pushButton[0]->setText("C");
    big_pushButton[1]->setText("<--");
    big_pushButton[2]->setText("%");

    pushButton[0][0]->setText("7");
    pushButton[1][0]->setText("8");
    pushButton[2][0]->setText("9");
    pushButton[3][0]->setText("/");
    pushButton[0][1]->setText("4");
    pushButton[1][1]->setText("5");
    pushButton[2][1]->setText("6");
    pushButton[3][1]->setText("x");
    pushButton[0][2]->setText("1");
    pushButton[1][2]->setText("2");
    pushButton[2][2]->setText("3");
    pushButton[3][2]->setText("-");
    pushButton[0][3]->setText("0");
    pushButton[1][3]->setText(".");
    pushButton[2][3]->setText("=");
    pushButton[3][3]->setText("+");

    for (int i{}; i < 4; ++i) {
        for (int j{}; j < 4; ++j) {
            if (pushButton[i][j]->text() == "+" ||
                pushButton[i][j]->text() == "-" ||
                pushButton[i][j]->text() == "x" ||
                pushButton[i][j]->text() == "/") {
                pushButton[i][j]->setStyleSheet("background-color: darkcyan; color:black;");
                connect(pushButton[i][j], SIGNAL(clicked()),this, SLOT(math_operations()));
            }
            else if (pushButton[i][j]->text() == "=" ||
                     pushButton[i][j]->text() == ".") {
                pushButton[i][j]->setStyleSheet("background-color: darkturquoise; color:black;");
                connect(pushButton[i][j], SIGNAL(clicked()),this, SLOT(operations()));
            }
            else {
                pushButton[i][j]->setStyleSheet("background-color: lightsteelblue; color:black;");
                connect(pushButton[i][j], SIGNAL(clicked()),this, SLOT(digit_buttons()));
            }
        }
    }
    for (int i{}; i < 3; ++i) {
        big_pushButton[i]->setStyleSheet("background-color: darkturquoise; color:black;");
        connect(big_pushButton[i], SIGNAL(clicked()),this, SLOT(operations()));
    }
}

void MainWindow::digit_buttons()
{
    QPushButton *pushButton1 = (QPushButton*)sender();
    QFont font = label->font();
    if (label->text().size() < 6) {
        font.setPointSize(30);
    }
    else if (label->text().size() >= 6 && label->text().size() < 10) {
        font.setPointSize(25);
    }
    else if (label->text().size() >= 10 && label->text().size() <= 14){
        font.setPointSize(22);
    }
    else if (label->text().size() > 14 && label->text().size() <= 17) {
        font.setPointSize(17);
    }
    label->setFont(font);
    if (label->text().size() <= 17) {
        if (big_pushButton[2]->isChecked() ||
                pushButton[2][3]->isChecked() ||
                label->text() == "0") {
            label->setText(pushButton1->text());
            pushButton[2][3]->setChecked(false);
            big_pushButton[2]->setChecked(false);
        }
        else {
            label->setText(label->text() + pushButton1->text());
        }
    }
}

void MainWindow::math_operations()
{
    QPushButton *pushButton1 = (QPushButton*)sender();
    if (pushButton[2][3]->isChecked() ||
            big_pushButton[2]->isChecked()) {
        pushButton[2][3]->setChecked(false);
        big_pushButton[2]->setChecked(false);
       // label->setText(label->text() + pushButton1->text());
    }
    if (label->text() == "0") {
        label->setText("0" + pushButton1->text());
    }
        label_string = label->text();
        // կոտորոկային թվի վերջում գրված զրոները ջնջում ենք
        if (label_string[label_string.size() - 1] == '0')
            {
            int i = label_string.size() - 1;
            int dot_count{};
            while(label_string[i] != '+' &&
                  label_string[i] != '-' &&
                  label_string[i] != 'x' &&
                  label_string[i] != '/') {
                if (label_string[i] == '.') {
                    dot_count++;
                }
                --i;
            }
            if (dot_count > 0){
                i = label_string.size() - 1;
                while (label_string[i] == '0' && i > 1) {
                    label_string.remove(label_string.size() - 1, 1);
                    --i;
                }
                label->setText(label_string);
            }
        }
        // եթե թվի վերջում կետ կա, ջնջում ենք կետը
        if (label_string[label_string.size() - 1] == '.') {
            label_string.remove(label_string.size() - 1, 1);
            label->setText(label_string);
        }
        // վերջում գրված գործողության նշանը կարանք փոխենք
        if (label_string[label_string.size() - 1] == '+' ||
                 label_string[label_string.size() - 1] == '-' ||
                 label_string[label_string.size() - 1] == 'x' ||
                 label_string[label_string.size() - 1] == '/') {
            label_string = label->text();
            label_string.remove(label_string.size() - 1, 1);
            label->setText(label_string);
        }
        if (label->text() == "0") {
            label->setText("0" + pushButton1->text());
        }
        else {
            label->setText(label->text() + pushButton1->text());
        }
}

QString MainWindow::parse()
{
    QString token{};
    QList<QString> num_list{};
    QList<QString> oper_list{};
    QList<QString> new_oper_list{};
    QList<QString> new_num_list{};
    label_string = label->text();
    int i{};
    while (i < label_string.size()) {
        if (label_string[i] != '+' &&
               label_string[i] != '-' &&
               label_string[i] != 'x' &&
               label_string[i] != '/') {
            token += label_string[i];
        }
        else {
            num_list.push_back(token);
            oper_list.push_back(label_string[i]);
            token = "";
        }
        ++i;
    }
    num_list.push_back(token);
    for (int i{}; i < oper_list.size(); ++i) {
        qDebug() << "oper_list  " << oper_list[i];
    }
    for (int i{}; i < num_list.size(); ++i) {
        qDebug() << "num_list  " << num_list[i];
    }
    double first{};
    double second{};
    QString result{};
    do {
        if (oper_list.first() == "x") {
            first = num_list.first().toDouble();
            num_list.pop_front();
            second = num_list.first().toDouble();
            num_list.pop_front();
            result = QString::number(first * second);
            oper_list.pop_front();
            num_list.push_front(result);
        }
        else if (oper_list.first() == "/") {
            first = num_list.first().toDouble();
            num_list.pop_front();
            second = num_list.first().toDouble();
            num_list.pop_front();
            result = QString::number(first / second);
            oper_list.pop_front();
            num_list.push_front(result);
        }
        else {
            new_oper_list.push_back(oper_list.first());
            oper_list.pop_front();
            new_num_list.push_back(num_list.first());
            num_list.pop_front();
        }
    } while (!oper_list.isEmpty());
    new_num_list.push_back(num_list.first());
    num_list.pop_front();
    for (int i{}; i < new_oper_list.size(); ++i) {
        qDebug() << new_oper_list[i];
    }
    for (int i{}; i < new_num_list.size(); ++i) {
        qDebug() << new_num_list[i];
    }
    if (new_oper_list.isEmpty()) {
        return new_num_list.first();
    }
    do {
        if (new_oper_list.first() == '+') {
            first = new_num_list.first().toDouble();
            new_num_list.pop_front();
            second = new_num_list.first().toDouble();
            new_num_list.pop_front();
            new_oper_list.pop_front();
            result = QString::number(first + second);
            new_num_list.push_front(result);
        }
        else if (new_oper_list.first() == '-') {
            first = new_num_list.first().toDouble();
            new_num_list.pop_front();
            second = new_num_list.first().toDouble();
            new_num_list.pop_front();
            new_oper_list.pop_front();
            result = QString::number(first - second);
            new_num_list.push_front(result);
        }
    } while (!new_oper_list.isEmpty());
   return new_num_list.first();
}

void MainWindow::on_pushButton_dot_clicked()
{
    if (pushButton[2][3]->isChecked() ||
            big_pushButton[2]->isChecked() ||
            label->text() == "0") {
        pushButton[2][3]->setChecked(false);
        big_pushButton[2]->setChecked(false);
        label->setText("0.");
    }
    else {
        label_string = label->text();
        if (label_string[label_string.size() - 1] == '+' ||
                label_string[label_string.size() - 1] == '-' ||
                label_string[label_string.size() - 1] == 'x' ||
                label_string[label_string.size() - 1] == '/' ||
                label_string[label_string.size() - 1] == '%') {
            label->setText(label->text() + "0.");
        }
        else {
            int i = label_string.size() - 1;
            int dot_count{};
            while ((label_string[i] != '+' &&
                  label_string[i] != '-' &&
                  label_string[i] != 'x' &&
                  label_string[i] != '/') &&
                  i > 0) {
                if (label_string[i] == '.') {
                    dot_count++;
                }
                --i;
            }
            if (dot_count == 0) {
                label->setText(label->text() + '.');
            }
        }
    }
}

// buttons "%", "<--", "C", ".", "="
void MainWindow::operations()
{
    QPushButton *button = (QPushButton*)sender();
    if (pushButton[2][3]->isChecked()) {
        pushButton[2][3]->setChecked(false);
    }
    double numbers{};
    QString result1{};
    bool is_number_string{true};
    label_string = label->text();
    if(button->text() == '%') {
        for(int i{}; i < label_string.size(); ++i) {
            if (label_string[i] == '+' ||
                    label_string[i] == '-' ||
                    label_string[i] == 'x' ||
                    label_string[i] == '/') {
                is_number_string = false;
                break;
            }
        }
        if (is_number_string) {
            numbers = label_string.toDouble();
        }
        else{
            numbers = parse().toDouble();
        }
         numbers /= double(100);
         result1 = QString::number(numbers, 'd', 10);
         if (result1.contains(".")) {
             int count_of_0s{};
             for (int i = result1.size() - 1; i > 0; --i) {
                 if (result1[i] != '0') {
                     result1.remove(i + 1, count_of_0s);
                     break;
                 }
                 ++count_of_0s;
             }
         }
         QFont font = label->font();
         if (label->text().size() < 6) {
             font.setPointSize(30);
         }
         else if (label->text().size() >= 6 && label->text().size() < 10) {
             font.setPointSize(25);
         }
         else if (label->text().size() >= 10 && label->text().size() <= 14){
             font.setPointSize(22);
         }
         else if (label->text().size() > 14 && label->text().size() <= 17) {
             font.setPointSize(17);
         }
         label->setFont(font);
         label->setText(result1);
    }
    else if (button->text() == "<--") {
        QFont font = label->font();
        if (label->text().size() < 6) {
            font.setPointSize(30);
        }
        else if (label->text().size() >= 6 && label->text().size() < 10) {
            font.setPointSize(25);
        }
        else if (label->text().size() >= 10 && label->text().size() <= 14){
            font.setPointSize(22);
        }
        else if (label->text().size() > 14 && label->text().size() <= 17) {
            font.setPointSize(17);
        }
        else if (label->text().size() > 17) {
            font.setPointSize(15);
        }
        label->setFont(font);

        label->setText((label->text()).remove(label->text().size() - 1, 1));

        if (label->text() == "") {
            label->setText("0");
        }
    }
    else if (button->text() == "C") {
        on_pushButton_C_clicked();
    }
    else if (button->text() == ".") {
        on_pushButton_dot_clicked();
    }
    else { // if (button->text() == "=")
        on_pushButton_equal_clicked();
    }
}

void MainWindow::on_pushButton_equal_clicked()
{
    pushButton[2][3]->setChecked(true);
    label_string = label->text();

    // if last on label is operation symbol, remove that symbol
    if (label_string[label_string.size() - 1] == '+' ||
            label_string[label_string.size() - 1] == '-' ||
            label_string[label_string.size() - 1] == '*' ||
            label_string[label_string.size() - 1] == '/') {
        label_string.remove(label_string.size() - 1, 1);
        label->setText(label_string);
    }
    label->setText(parse());
}

void MainWindow::on_pushButton_C_clicked()
{
    label->setText("0");
}
