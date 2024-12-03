#include "editrecords.h"
#include "ui_editrecords.h"
#include "mainwindow.h"
#include <QDebug>
#include <QMessageBox>

// 构造函数
editRecords::editRecords(dataRecord *record, QWidget *parent)
    : QDialog(parent), ui(new Ui::Dialog), record(record)
{
    ui->setupUi(this);

    // 构建槽
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &editRecords::on_acceptButton_clicked);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &editRecords::on_cancelButton_clicked);
    // 传入值
    ui->regionValue->setText(record->getRegion());
    ui->yearValue->setText(QString::number(record->getYear()));
    ui->fixedPhoneValue->setText(QString::number(record->getFixedPhoneUsers().getValue()));
    ui->mobilePhoneValue->setText(QString::number(record->getMobilePhoneUsers().getValue()));
    ui->internetValue->setText(QString::number(record->getInternetUsers().getValue()));
    ui->fixedAssetsValue->setText(QString::number(record->getFixedAssetsInvestment().getValue()));
    ui->communicationValue->setText(QString::number(record->getCommunicationIncome().getValue()));
    ui->infoServiceValue->setText(QString::number(record->getInfoServiceIncome().getValue()));
    ui->infoProductValue->setText(QString::number(record->getInfoProductIncome().getValue()));

    // 传入单位
    ui->fixedPhoneUnit->setText((record->getFixedPhoneUsers().getUnit()));
    ui->mobilePhoneUnit->setText((record->getMobilePhoneUsers().getUnit()));
    ui->internetUnit->setText((record->getInternetUsers().getUnit()));
    ui->fixedAssetsUnit->setText((record->getFixedAssetsInvestment().getUnit()));
    ui->communicationUnit->setText((record->getCommunicationIncome().getUnit()));
    ui->infoServiceUnit->setText((record->getInfoServiceIncome().getUnit()));
    ui->infoProductUnit->setText((record->getInfoProductIncome().getUnit()));


}


void editRecords::on_acceptButton_clicked() {
    QString region = ui->regionValue->text();
    QString year = ui->yearValue->text();

    if (region.isEmpty() || year.isEmpty()) {
        QMessageBox::warning(this, "警告", "地区和年份是必填项！");
        return;
    }

    bool yearOk;
    int yearInt = year.toInt(&yearOk);
    if (!yearOk) {
        QMessageBox::warning(this, "警告", "年份必须是一个有效的数字！");
        return;
    }

    auto parseValueWithUnit = [](const QString &input, const QString &unit) -> ValueWithUnit {
        bool ok;
        double value = input.toDouble(&ok);
        return ok ? ValueWithUnit(value, unit) : ValueWithUnit(0.0, unit);
    };

    // 更新记录内容
    record->setRegion(region);
    record->setYear(yearInt);
    record->setFixedPhoneUsers(parseValueWithUnit(ui->fixedPhoneValue->text(), ui->fixedPhoneUnit->text()));
    record->setMobilePhoneUsers(parseValueWithUnit(ui->mobilePhoneValue->text(), ui->mobilePhoneUnit->text()));
    record->setInternetUsers(parseValueWithUnit(ui->internetValue->text(), ui->internetUnit->text()));
    record->setFixedAssetsInvestment(parseValueWithUnit(ui->fixedAssetsValue->text(), ui->fixedAssetsUnit->text()));
    record->setCommunicationIncome(parseValueWithUnit(ui->communicationValue->text(), ui->communicationUnit->text()));
    record->setInfoServiceIncome(parseValueWithUnit(ui->infoServiceValue->text(), ui->infoServiceUnit->text()));
    record->setInfoProductIncome(parseValueWithUnit(ui->infoProductValue->text(), ui->infoProductUnit->text()));

    QMessageBox::information(this, "成功", "记录已成功更新！");
    accept(); // 关闭窗口
}



// 析构函数
editRecords::~editRecords()
{
    delete ui;
}
void editRecords::on_cancelButton_clicked()
{
    reject();
}
