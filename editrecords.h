#ifndef EDITRECORDS_H
#define EDITRECORDS_H

#include <QDialog>
#include "datarecord.h"

namespace Ui {
class Dialog;
}

class editRecords : public QDialog
{
    Q_OBJECT

public:
    // 构造函数，接收要编辑的原始记录
    explicit editRecords(dataRecord *record, QWidget *parent = nullptr);
    ~editRecords();

signals:
    // 修改后的记录信号
    void recordModified(const dataRecord &modifiedRecord);

private slots:
    // 确认按钮被点击时
    void on_acceptButton_clicked();
    void on_cancelButton_clicked();

    // 取消按钮被点击时
    // void on_buttonBox_rejected();

private:
    Ui::Dialog *ui;  // UI 指针，负责界面的控制
    dataRecord *record;  // 原始数据记录
};

#endif // EDITRECORDS_H
