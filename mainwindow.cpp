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
    isValidInput = true;
    Output = ui->Lbl_result;

    controller *controllModule = new controller();

    QString input_n1 = ui->input_N1->toPlainText(),
            input_n2 = ui->input_N3->toPlainText();

    std::list<QString> strings = {input_n1, input_n2};
    for(QString s: strings) if(s.toStdString().empty())
    {
        isValidInput = false;
        break;
    }

    if(isValidInput)
    {
        controllModule->SetInput(input_n1.toStdString(), input_n2.toStdString());
        ui->Lbl_operation->setText(controllModule->GetInfo().c_str());
        controllModule->Select();

        string out = controllModule->Print();
        Output->setText(out.c_str());
    }
    else Output->setText("Недопустимый ввод");
}
void MainWindow::handleConvertButton()
{
    isValidInput = true;
    Output = ui->Lbl_result2;

    controller *controllModule = new controller();

    QString input_n1 = ui->input_C1->toPlainText(),
            input_n2 = ui->input_C2->toPlainText(),
            input_n3 = ui->input_C3->toPlainText();

    std::list<QString> strings = {input_n1, input_n2, input_n3};
    for(QString s: strings) if(s.toStdString().empty())
    {
        isValidInput = false;
        break;
    }

    if(isValidInput)
    {
        string out = controllModule->Convert(input_n1.toStdString(), stoi(input_n2.toStdString()), stoi(input_n3.toStdString()));
        Output->setText(out.c_str());
    }
    else Output->setText("Недопустимый ввод");
}

MainWindow::~MainWindow()
{
    delete ui;
}

