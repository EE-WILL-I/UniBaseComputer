#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<controller.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    connect(ui->Btn_compute, SIGNAL (released()), this, SLOT (handleComputeButton()));
    connect(ui->Btn_convert, SIGNAL (released()), this, SLOT (handleConvertButton()));
    this->setWindowTitle("UniBase Computer");
}

void MainWindow::handleComputeButton()
{
    Output = ui->Lbl_result;
    QTextEdit *input1 = ui->input_N1,
            *input2 = ui->input_N3;

    controller *controllModule = new controller();

    QString input_n1 = input1->toPlainText(),
            input_n2 = input2->toPlainText();

    controllModule->SetInput(input_n1.toStdString(), input_n2.toStdString());
    ui->Lbl_operation->setText(controllModule->GetInfo().c_str());
    controllModule->Select();

    string text = controllModule->Print();
    Output->setText(text.c_str());
}
void MainWindow::handleConvertButton()
{
    Output = ui->Lbl_result2;
    QTextEdit *input1 = ui->input_C1,
            *input2 = ui->input_C2,
            *input3 = ui->input_C3;

    controller *controllModule = new controller();

    QString input_n1 = input1->toPlainText(),
            input_n2 = input2->toPlainText(),
            input_n3 = input3->toPlainText();

    string text = controllModule->Convert(input_n1.toStdString(), stoi(input_n2.toStdString()), stoi(input_n3.toStdString()));
    Output->setText(text.c_str());
}

MainWindow::~MainWindow()
{
    delete ui;
}

