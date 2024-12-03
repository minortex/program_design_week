#ifndef ADDRECORDS_H
#define ADDRECORDS_H

#include "mainwindow.h"
#include "ui_addrecords.h"
#include <QDialog>

class MainWindow;

namespace Ui {
class AddRecordsDialog;
}

class AddRecordsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddRecordsDialog(QWidget *parent = nullptr);  // 构造函数
    ~AddRecordsDialog();                                     // 析构函数

private slots:
    void processInput();    // 例如，确认按钮的点击事件
    void on_cancelButton_clicked(); // 例如，取消按钮的点击事件

private:
    Ui::AddRecordsDialog *ui;  // UI 对象指针
    MainWindow *m_mainWindow;
};

#endif // ADDRECORDS_H