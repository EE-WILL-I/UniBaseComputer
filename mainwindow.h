#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleComputeButton();
    void handleConvertButton();
    void handleConvertDoubleButton();

private:
    Ui::MainWindow *ui;
    QLabel *Output;
    bool isValidInput = true;
};
#endif // MAINWINDOW_H
