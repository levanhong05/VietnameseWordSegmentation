#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _segment = new WordSegmentation();

    connect(_segment, SIGNAL(segmentsChanged(QString)), this, SLOT(onSegmentChanged(QString)));

    ui->btnTest->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSegmentChanged(QString text)
{
    ui->listResult->addItem(text);
}

void MainWindow::on_btnTrainingData_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Training Data"), QString(), tr("Text File (*.txt)"));

    if (filePath == "") {
        return;
    }

    if (QFile::exists(filePath)) {
        ui->txtTrainingData->setText(filePath);
    }
}

void MainWindow::on_btnTestData_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Test Data"), QString(), tr("Text File (*.txt)"));

    if (filePath == "") {
        return;
    }

    if (QFile::exists(filePath)) {
        ui->txtTestData->setText(filePath);
    }
}

void MainWindow::on_btnTraining_clicked()
{
    if (QFile::exists(ui->txtTrainingData->text())) {
        bool success = _segment->trainingData(ui->txtTrainingData->text());

        if (success) {
            QMessageBox::information(this, tr("Training Data"), tr("Training data successfully."));

            ui->btnTest->setEnabled(true);
        } else {
            QMessageBox::critical(this, tr("Training Data"), tr("Training data failed."));

            ui->btnTest->setEnabled(false);
        }
    }
}

void MainWindow::on_btnTest_clicked()
{
    if (QFile::exists(ui->txtTestData->text())) {
        _segment->processing(ui->txtTestData->text());
    } else {
        QMessageBox::critical(this, tr("Word Segmentation"), tr("Could not found test data."));
    }
}
