#include "searchwidget.h"
#include "ui_searchwidget.h"
#include <QDebug>

SearchWidget::SearchWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchWidget)
{
    ui->setupUi(this);

    setNameList();
    setTypeList();
    QComboBox *new_list = new QComboBox();

}

SearchWidget::~SearchWidget()
{
    delete ui;
}

void SearchWidget::setNameList()
{


            iofile->readFromFile();

            nameList = iofile->getNameList();

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
            ui->searchByNameComboBox->setModel(proxyModel);
            ui->searchByNameComboBox->setEditable(true);
            ui->searchByNameComboBox->setCompleter(completer);

}

void SearchWidget::setTypeList()
{

    iofile->readFromFile();

    typeList = iofile->getTypeList();
    typeList.removeDuplicates();
    QStringListModel *stringListModel = new QStringListModel;
    stringListModel->setStringList(typeList);

    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel;
    proxyModel->setSourceModel(stringListModel);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    auto completer = new QCompleter(this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setModel(proxyModel);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    completer->setFilterMode(Qt::MatchContains);
    completer->setMaxVisibleItems(4);
    ui->searchByTypeComboBox->setModel(proxyModel);
    ui->searchByTypeComboBox->setEditable(true);
    ui->searchByTypeComboBox->setCompleter(completer);
}

void SearchWidget::on_searchButton_clicked()
{
    QVector<QVector<float>> listCoTypeMatch;
    QVector<float> listCoNameMatch;
    name = ui->searchByNameComboBox->currentText();
    type = ui->searchByTypeComboBox->currentText();
    radius = ui->radiusLineEdit->text().toFloat();
    if(!nameList.contains(name))
    {
        QMessageBox::warning(this,"Warning","Name does not exist!");
        return;
    }
    if(!typeList.contains(type))
    {
        QMessageBox::warning(this,"Warning","Type does not exist!");

        return;
    }
    listCoTypeMatch = iofile->getCoordinateByType1(type);
    listCoNameMatch = iofile->getCoordinateByName(name);
    emitSearchRequestData(listCoNameMatch,radius,listCoTypeMatch);
}
