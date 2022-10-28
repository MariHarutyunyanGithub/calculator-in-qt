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
    setStyleSheet("background-color: grey");
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

void MainWindow::set_font()
{
    QFont font = label->font();
    if (label->text().size() < 6) {
        font.setPointSize(30);
    }
    else if (label->text().size() >= 6 && label->text().size() < 10) {
        font.setPointSize(25);
    }
    else {
        for (int i{10}, j{23}; i < 17; ++i, --j) {
            if (label->text().size() == i) {
                font.setPointSize(j);
            }
        }
    }
    label->setFont(font);
}

//numerical buttons
void MainWindow::digit_buttons()
{
    QPushButton *pushButton1 = (QPushButton*)sender();
    set_font();
    if (label->text().size() <= 17) {
        if (big_pushButton[2]->isChecked() ||
                pushButton[2][3]->isChecked() ||
                label->text() == "0") {
            label->setText(pushButton1->text());
            pushButton[2][3]->setChecked(false);
            big_pushButton[2]->setChecked(false);
        }
        else {
            // do not allow a zero to be written at the beginning of the number
            label_string = label->text();
            if (label_string.size() >= 3 &&
                    label_string[label_string.size() - 1] == '0' &&
                    (label_string[label_string.size() - 2] == '+' ||
                    label_string[label_string.size() - 2] == '-' ||
                    label_string[label_string.size() - 2] == 'x' ||
                    label_string[label_string.size() - 2] == '/')){
                label->setText(label_string.remove(label_string.size() - 1, 1)
                               + pushButton1->text());
            }
            else {
                label->setText(label->text() + pushButton1->text());
            }
        }
    }
}

