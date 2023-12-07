#ifndef EDITABLESQLQUERYMODEL_H
#define EDITABLESQLQUERYMODEL_H
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QModelIndex>
#include <QList>
#include <QTextStream>
#include <QGeoServiceProvider>
#include <QGeoCodingManager>
#include <QGeoCodeReply>
#include <QGeoCoordinate>
class EditableSqlQueryModel : public QSqlQueryModel
{

public:
    EditableSqlQueryModel(QObject *parent = nullptr) : QSqlQueryModel(parent) {}
 QGeoCoordinate location() const;
    void setEditModeEnabled(bool enabled)
    {
        isEditModeEnabled = enabled;
    }

    void setEditableColumns(const QList<int> &editableColumns)
    {
        editableColumnsList = editableColumns;
    }
    void setEditableRows(int editableRow)
    {
        editableRows = editableRow;
    }
    Qt::ItemFlags flags(const QModelIndex &index) const override
    {
        Qt::ItemFlags flags = QSqlQueryModel::flags(index);

        if (isEditModeEnabled) {
            // Check if the column is in the list of editable columns
            if (editableColumnsList.contains(index.column())&&editableRows==index.row()) {
                flags |= Qt::ItemIsEditable;
            }

        }
        return flags;
    }

private:

    bool isEditModeEnabled = false;
    QList<int> editableColumnsList;
    int editableRows=-1;
};


#endif // EDITABLESQLQUERYMODEL_H
