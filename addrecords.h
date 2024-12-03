#ifndef ADDRECORDS_H
#define ADDRECORDS_H

#include <QDialog>

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
    void on_okButton_clicked();    // 例如，确认按钮的点击事件
    void on_cancelButton_clicked(); // 例如，取消按钮的点击事件

private:
    Ui::AddRecordsDialog *ui;  // UI 对象指针
};

#endif // ADDRECORDS_H