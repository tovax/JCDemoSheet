#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QObject>
#include <QAbstractTableModel>

/*!
 * @brief Table Model
 * @details
 * @note
 */
class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    TableModel(QObject *parent = nullptr,
                            const QStringList &hHeaderList = QStringList(),
                            const QStringList &vHeaderList = QStringList(),
                            QString fil = QString());
    ~TableModel();

    int32_t rowCount(const QModelIndex &parent) const;
    int32_t columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int32_t role);
    QVariant headerData(int32_t section, Qt::Orientation orientation, int32_t role) const;
    bool setHeaderData(int32_t section, Qt::Orientation orientation, const QVariant &value, int32_t role);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

private:
    QString iniFile = QString();                //!< Ini File
    QStringList horizontalHeaderList;           //!< Horizontal Header List
    QStringList verticalHeaderList;             //!< Vertical Header List
};

#endif // TABLEMODEL_H
