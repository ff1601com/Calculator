#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qDebug>

double firstNum;
bool userTypingSecondNumber = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // digits pressed
    connect(ui->pushButton_0,SIGNAL(released()),this, SLOT(digit_pressed()));
    connect(ui->pushButton_1,SIGNAL(released()),this, SLOT(digit_pressed()));
    connect(ui->pushButton_2,SIGNAL(released()),this, SLOT(digit_pressed()));
    connect(ui->pushButton_3,SIGNAL(released()),this, SLOT(digit_pressed()));
    connect(ui->pushButton_4,SIGNAL(released()),this, SLOT(digit_pressed()));
    connect(ui->pushButton_5,SIGNAL(released()),this, SLOT(digit_pressed()));
    connect(ui->pushButton_6,SIGNAL(released()),this, SLOT(digit_pressed()));
    connect(ui->pushButton_7,SIGNAL(released()),this, SLOT(digit_pressed()));
    connect(ui->pushButton_8,SIGNAL(released()),this, SLOT(digit_pressed()));
    connect(ui->pushButton_9,SIGNAL(released()),this, SLOT(digit_pressed()));

    // decimal pressed
    connect(ui->pushButton_decimal,SIGNAL(released()),this, SLOT(decimal_pressed()));

    // unary operation pressed
    connect(ui->pushButton_plus_minus,SIGNAL(released()),this, SLOT(unary_operation_pressed()));
    connect(ui->pushButton_percent,SIGNAL(released()),this, SLOT(unary_operation_pressed()));

    // clear pressed
    connect(ui->pushButton_clear,SIGNAL(released()),this, SLOT(clear_pressed()));

    // equals pressed
    connect(ui->pushButton_equals,SIGNAL(released()),this, SLOT(equals_pressed()));

    // binary pressed
    connect(ui->pushButton_add,SIGNAL(released()),this, SLOT(binary_operation_pressed()));
    connect(ui->pushButton_subtract,SIGNAL(released()),this, SLOT(binary_operation_pressed()));
    connect(ui->pushButton_multiply,SIGNAL(released()),this, SLOT(binary_operation_pressed()));
    connect(ui->pushButton_divide,SIGNAL(released()),this, SLOT(binary_operation_pressed()));

    // set checkability of binary operations to true
    ui->pushButton_add->setCheckable(true);
    ui->pushButton_subtract->setCheckable(true);
    ui->pushButton_multiply->setCheckable(true);
    ui->pushButton_divide->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


/**
 * handle digit operations
 * @brief MainWindow::digit_pressed
 */
void MainWindow::digit_pressed()
{
    QPushButton *button = (QPushButton*) sender();

    double labelNumber;
    QString newLabel;

    if((ui->pushButton_add->isChecked() || ui->pushButton_subtract->isChecked() ||
       ui->pushButton_multiply->isChecked() || ui->pushButton_divide->isChecked()) && (!userTypingSecondNumber))
    {
        labelNumber = button->text().toDouble();
        userTypingSecondNumber = true;
        newLabel = QString::number(labelNumber, 'g', 15);
    }
    else
    {
        if(ui->label->text().contains(".") && button->text() == "0")
        {
            newLabel = ui->label->text() + button->text();
        }
        else
        {
            labelNumber = (ui->label->text() + button->text()).toDouble();
            newLabel = QString::number(labelNumber, 'g', 15);
        }
    }
    ui->label->setText(newLabel);
}

/**
 * handle decimal operations
 * @brief MainWindow::decimal_pressed
 */
void MainWindow::decimal_pressed()
{
    if(!ui->label->text().contains("."))
    {
      ui->label->setText(ui->label->text().append("."));
    }
}

/**
 * handle unary operations
 * @brief MainWindow::unary_operation_pressed
 */
void MainWindow::unary_operation_pressed()
{
    QPushButton *button = (QPushButton*) sender();
    double labelNumber;
    QString newLabel;

    if(button->text() == "+/-")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * -1;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
    }

    if(button->text() == "%")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * 0.01;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
    }
}

/**
 * handle clear operations, reset calculator
 * @brief MainWindow::clear_pressed
 */
void MainWindow::clear_pressed()
{
    ui->pushButton_add->setChecked(false);
    ui->pushButton_subtract->setChecked(false);
    ui->pushButton_multiply->setChecked(false);
    ui->pushButton_divide->setChecked(false);

    userTypingSecondNumber = false;

    ui->label->setText("0");
}

/**
 * handle equal operations
 * @brief MainWindow::equals_pressed
 */
void MainWindow::equals_pressed()
{
    double labelNumber, secondNum;
    QString newLabel;

    secondNum = ui->label->text().toDouble();

    if(ui->pushButton_add->isChecked())
    {
        labelNumber = firstNum + secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        ui->pushButton_add->setChecked(false);
    }
    else if(ui->pushButton_subtract->isChecked())
    {
        labelNumber = firstNum - secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        ui->pushButton_subtract->setChecked(false);
    }
    else if(ui->pushButton_multiply->isChecked())
    {
        labelNumber = firstNum * secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        ui->pushButton_multiply->setChecked(false);
    }
    else if(ui->pushButton_divide->isChecked())
    {
        labelNumber = firstNum / secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        ui->pushButton_divide->setChecked(false);
    }

    userTypingSecondNumber = false;
}

/**
 * handle binary operations
 * @brief MainWindow::binary_operation_pressed
 */
void MainWindow::binary_operation_pressed()
{
    QPushButton *button = (QPushButton*) sender();

    firstNum = ui->label->text().toDouble();

    button->setChecked(true);
}
