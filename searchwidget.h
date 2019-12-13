#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>
#include <QCompleter>
#include <QSortFilterProxyModel>
#include <QStringListModel>
#include <iofile.h>
#include <QComboBox>
#include <QLabel>
#include <QMessageBox>
namespace Ui {
class SearchWidget;
}

class SearchWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SearchWidget(QWidget *parent = nullptr);
    ~SearchWidget();

    void setNameList();
    void setTypeList();
signals:
    void emitSearchRequestData(QVector<float>,float,QVector<QVector<float>>);
private slots:
    void on_searchButton_clicked();

private:
    Ui::SearchWidget *ui;

    QStringList nameList;
    QStringList typeList;

    QString name;
    QString type;
    float radius;
    IOFile *iofile = new IOFile();
};

#endif // SEARCHWIDGET_H
