#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget_map->resize(941,525);

    QObject::connect(ui->widget_search,SIGNAL(emitSearchRequestData(QVector<float>,float,QVector<QVector<float>>)),this,SLOT(getSearchRequestData(QVector<float>,float,QVector<QVector<float>>)),Qt::QueuedConnection);
    QObject::connect(ui->widget_direction,SIGNAL(emitPathData(QVector<float>,QVector<float>)),this,SLOT(getPathData(QVector<float>,QVector<float>)),Qt::QueuedConnection);
    QObject::connect(ui->widget_map, SIGNAL (EmitCoordinates(int,int)), ui->widget_direction, SLOT(updateCoordinates(int,int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getSearchRequestData(QVector<float> listCoNameMatch,float radius,QVector<QVector<float>> listCoTypeMatch)
{

    QString radius_val;
    QString nameco_val;
    QString typeco_val;

    for (int i=0;i<listCoNameMatch.size();i++) {
        QString a;
        a.setNum(listCoNameMatch[i]);
        nameco_val.append(a+",");
    }

    for (int i=0;i<listCoTypeMatch.size();i++) {
        for (int j=0;j<listCoTypeMatch[i].size();j++) {
            QString b;
            b.setNum(listCoTypeMatch[i][j]);
            typeco_val.append(b+",");
        }
        typeco_val.append(";");
    }

    radius_val.setNum(radius);

    ui->label->setText(nameco_val);

    ui->label_3->setText(radius_val);

    ui->label_5->setText(typeco_val);
}

void MainWindow::getPathData(QVector<float> source, QVector<float> dest)
{
    QString source_val;
    QString dest_val;
    for (int i=0;i<source.size();i++) {
        QString a;
        a.setNum(source[i]);
        source_val.append(a+",");
    }
    for (int i=0;i<dest.size();i++) {
        QString b;
        b.setNum(dest[i]);
        dest_val.append(b+",");
    }
    ui->label->setText(source_val);
    ui->label_5->setText(dest_val);

}

