#ifndef JCDEMOSHEET_H
#define JCDEMOSHEET_H

#include <QWidget>
#include <QTableView>

#include "TableModel.h"

class JCDemoSheet : public QWidget
{
    Q_OBJECT

public:
    JCDemoSheet(QWidget *parent = nullptr);
    ~JCDemoSheet();

private:
    TableModel *tableModel = nullptr;
    QTableView *tableView = nullptr;
    QString iniFile;


    bool createIniFile(QString &name);
    void setupUi(void);
    void initialize(void);
};

#endif // JCDEMOSHEET_H
