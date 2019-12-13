#ifndef IOFILE_H
#define IOFILE_H
#include<QString>
#include<QDir>
class IOFile
{
public:
    IOFile();
    bool readFromFile();
    bool writeToFile(QString name,QString coordinate,QString type);
    QStringList getNameList();
    QStringList getCoordinateList();
    QStringList getTypeList();
    QStringList getLatLon(QString);
    int getCoordinateByType(QString,float listMatchCoordinate[10][2]);
    QVector<QVector<float>> getCoordinateByType1(QString);
    QVector<float> getCoordinateByName(QString);
    QVector<int> getIndexesOfMatchElements(QString,int index = 0);
private:
    QString path = QDir::current().absolutePath()+"/mapdata.txt";
    QStringList name_list;
    QStringList coordinate_list;
    QStringList type_list;
    //float listMatchCoordinate[10][2] = {0};
};

#endif // IOFILE_H
