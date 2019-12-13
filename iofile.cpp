#include "iofile.h"
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDebug>
IOFile::IOFile()
{

}

//read data from text file and store it to the list of name, coordinate, type
bool IOFile::readFromFile()
{
    QFile inputFile(path);
    QString line;
    QStringList list;
    if (!inputFile.open(QIODevice::ReadOnly)) //open file to read only mode.
    {
            qDebug("The file can not be opened to read."); //throw error if can't open file
            exit(1);
    }

    QTextStream in(&inputFile);
    name_list.clear();
    coordinate_list.clear();
    type_list.clear();
    while (!in.atEnd()) //while not end of file
    {
      line = in.readLine();  //read one line
      list = line.split(';'); //split data line to list string ["name","lat,lon","type"]

      name_list.append(list.value(0)); //save string name to the list of name
      coordinate_list.append(list.value(1)); //same for lat,lon
      type_list.append(list.value(2)); //same for type
    }
    //qDebug("%s",qUtf8Printable(name_list.value(0)));
    inputFile.close();
    return true;
}

//add new data line to text file
bool IOFile::writeToFile(QString name, QString coordinate, QString type)
{
    if(name_list.contains(name,Qt::CaseInsensitive))
    {
        qDebug("Place name already exists!");
        return false;
    }
    if(coordinate_list.contains(coordinate,Qt::CaseInsensitive))
    {
        qDebug("Coordinate already exists!");
        return false;
    }

    QFile inputFile(path);
    if (!inputFile.open(QIODevice::Append)) //open file in append mode. Throw error if cant open file
    {
            qDebug("The file can not be opened to write.");
            return false;
    }
    QTextStream out(&inputFile);
    QString inputString;
    QString separate = ";";
    inputString.append(name+separate);  //append strings
    inputString.append(coordinate + separate);
    inputString.append(type + separate);
    //qDebug("%s",qUtf8Printable(inputString));
    out << inputString << endl; //write string line to text file
    inputFile.close();
    return true;
}

QStringList IOFile::getNameList()
{
    return name_list;
}

QStringList IOFile::getTypeList()
{
    return type_list;
}

QStringList IOFile::getCoordinateList()
{
    return coordinate_list;
}

//Separate single string "lat,lon" to list string of ["lat","lon"]
QStringList IOFile::getLatLon(QString coordinate)
{
    QStringList listCoordinate;
    listCoordinate = coordinate.split(",");
    return listCoordinate;
}

QVector<QVector<float>> IOFile::getCoordinateByType1(QString type)
{
    QVector<int> match_index;
    QStringList matchCoordinate;
    QString coordinate;
    QStringList lat;
    QVector<QVector<float>> listMatch;


        //memset(listMatchCoordinate,0,10*2*sizeof(float));
        match_index = getIndexesOfMatchElements(type);

        for(int i = 0; i<match_index.size();i++)
        {
            QVector<float> element;
            coordinate = coordinate_list.at(match_index.at(i));
            matchCoordinate = coordinate.split(",");
            element.append(matchCoordinate.at(0).toFloat());
            element.append(matchCoordinate.at(1).toFloat());
            listMatch.append(element);
        }
        //qDebug()<<match_index;
        //qDebug()<< listMatch;
        return listMatch;

}

QVector<float> IOFile::getCoordinateByName(QString name)
{
    QVector<int> match_index;
    QStringList matchCoordinate;
    QString coordinate;
    QVector<float> listMatch;
    int index;
    index = name_list.indexOf(name);
    coordinate = coordinate_list.at(index);
    matchCoordinate = coordinate.split(",");
    listMatch.append(matchCoordinate.at(0).toFloat());
    listMatch.append(matchCoordinate.at(1).toFloat());

    return listMatch;
}

int IOFile::getCoordinateByType(QString type,float listMatchCoordinate[10][2])
{
    QVector<int> match_index;
    QStringList matchCoordinate;
    QString coordinate;
    QStringList lat;
    QVector<QVector<float>> listMatch;
    if(type.isEmpty())
    {
        return 0;
    }
    else
    {
        memset(listMatchCoordinate,0,10*2*sizeof(float));
        match_index = getIndexesOfMatchElements(type);
        for(int i = 0; i<match_index.size();i++)
        {
            coordinate = coordinate_list.at(match_index.at(i));
            matchCoordinate = coordinate.split(",");
            listMatchCoordinate[i][0] = matchCoordinate.at(0).toFloat();
            listMatchCoordinate[i][1] = matchCoordinate.at(1).toFloat();
        }
        //qDebug()<< listMatchCoordinate[0][0];
        //qDebug()<< listMatchCoordinate[1][0];
        return match_index.size();
    }
}

QVector<int> IOFile::getIndexesOfMatchElements(QString type, int index)
{
    int match = 0;
    QVector<int> matches;
    while(index < type_list.size())
    {
        match = type_list.indexOf(type, index);
        if(match == -1) break;
        matches.append(match);
        index = match + 1;
    }
    return matches;
}




