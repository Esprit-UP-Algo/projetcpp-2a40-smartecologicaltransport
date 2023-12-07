#ifndef MYCUSTOMDELEGATE_H
#define MYCUSTOMDELEGATE_H
#include <QStyledItemDelegate>
#include <QComboBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QTableView>
#include <QApplication>
#include <QTextStream>
#include <QTime>
#include <QList>
#include "stations.h"
class MyCustomDelegate : public QStyledItemDelegate
{
 Q_OBJECT
public:
    MyCustomDelegate(QObject* parent=nullptr):QStyledItemDelegate(parent){}
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override
    {
        // Create and return a custom editor widget based on the column or data type
        if (index.column() == 1)
        {
            QComboBox* comboBox1 = new QComboBox(parent);

            comboBox1->setStyleSheet("background-color:white;border-radius:10px;");
            comboBox1->addItem("Ouverte");
            comboBox1->addItem("Occupe");
            comboBox1->addItem("Hors service");
            comboBox1->addItem("En construction");
            return comboBox1;
        }
        else
        {
            if (index.column() == 2)
            {
                QSpinBox* spinBox = new QSpinBox(parent);
                // Customize the spin box
                spinBox->setRange(1, 10);
                return spinBox;
            }
            else
            {
                if (index.column()==3)
                {
                    QComboBox* comboBox2 = new QComboBox(parent);
                    comboBox2->setStyleSheet("background-color:white;border-radius:10px;");
                    comboBox2->addItem("Type 1 (SAE J1772)");
                    comboBox2->addItem("Type 2 (IEC 62196-2) ");
                    comboBox2->addItem("Combo CSS");
                    comboBox2->addItem("CHAdeMO");
                    comboBox2->addItem("Tesla Supercharger");
                    return comboBox2;
                }
                else
                {
                    if(index.column()==0||index.column()==4)
                    {
                    // Use the default editor for other columns
                    QLineEdit* lineEdit=new QLineEdit(parent);
                    return lineEdit;
                    }
/*
                    else
                    {

                        if (index.column() == 5)
                        {
                            // Create an "Edit" button

                            QPushButton* editButton = new QPushButton(parent);
                            editButton->setIcon(QIcon(":/new/prefix1/slim/slim/edit1.png")); // Set the icon for the button if needed
                            connect(editButton, &QPushButton::clicked, [this, index]() {
                                            if (view && otherColumn >= 0) {
                                                QModelIndex otherIndex = index.sibling(index.row(), otherColumn);
                                                view->setCurrentIndex(otherIndex);
                                                view->edit(otherIndex);
                                            }
                                        });

                            return editButton;
                        }
                        else
                        {
                            // Create a "Delete" button
                            QPushButton* deleteButton = new QPushButton("Delete", parent);
                            return deleteButton;
                        }
                    }
                    */
                }
            }
        }
    }

