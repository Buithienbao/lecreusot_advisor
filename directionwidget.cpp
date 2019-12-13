#include "directionwidget.h"
#include "ui_directionwidget.h"

DirectionWidget::DirectionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DirectionWidget)
{
    ui->setupUi(this);
    iofile->readFromFile();

    nameList = iofile->getNameList();
    setSourceList();
    setDestinationList();
    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base,Qt::gray);
    palette->setColor(QPalette::Text,Qt::white);
    ui->mapCheckBox->setCheckState(Qt::Unchecked);
    ui->listCheckBox->setCheckState(Qt::Unchecked);
    ui->directionSourceComboBox->setEnabled(false);
    ui->directionDestinationComboBox->setEnabled(false);
    ui->sourceRadioButton->setEnabled(false);
    ui->destinationRadioButton->setEnabled(false);
    ui->directionButton->setEnabled(false);
    ui->directionByMapButton->setEnabled(false);
    ui->lineEdit->setPlaceholderText("Source Value");
    ui->lineEdit_2->setPlaceholderText("Destination Value");
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit->setPalette(*palette);
    ui->lineEdit_2->setReadOnly(true);
    ui->lineEdit_2->setPalette(*palette);
}

DirectionWidget::~DirectionWidget()
{
    delete ui;
}

void DirectionWidget::setSourceList()
{


    QStringListModel *stringListModel = new QStringListModel;
    stringListModel->setStringList(nameList);

    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel;
    proxyModel->setSourceModel(stringListModel);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    auto completer = new QCompleter(this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setModel(proxyModel);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    completer->setFilterMode(Qt::MatchContains);
    completer->setMaxVisibleItems(4);
    ui->directionSourceComboBox->setModel(proxyModel);
    ui->directionSourceComboBox->setEditable(true);
    ui->directionSourceComboBox->setCompleter(completer);
}

void DirectionWidget::setDestinationList()
{


    QStringListModel *stringListModel = new QStringListModel;
    stringListModel->setStringList(nameList);

    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel;
    proxyModel->setSourceModel(stringListModel);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    auto completer = new QCompleter(this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setModel(proxyModel);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    completer->setFilterMode(Qt::MatchContains);
    completer->setMaxVisibleItems(4);
    ui->directionDestinationComboBox->setModel(proxyModel);
    ui->directionDestinationComboBox->setEditable(true);
    ui->directionDestinationComboBox->setCompleter(completer);
}


void DirectionWidget::on_listCheckBox_stateChanged(int arg1)
{
    if(arg1 == 0)
    {
        ui->directionSourceComboBox->setEnabled(false);
        ui->directionDestinationComboBox->setEnabled(false);
        ui->directionButton->setEnabled(false);
    } else if(arg1 == 2)
    {
        ui->directionSourceComboBox->setEnabled(true);
        ui->directionDestinationComboBox->setEnabled(true);
        ui->directionButton->setEnabled(true);
        ui->mapCheckBox->setCheckState(Qt::Unchecked);
    }
}



void DirectionWidget::on_mapCheckBox_stateChanged(int arg1)
{
    if(arg1 == 0)
    {
        ui->sourceRadioButton->setEnabled(false);
        ui->destinationRadioButton->setEnabled(false);
        ui->directionByMapButton->setEnabled(false);
    } else if(arg1 == 2)
    {
        ui->sourceRadioButton->setEnabled(true);
        ui->destinationRadioButton->setEnabled(true);
        ui->directionByMapButton->setEnabled(true);
        ui->listCheckBox->setCheckState(Qt::Unchecked);
    }
}

void DirectionWidget::on_directionButton_clicked()
{

    QString source = ui->directionSourceComboBox->currentText();
    QString destination = ui->directionDestinationComboBox->currentText();
    if(!nameList.contains(source))
    {
        QMessageBox::warning(this,"Warning","Source name does not exist!");
        return;
    }
    if(!nameList.contains(destination))
    {
        QMessageBox::warning(this,"Warning","Destination name does not exist!");
        return;
    }
    if(source == destination)
    {
        QMessageBox::warning(this,"Warning","Source and destination must be different!");
        return;
    }
    sourceCoordinate.clear();
    destCoordinate.clear();
    sourceCoordinate = iofile->getCoordinateByName(source);
    destCoordinate = iofile->getCoordinateByName(destination);
    emitPathData(sourceCoordinate,destCoordinate);
}

void DirectionWidget::on_directionByMapButton_clicked()
{

    if(!sourceTextChanged)
    {
        QMessageBox::information(this,"Information","Please choose source point!");
        return;
    }
    if(!destTextChanged)
    {
        QMessageBox::information(this,"Information","Please choose destination point!");
        return;
    }
//    qDebug()<<source_val;
//    qDebug()<<destination_val;
//    qDebug()<<sourceCoordinate;
//    qDebug()<<destCoordinate;
    emitPathData(sourceCoordinate,destCoordinate);

}

void DirectionWidget::on_lineEdit_textChanged(const QString &arg1)
{
    sourceTextChanged = true;
    source_val = arg1;
}


void DirectionWidget::on_lineEdit_2_textChanged(const QString &arg1)
{
    destTextChanged = true;
    destination_val = arg1;
}

void DirectionWidget::updateCoordinates(int x_val, int y_val)
{

    QString a;
    a.append(QString::number(x_val));
    a.append(",");
    a.append(QString::number(y_val));
    if(ui->sourceRadioButton->isChecked())
    {
        sourceCoordinate.clear();
        sourceCoordinate.append(x_val);
        sourceCoordinate.append(y_val);
        ui->lineEdit->setText(a);
    } else if(ui->destinationRadioButton->isChecked())
    {
        destCoordinate.clear();
        destCoordinate.append(x_val);
        destCoordinate.append(y_val);
        ui->lineEdit_2->setText(a);
    } else {
        return;
    }


}
