#include "addrecords.h"
#include "mainwindow.h"
#include "ui_addrecords.h"
#include <qdialogbuttonbox.h>
#include <QDebug>
#include <QMessageBox>
#include "datarecord.h"

AddRecordsDialog::AddRecordsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRecordsDialog)
{
    ui->setupUi(this);

    // 连接信号与槽
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &AddRecordsDialog::processInput);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &AddRecordsDialog::on_cancelButton_clicked);
}

AddRecordsDialog::~AddRecordsDialog()
{
    delete ui;
}

void AddRecordsDialog::processInput()
{
    // 收集输入框数据
    QString region = ui->regionValue->text();
    QString year = ui->yearValue->text();
    QString fixedPhone = ui->fixedPhoneValue->text();
    QString mobilePhone = ui->mobilePhoneValue->text();
    QString internet = ui->internetValue->text();
    QString fixedAssets = ui->fixedAssetsValue->text();
    QString communication = ui->communicationValue->text();
    QString infoService = ui->infoServiceValue->text();
    QString infoProduct = ui->infoProductValue->text();

    // 收集单位输入框的数据
    QString fixedPhoneUnit = ui->fixedPhoneUnit->text();
    QString mobilePhoneUnit = ui->mobilePhoneUnit->text();
    QString internetUnit = ui->internetUnit->text();
    QString fixedAssetsUnit = ui->fixedAssetsUnit->text();
    QString communicationUnit = ui->communicationUnit->text();
    QString infoServiceUnit = ui->infoServiceUnit->text();
    QString infoProductUnit = ui->infoProductUnit->text();
    // ui->infoProductUnit->setText("test");

    // 检查是否有必填项未填写
    if (region.isEmpty() || year.isEmpty()) {
        QMessageBox::warning(this, "警告", "地区和年份是必填项！");
        return;
    }

    // 转换年份为整数
    bool yearOk;
    int yearInt = year.toInt(&yearOk);
    if (!yearOk) {
        QMessageBox::warning(this, "警告", "年份必须是一个有效的数字！");
        return;
    }

    // 转换其他输入为浮点数并附带单位
    auto parseValueWithUnit = [](const QString& input, const QString& unit) -> ValueWithUnit {
        bool ok;
        double value = input.toDouble(&ok);
        return ok ? ValueWithUnit(value, unit) : ValueWithUnit(0.0, unit);
    };

    ValueWithUnit fixedPhoneUsers = parseValueWithUnit(fixedPhone, fixedPhoneUnit);
    ValueWithUnit mobilePhoneUsers = parseValueWithUnit(mobilePhone, mobilePhoneUnit);
    ValueWithUnit internetUsers = parseValueWithUnit(internet, internetUnit);
    ValueWithUnit fixedAssetsInvestment = parseValueWithUnit(fixedAssets, fixedAssetsUnit);
    ValueWithUnit communicationIncome = parseValueWithUnit(communication, communicationUnit);
    ValueWithUnit infoServiceIncome = parseValueWithUnit(infoService, infoServiceUnit);
    ValueWithUnit infoProductIncome = parseValueWithUnit(infoProduct, infoProductUnit);

    dataRecord record(region, yearInt, fixedPhoneUsers, mobilePhoneUsers, internetUsers, fixedAssetsInvestment, communicationIncome, infoServiceIncome, infoProductIncome);

    if (MainWindow *mainWindow = qobject_cast<MainWindow*>(parent())) {
        mainWindow->addRecord(record);

        // 测试遍历所有数据
        for (const dataRecord &record : mainWindow->getRecords()) {
            qDebug() << "区域: " << record.getRegion()
                    << ", 年份: " << record.getYear()
                    << ", 固定电话用户: " << record.getFixedPhoneUsers().getValue() << " " << record.getFixedPhoneUsers().getUnit()
                    << ", 移动电话用户: " << record.getMobilePhoneUsers().getValue() << " " << record.getMobilePhoneUsers().getUnit()
                    << ", 网络用户: " << record.getInternetUsers().getValue() << " " << record.getInternetUsers().getUnit()
                    << ", 固定资产投资: " << record.getFixedAssetsInvestment().getValue() << " " << record.getFixedAssetsInvestment().getUnit()
                    << ", 通信收入: " << record.getCommunicationIncome().getValue() << " " << record.getCommunicationIncome().getUnit()
                    << ", 信息服务收入: " << record.getInfoServiceIncome().getValue() << " " << record.getInfoServiceIncome().getUnit()
                    << ", 信息产品收入: " << record.getInfoProductIncome().getValue() << " " << record.getInfoProductIncome().getUnit();
        }
    } else {
        QMessageBox::warning(this, "错误", "无法添加记录到主窗口！");
    }

    // 提示用户操作成功
    QMessageBox::information(this, "成功", "记录已成功添加！");
    accept(); // 关闭窗口
}
void AddRecordsDialog::on_cancelButton_clicked()
{
    reject();
}