    void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const override
    {
        editor->setGeometry(option.rect);
    }
    void setEditorData(QWidget* editor, const QModelIndex& index) const override
    {
        // Set the data in the custom editor based on the column or data type
        if (index.column() == 1) {
            QComboBox* comboBox1 = qobject_cast<QComboBox*>(editor);
            if (comboBox1) {
                // Set the current index in the combo box
                QVariant data=index.data(Qt::EditRole);
                QString statut=data.toString();
                comboBox1->setCurrentText(statut);
            }
        }
        else
        {
            if(index.column()==3)
            {
                QComboBox* comboBox2 = qobject_cast<QComboBox*>(editor);
                if (comboBox2) {
                    // Set the current index in the combo box
                    QVariant data=index.data(Qt::EditRole);
                    QString type_connect=data.toString();
                    comboBox2->setCurrentText(type_connect);
                }
            }
            else
            {
                if (index.column() == 2)
                {
                    QSpinBox* spinBox = qobject_cast<QSpinBox*>(editor);
                    if (spinBox) {
                        // Set the value in the spin box
                        QVariant data=index.data(Qt::EditRole);
                        int value=data.toInt();
                        spinBox->setValue(value);
                    }
                }
                 else
                    {
                        if(index.column()==0||index.column()==4){
                    QLineEdit* lineEdit = qobject_cast<QLineEdit*>(editor);
                            // Check if the editor is a QLineEdit

                            // Retrieve the value from the model's data for the given index
                            QVariant data = index.data(Qt::EditRole); // Use Qt::EditRole to obtain editable data

                            // Assuming the data represents the text for the line edit
                            QString text = data.toString();

                            // Set the text in the line edit
                            lineEdit->setText(text);
                        }
                        else
                        {
                            QPushButton* button = qobject_cast<QPushButton*>(editor);
                            if (button)
                            {
                                // Customize the QPushButton behavior
                                connect(button, &QPushButton::clicked, [index]() {});
                            }
                         }
                      }
            }
        }
    }

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {

        if(index.column()==5)
        {
            QStyleOptionButton buttonOption;
            buttonOption.rect = option.rect;
            QIcon icon(":/new/prefix1/slim/slim/edit0.png");
            buttonOption.icon = icon;
            buttonOption.iconSize=QSize(25,25);
            QApplication::style()->drawControl(QStyle::CE_PushButton, &buttonOption, painter);
        }
        else
        {
            if(index.column()==6)
            {
                QStyleOptionButton buttonOption;
                buttonOption.rect = option.rect;
                QIcon icon(":/new/prefix1/slim/slim/supp0.png");
                buttonOption.icon = icon;
                buttonOption.iconSize=QSize(25,25);
                QApplication::style()->drawControl(QStyle::CE_PushButton, &buttonOption, painter);
            }
            else
                QStyledItemDelegate::paint(painter, option, index);
        }
    }
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override {

        if (option.rect.contains(QCursor::pos()) && QApplication::mouseButtons() == Qt::LeftButton)
        {

        }
        else
        {
            if(index.column()==5)
           {
                static QTime lastClickTime;
                int clickInterval = 1000; // Adjust the interval as needed (in milliseconds)
                if (lastClickTime.isNull() || lastClickTime.elapsed() >= clickInterval)
                {
                    // Handle the left-click action here
                    emit buttonClicked(index);
                    editrow=index.row();
                    QModelIndex dataIndex = model->index(index.row(), 0);
                    QVariant value = index.model()->data(dataIndex);
                    ref=value.toString();

                    // Update the last click time
                    lastClickTime.start();
                }
            }
            else if(index.column()==6)
            {
                static QTime lastClickTime;
                int clickInterval = 1000; // Adjust the interval as needed (in milliseconds)
                if (lastClickTime.isNull() || lastClickTime.elapsed() >= clickInterval)
                {
                    // Handle the left-click action here
                    emit buttonsuppClicked(index);
                    supprow=index.row();
                    QModelIndex dataIndex = model->index(index.row(), 0);
                    QVariant value = index.model()->data(dataIndex);
                    ref=value.toString();
                    // Update the last click time
                    lastClickTime.start();
                }
            }
        }
        return QStyledItemDelegate::editorEvent(event, model, option, index);
    }

    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override
    {
        QVariant nv;

        // Set the model data based on the column or data type
        if (index.column() == 1)
        {
            editcolonne=1;
            QComboBox* comboBox1 = qobject_cast<QComboBox*>(editor);
            if (comboBox1) {
                 nv = comboBox1->currentText();

            // Set the model data at the specified index with the new value
            model->setData(index, nv, Qt::EditRole);
            QTextStream outputStream(stdout);
        //    outputStream << selectedText;
            }
        }
        else
        {
            if(index.column()==3)
            {editcolonne=3;
                QComboBox* comboBox2 = qobject_cast<QComboBox*>(editor);
                if (comboBox2) {
                     nv = comboBox2->currentText();

                // Set the model data at the specified index with the new value
                model->setData(index, nv, Qt::EditRole);


                }

            }
            else{

                if (index.column() == 2)
                {
                    editcolonne=2;
                    QSpinBox* spinBox = qobject_cast<QSpinBox*>(editor);
                    if (spinBox)
                    {
                       // Retrieve the value from the spin box
                         nv = spinBox->value();

                        // Set the model data with the value
                        model->setData(index, nv, Qt::EditRole);
                    }
                }
                else
                {
                    if(index.column()==0){
                        editcolonne=0;
                    QLineEdit* lineEdit = qobject_cast<QLineEdit*>(editor);
                    // Check if the editor is a QLineEdit
                    if(lineEdit)
                    {
                        // Retrieve the text from the line edit
                        nv = lineEdit->text();
                        QString val;
                        if (!val.isEmpty())
                        {
                            // Set the model data with the text
                            model->setData(index, nv, Qt::EditRole);
                        }
                    }
                    }

                    else if(index.column()==4)
                    {

                        QLineEdit* lineEdit = qobject_cast<QLineEdit*>(editor);
                        // Check if the editor is a QLineEdit
                        if(lineEdit)
                        {
                            // Retrieve the text from the line edit
                            nv = lineEdit->text();

                            // Set the model data with the text
                            model->setData(index, nv, Qt::EditRole);
                        }
                    }
                }
            }
        }
        updatedValue = nv;
        const_cast<MyCustomDelegate*>(this)->emitDataChangedSignal(index, updatedValue);
    }
    void focusOnCell(QAbstractItemView* view, const QModelIndex& index) const
    {
        // Placer la vue en mode édition pour la cellule spécifiée
        view->edit(index);
    }
    void emitDataChangedSignal(const QModelIndex& index, const QVariant& value)
    {
        emit dataChangedSignal(index, value);
    }
    void setButtonColumn(int column) {
        buttonColumn = column;
    }

    void setOtherColumn(int column) {
        otherColumn = column;
    }

    void setView(QTableView* tableView) {
        view = tableView;
    }

    QVariant getUpdatedValue() const {
            return updatedValue;
        }
    int getEditColonne() const{return editcolonne;}
private:
    int buttonColumn = -1;
    int otherColumn = -1;
    QTableView* view = nullptr;
    mutable QVariant updatedValue;
    mutable int editcolonne=-1;
public:
    int editrow=-1;
    int supprow=-1;
    QString ref;

signals:
   void buttonClicked(const QModelIndex &index);
   void buttonsuppClicked(const QModelIndex &index);
    void dataChangedSignal(const QModelIndex& index, const QVariant& value);
};

#endif // MYCUSTOMDELEGATE_H
