#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "wordsegmentation.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onSegmentChanged(QString text);

private slots:
    void on_btnTrainingData_clicked();

    void on_btnTestData_clicked();

    void on_btnTraining_clicked();

    void on_btnTest_clicked();

private:
    Ui::MainWindow *ui;

    WordSegmentation *_segment;
};

#endif // MAINWINDOW_H