// buttons "+", "-", "x", "/"
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
        // delete the last zeros of a fractional number
        if (label_string[label_string.size() - 1] == '0')
            {
            int i = label_string.size() - 1;
            int dot_count{};
            while(label_string[i] != '+' &&
                  label_string[i] != '-' &&
                  label_string[i] != 'x' &&
                  label_string[i] != '/' &&
                  i > 0) {
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
        // if there is a dot at the end of the line, delete it
        if (label_string[label_string.size() - 1] == '.') {
            label_string.remove(label_string.size() - 1, 1);
            label->setText(label_string);
        }
        // we can change the action symbol written at the end of the line
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

// buttons "%", "<--", "C", ".", "="
void MainWindow::operations()
{
    QPushButton *button = (QPushButton*)sender();
    if (pushButton[2][3]->isChecked()) {
        pushButton[2][3]->setChecked(false);
    }

    if(button->text() == '%') {
        on_persent_clicked();
    }
    else if (button->text() == "<--") {
        on_back_clicked();
    }
    else if (button->text() == "C") {
        on_C_clicked();
    }
    else if (button->text() == ".") {
        on_dot_clicked();
    }
    else {
        on_equal_clicked();
    }
}

// parses label->text()
QString MainWindow::parse()
{
    label_string = label->text();
    int i = label_string.size() - 1;
    // if there are no action characters in the string, return the string itself
    bool oper_exists{};
    while (i >= 0) {
        if (label_string[i] == '+' ||
                label_string[i] == '-' ||
                label_string[i] == 'x' ||
                label_string[i] == '/') {
            oper_exists = true;
            break;
        }
        --i;
    }
    if (!oper_exists) {
        return label_string;
    }
    // otherwise if there is at least one action token
    else {
        QString token{};
        QList<QString> num_list{};
        QList<QString> oper_list{};
        // split the string into tokens
        i = 0;
        while (i < label_string.size()) {
            if (label_string[i] != '+' &&
                   label_string[i] != '-' &&
                   label_string[i] != 'x' &&
                   label_string[i] != '/') {
                token += label_string[i];
            }
            else { // store numbers in a separate list, operation symbols separately
                num_list.push_back(token);
                oper_list.push_back(label_string[i]);
                token = "";
            }
            ++i;
        }
        num_list.push_back(token);
        double first{};
        double second{};
        QString result{};
        // perform the actions with high priority, leaving only the actions
        // with low priority in the list. And replace the corresponding
        // operands with the result of the operation

        for (int i{}; i < oper_list.size(); ++i) {
            if (oper_list[i] == "x") {
                oper_list.removeAt(i);
                first = num_list[i].toDouble();
                second = num_list[i + 1].toDouble();
                result = QString::number(first * second);
                num_list.removeAt(i);
                num_list.removeAt(i);
                num_list.insert(i, result);
                --i;
            }
            else if (oper_list[i] == "/") {
                oper_list.removeAt(i);
                first = num_list[i].toDouble();
                second = num_list[i + 1].toDouble();
                result = QString::number(first / second);
                num_list.removeAt(i);
                num_list.removeAt(i);
                num_list.insert(i, result);
                --i;
            }
        }

        // perform the actions one by one, collecting the result of the action
        double result1{};
        if (oper_list.isEmpty()) {
            return num_list.first();
        }
        do {
            if (oper_list.first() == "+") {
                result1 = num_list[0].toDouble() + num_list[1].toDouble();
                num_list.pop_front();
                num_list.pop_front();
                result = QString::number(result1);
                num_list.push_front(result);
                oper_list.pop_front();
            }
            else if (oper_list.first() == "-") {
                result1 = num_list[0].toDouble() - num_list[1].toDouble();
                num_list.pop_front();
                num_list.pop_front();
                result = QString::number(result1);
                num_list.push_front(result);
                oper_list.pop_front();
            }
        } while (!oper_list.isEmpty());
       return num_list.first();
    }
}

void MainWindow::on_back_clicked()
{
    set_font();
    label->setText((label->text()).remove(label->text().size() - 1, 1));

    if (label->text() == "") {
        label->setText("0");
    }
}

void MainWindow::on_persent_clicked()
{
    double numbers{};
    QString result1{};
    bool is_number_string{true};
    label_string = label->text();
    if (label->text() == "0." || label->text() == "0") {
        label->setText("0");
    }
    else {
        int oper_count{};
        for(int i{}; i < label_string.size(); ++i) {
            if (label_string[i] == '+' ||
                    label_string[i] == '-' ||
                    label_string[i] == 'x' ||
                    label_string[i] == '/') {
                oper_count++;
                is_number_string = false;
            }
        }
        if (is_number_string) {
            if (label_string.contains(".")) {
                int count_of_0s{};
                for (int i = label_string.size() - 1; i >= 0; --i) {
                    if (label_string[i] != '0') {
                        label_string.remove(i + 1, count_of_0s);
                        break;
                    }
                    ++count_of_0s;
                }
            }
             numbers = label_string.toDouble();
        }
        // if label contains exactly one operator, it is at the end, delete it
        else if (oper_count == 1 &&
                 (label_string[label_string.size() - 1] == '+' ||
                 label_string[label_string.size() - 1] == '-' ||
                 label_string[label_string.size() - 1] == 'x' ||
                 label_string[label_string.size() - 1] == '/')) {
            label_string.remove(label_string.size() - 1, 1);
            numbers = label_string.toDouble();
        }
        // otherwise
        else {
            numbers = parse().toDouble();
        }
         numbers /= double(100);
         result1 = QString::number(numbers);
         // delete the last zeros from the fractional result
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
         set_font();
         if (result1 == "0.") {
             result1 = "0";
         }
         label->setText(result1);
    }
}

void MainWindow::on_dot_clicked()
{
    if (pushButton[2][3]->isChecked() ||
            big_pushButton[2]->isChecked() ||
            label->text() == "0") {
        pushButton[2][3]->setChecked(false);
        big_pushButton[2]->setChecked(false);
        label->setText("0.");
    }
    // if we click a dot after the action symbol
    else {
        label_string = label->text();
        if (label_string[label_string.size() - 1] == '+' ||
                label_string[label_string.size() - 1] == '-' ||
                label_string[label_string.size() - 1] == 'x' ||
                label_string[label_string.size() - 1] == '/' ||
                label_string[label_string.size() - 1] == '%') {
            label->setText(label->text() + "0.");
        }
        // if the last number does not contain a dot symbol, set the symbol
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

void MainWindow::on_equal_clicked()
{
    pushButton[2][3]->setChecked(true);
    label_string = label->text();
    // if last on label is operation symbol, remove that symbol
    if (label_string[label_string.size() - 1] == '+' ||
            label_string[label_string.size() - 1] == '-' ||
            label_string[label_string.size() - 1] == 'x' ||
            label_string[label_string.size() - 1] == '/') {
        label_string.remove(label_string.size() - 1, 1);
        label->setText(label_string);
    }
    // delete the zeros written at the end of the fractional number
    if (label_string[label_string.size() - 1] == '0')
        {
        int i = label_string.size() - 1;
        int dot_count{};
        while(label_string[i] != '+' &&
              label_string[i] != '-' &&
              label_string[i] != 'x' &&
              label_string[i] != '/' &&
              i > 0) {
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
    // if there is a dot at the end of the number, delete it
    if (label_string[label_string.size() - 1] == '.') {
        label_string.remove(label_string.size() - 1, 1);
        label->setText(label_string);
    }
    set_font();
    label->setText(parse());
}

void MainWindow::on_C_clicked()
{
    pushButton[2][3]->setChecked(false);
    big_pushButton[2]->setChecked(false);
    label->setText("0");
}
