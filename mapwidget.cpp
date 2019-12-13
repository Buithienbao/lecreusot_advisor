#include "mapwidget.h"

MapWidget::MapWidget(QWidget *parent) : QWidget(parent)
{

}
void MapWidget::mousePressEvent(QMouseEvent *e)
{
    const QPoint p = e->pos();
    emit EmitCoordinates(p.x(),p.y());
}

void MapWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QString filename = "/home/bao/Pictures/le_creusot.png";
    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);
    setPixMap(filename);
    if (pixmap.isNull()) {
        painter.setPen(Qt::green);
        painter.drawText(rect(), Qt::AlignCenter, tr("Rendering initial image, please wait..."));
        return;
    } else
    {
        painter.drawPixmap(0,0,pixmap);
    }

}

void MapWidget::setPixMap(QString filename)
{
    pixmap = QPixmap(filename);
}
