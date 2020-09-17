#include "JCDemoSheet.h"

#include <QDebug>
#include <QApplication>
#include <QHeaderView>
#include <QLayout>
#include <QFile>

#include "Sheet.h"

JCDemoSheet::JCDemoSheet(QWidget *parent) : QWidget(parent)
{
    // 1
    if (createIniFile(iniFile)) {
        qDebug() << __FUNCTION__ << QString("Create ini file success: %1").arg(iniFile);
    } else {
        qDebug() << __FUNCTION__ << QString("Create ini file failed: %1").arg(iniFile);
        return;
    }

    // 2
    showMaximized();

    // 3
    setupUi();

    // 4
    initialize();
}

JCDemoSheet::~JCDemoSheet()
{

}

bool JCDemoSheet::createIniFile(QString &name)
{
    bool ret = false;

    name = QString("%1/%2.ini").arg(QApplication::applicationDirPath()).arg(QApplication::applicationName());
    QFile file(name);

    if (file.exists() == false) {
        if (file.open(QIODevice::ReadWrite | QIODevice::Text) == true) {
            ret = true; // create success
        } else {
            ret = false; // create failed
        }
    } else {
        ret = true; // exist
    }

    file.close();

    return ret;
}

void JCDemoSheet::setupUi()
{
    // 1 - TableModel
    QStringList hHeaderList;
    hHeaderList.clear();
    for (int32_t columnIndex = SheetColumn::Min; columnIndex <= SheetColumn::Max; columnIndex++) {
        hHeaderList.append(SheetColumn::Text[columnIndex]);
    }

    QStringList vHeaderList;
    vHeaderList.clear();
    for (int32_t rowIndex = 0; rowIndex < 30; rowIndex++) {
        vHeaderList.append(QString::number(rowIndex + 1));
    }

    tableModel = new TableModel(this, hHeaderList, vHeaderList, iniFile);

    // 2 - TableView
    tableView = new QTableView(this);
    tableView->setModel(tableModel);

    tableView->setFrameShape(QFrame::StyledPanel);
    tableView->horizontalHeader()->setVisible(true);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->verticalHeader()->setVisible(true);
    tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    tableView->setAlternatingRowColors(true);
    tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    // 3 - MainLayout
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0); // left top right bottom
    mainLayout->addWidget(tableView, 0, 0);
    mainLayout->setRowStretch(0, 1);
    mainLayout->setColumnStretch(0, 1);
    this->setLayout(mainLayout);
}

void JCDemoSheet::initialize()
{

}


