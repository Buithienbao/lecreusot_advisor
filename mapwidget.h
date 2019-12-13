#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPoint>
#include <QMouseEvent>
#include <QLabel>
#include <QPainter>
class MapWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MapWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void setPixMap(QString filename);
signals:
    void EmitCoordinates(int,int);
public slots:

private:
    QPixmap pixmap;
};

#endif // MAPWIDGET_H
