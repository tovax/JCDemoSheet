#include "TableModel.h"

#include <QDebug>
#include <QSettings>

#include "Sheet.h"

TableModel::TableModel(QObject *parent, const QStringList &hHeaderList, const QStringList &vHeaderList, QString fil) : QAbstractTableModel(parent)
{
    beginResetModel();

    horizontalHeaderList = hHeaderList;

    verticalHeaderList = vHeaderList;

    iniFile = fil;

    endResetModel();

}

TableModel::~TableModel()
{

}
/*!
 * @brief Row Count
 * @details
 * @note
 */
int32_t TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return verticalHeaderList.count();
}

/*!
 * @brief Column Count
 * @details
 * @note
 */
int32_t TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return horizontalHeaderList.count();
}

/*!
 * @brief Get Data
 * @details
 * @note
 */
QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    QVariant variant = QVariant();

    if (role == Qt::TextAlignmentRole) {
        variant = int32_t(Qt::AlignCenter);
    } else if ((role == Qt::EditRole) || (role == Qt::DisplayRole)) {
        // ini file
        QSettings settings(iniFile, QSettings::IniFormat);
        // begin
        settings.beginGroup(SheetGroup::Text);
        // get value
        QString key = QString("R%1C%2").arg(index.row()).arg(index.column());
        variant = settings.value(key);
        // end
        settings.endGroup();
    } else {
        variant = QVariant();
    }

    return variant;
}

/*!
 * @brief Set Data
 * @details
 * @note
 */
bool TableModel::setData(const QModelIndex &index, const QVariant &value, int32_t role)
{
    qDebug() << __FUNCTION__;

    QVector<int32_t> rolesVector(1, role);

    if (!index.isValid()) {
        return false;
    }

    if ((role == Qt::EditRole) || (role == Qt::DisplayRole)) {


        // ini file
        QSettings settings(iniFile, QSettings::IniFormat);
        // begin
        settings.beginGroup(SheetGroup::Text);
        // set value
        QString key = QString("R%1C%2").arg(index.row()).arg(index.column());
        settings.setValue(key, value);
        // end
        settings.endGroup();
        // emit signal
        emit dataChanged(index, index, rolesVector);
    }

    return true;
}

/*!
 * @brief Get Header Data
 * @details
 * @note
 */
QVariant TableModel::headerData(int32_t section, Qt::Orientation orientation, int32_t role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            return horizontalHeaderList[section];
        } else if (orientation == Qt::Vertical) {
            return verticalHeaderList[section];
        } else {
            return QVariant();
        }
    }
    return QVariant();
}

/*!
 * @brief Set Header Data
 * @details
 * @note
 */
bool TableModel::setHeaderData(int32_t section, Qt::Orientation orientation, const QVariant &value, int32_t role)
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            horizontalHeaderList[section] = value.toString();
        } else if (orientation == Qt::Vertical) {
            verticalHeaderList[section] = value.toString();
        } else {
            return false;
        }
        emit headerDataChanged(orientation, section, section); // replace by HeaderChange
    }
    return true;
}

/*!
 * @brief
 * @details
 * @note
 */
Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    flags |= Qt::ItemIsEditable;
    return flags;
}

/*!
 * @brief Insert Rows
 * @details
 * @note
 */
bool TableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if (row > rowCount(QModelIndex())) {
        return false;
    }

    // important
    beginResetModel();
    endResetModel();

    return true;
}

/*!
 * @brief Remove Rows
 * @details
 * @note
 */
bool TableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (row >= rowCount(QModelIndex())) { // 大于等于行数
        return false;
    }

    // important
    beginResetModel();
    endResetModel();

    return true;
}

