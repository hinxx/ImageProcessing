#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDir>
#include <QString>
#include <QPixmap>
#include <QDebug>
#include <QPushButton>
#include <QEventLoop>
#include <ctime>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_imageButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Select Image","","Bmp Files (*.bmp)");
    ui->imageLine->setText(fileName);
    QPixmap im(fileName);
    ui->image1->setPixmap(im);
}

void MainWindow::on_applyButton_clicked()
{
    QString outName = ui->outNameLine->text();
    if(outName.isEmpty()) outName = "output";
    std::time_t start = std::time(nullptr);
    f.ReadImage(ui->imageLine->text().toUtf8().constData());
    string path = (QDir::currentPath() + "/outputs/" + outName).toUtf8().constData();
    if(ui->comboBox->currentText() == "Convert Grayscale")
    {

        f.grayScale(path);
        std::time_t end = std::time(nullptr);
        qDebug() << "Gecen Sure: " << end-start;
        QPixmap im(QDir::currentPath() + "/outputs/" + outName + ".bmp");
        ui->image2->setPixmap(im);
    }
    else if(ui->comboBox->currentText() == "Draw Rect")
    {
        rectForm.show();
        QObject::connect(&rectForm,SIGNAL(dataReady(QVector<int>)),this,SLOT(getData(QVector<int>)));
        QPushButton *button = rectForm.findChild<QPushButton*>("pushButton");   // instance of button in toplevel window
        QEventLoop loop;
        QObject::connect(button, SIGNAL(clicked(bool)),&loop, SLOT(quit()));
        loop.exec();    // wait to clicked button
        rectForm.close();
        f.grayScale(path);
        f.drawRect(vect.at(0),vect.at(1),vect.at(2),vect.at(3));
        vect.clear();   // clear old data
        f.ExportImage(path);
        QPixmap im(QDir::currentPath() + "/outputs/" + outName + ".bmp");
        ui->image2->setPixmap(im);
    }
    else if(ui->comboBox->currentText() == "Draw Circle")
    {
        circleForm.show();
        QObject::connect(&circleForm,SIGNAL(dataReady(QVector<int>)),this,SLOT(getData(QVector<int>)));
        QPushButton *button = circleForm.findChild<QPushButton*>("pushButton");   // instance of button in toplevel window
        QEventLoop loop;
        QObject::connect(button, SIGNAL(clicked(bool)),&loop, SLOT(quit()));
        loop.exec();    // wait to clicked button
        circleForm.close();
        f.grayScale(path);
        f.drawCircle(vect.at(0),vect.at(1),vect.at(2));
        vect.clear();
        f.ExportImage(path);
        QPixmap im(QDir::currentPath() + "/outputs/" + outName + ".bmp");
        ui->image2->setPixmap(im);
    }
    else if(ui->comboBox->currentText() == "Draw Ellipse")
    {   ellipseForm.show();
        QObject::connect(&ellipseForm,SIGNAL(dataReady(QVector<int>)),this,SLOT(getData(QVector<int>)));
        QPushButton *button = ellipseForm.findChild<QPushButton*>("pushButton");   // instance of button in toplevel window
        QEventLoop loop;
        QObject::connect(button, SIGNAL(clicked(bool)),&loop, SLOT(quit()));
        loop.exec();    // wait to clicked button
        ellipseForm.close();
        f.grayScale(path);
        f.drawEllipse(vect.at(0),vect.at(1),vect.at(2),vect.at(3));
        vect.clear();
        f.ExportImage(path);
        QPixmap im(QDir::currentPath() + "/outputs/" + outName + ".bmp");
        ui->image2->setPixmap(im);
    }
}

void MainWindow::getData(QVector<int> vector)
{
    for(int i=0; i<vector.size();i++)
        vect.append(vector.at(i));
}
