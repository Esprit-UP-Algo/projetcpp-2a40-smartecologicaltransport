#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_editer_clicked();

    void on_return_2_clicked();

     void on_pushButton_16_clicked();

    void on_done_clicked();

    void on_pushButton_17_clicked();

    void on_modifier_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_20_clicked();

    void on_refrechini_clicked();

    void on_filtrini_clicked();

    void on_pdf_clicked();

    void on_return_3_clicked();

    void on_return_4_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
