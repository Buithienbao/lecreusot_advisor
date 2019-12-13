#ifndef DIRECTIONWIDGET_H
#define DIRECTIONWIDGET_H

#include <QWidget>
#include <QCompleter>
#include <QSortFilterProxyModel>
#include <QStringListModel>
#include <iofile.h>
#include <QComboBox>
#include <QMessageBox>
#include <QDebug>
namespace Ui {
class DirectionWidget;
}

class DirectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DirectionWidget(QWidget *parent = nullptr);
    ~DirectionWidget();
    void setSourceList();
    void setDestinationList();
signals:
    void emitPathData(QVector<float>,QVector<float>);
private slots:
    void on_listCheckBox_stateChanged(int arg1);

    void on_mapCheckBox_stateChanged(int arg1);

    void on_directionButton_clicked();

    void on_directionByMapButton_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void updateCoordinates(int,int);
private:
    Ui::DirectionWidget *ui;
    IOFile *iofile = new IOFile();
    bool radbutton1 = false;
    bool radbutton2 = false;
    QStringList nameList;
    QStringList typeList;
    QString source_val;
    QString destination_val;
    QVector<float> sourceCoordinate;
    QVector<float> destCoordinate;
    bool sourceTextChanged = false;
    bool destTextChanged = false;
};

#endif // DIRECTIONWIDGET_H
