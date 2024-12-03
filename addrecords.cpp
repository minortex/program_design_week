#include "addrecords.h"
#include "ui_addrecords.h"

AddRecordsDialog::AddRecordsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRecordsDialog)
{
    ui->setupUi(this);  // 设置 UI 界面

}

AddRecordsDialog::~AddRecordsDialog()
{
    delete ui;  // 释放 UI 对象
}

// 示例槽函数实现
void AddRecordsDialog::on_okButton_clicked()
{
    // 处理确认按钮点击事件
    accept();  // 关闭对话框并返回 QDialog::Accepted
}

void AddRecordsDialog::on_cancelButton_clicked()
{
    // 处理取消按钮点击事件
    reject();  // 关闭对话框并返回 QDialog::Rejected
}