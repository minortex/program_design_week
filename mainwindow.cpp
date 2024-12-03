#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datarecord.h"
#include "addrecords.h"
#include <QDebug>
#include <QAction>
#include <QDialog>
#include <qabstractitemmodel.h>
#include <qstringlistmodel.h>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , listModel(new QStringListModel(this))
{
    ui->setupUi(this);
    // KDE6的全局菜单栏好像无法显示，这里先使用非原生菜单栏
    ui->menubar->setVisible(true);
    menuBar()->setNativeMenuBar(false);
    qDebug() << "MenuBar visible:" << ui->menubar->isVisible();

    ui->listView->setModel(listModel);

    // 创建记录
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::onActionNewTriged);
    connect(ui->actionFind, &QAction::triggered, this, &MainWindow::onActionFindTriged);
    connect(ui->actionChange, &QAction::triggered, this, &MainWindow::onActionChangeTriged);
    connect(ui->actionStatics, &QAction::triggered, this, &MainWindow::onActionStaticsTriged);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::onActionFileSaveTriged);
    connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::onActionFileLoadTriged);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::onSearchButtonClicked);
    connect(ui->modifyButton, &QPushButton::clicked, this, &MainWindow::onModifyButtonPushed);
    
}
QVector<dataRecord>& MainWindow::getRecords()
{
    return m_records; // 返回引用，供外部修改
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateListView()
{
    QStringList stringList;
    for (const dataRecord &record : m_records) {
        QString item = QString("地区: %1, 年份: %2, 固定电话用户: %3%4, 移动电话用户: %5%6, 互联网用户: %7%8, 固定资产投资: %9%10, 通信收入: %11%12, 信息服务收入: %13%14, 信息产品收入: %15%16")
                        .arg(record.getRegion())
                        .arg(record.getYear())
                        .arg(record.getFixedPhoneUsers().getValue())
                        .arg(record.getFixedPhoneUsers().getUnit())
                        .arg(record.getMobilePhoneUsers().getValue())
                        .arg(record.getMobilePhoneUsers().getUnit())
                        .arg(record.getInternetUsers().getValue())
                        .arg(record.getInternetUsers().getUnit())
                        .arg(record.getFixedAssetsInvestment().getValue())
                        .arg(record.getFixedAssetsInvestment().getUnit())
                        .arg(record.getCommunicationIncome().getValue())
                        .arg(record.getCommunicationIncome().getUnit())
                        .arg(record.getInfoServiceIncome().getValue())
                        .arg(record.getInfoServiceIncome().getUnit())
                        .arg(record.getInfoProductIncome().getValue())
                        .arg(record.getInfoProductIncome().getUnit());
        stringList.append(item);
    }
    listModel->setStringList(stringList); // 更新模型
}


// 添加记录到容器
void MainWindow::addRecord(const dataRecord &record)
{
    m_records.append(record); // 添加记录
    updateListView();
}

void MainWindow::onActionNewTriged()
{
AddRecordsDialog dialog(this); // 将主窗口作为父窗口
    int result = dialog.exec();    // 显示模态窗口，并等待用户操作
    if (result == QDialog::Accepted) {
        qDebug() << "Dialog accepted!";
        // 可在此处理用户点击确认后的逻辑
    } else {
        qDebug() << "Dialog rejected!";
        // 可在此处理用户点击取消后的逻辑
    }

}

void MainWindow::onSearchButtonClicked()
{
    QString searchText = ui->searchLineEdit->text(); // 获取搜索框输入
    QStringList filteredList;

    filteredRecords.clear(); // 清空之前的匹配记录

    for (const dataRecord &record : m_records) {
        // 将记录转为字符串，便于匹配
        QString recordString = QString("地区: %1, 年份: %2, 固定电话用户: %3%4, 移动电话用户: %5%6, 互联网用户: %7%8, 固定资产投资: %9%10, 通信收入: %11%12, 信息服务收入: %13%14, 信息产品收入: %15%16")
                                .arg(record.getRegion())
                                .arg(record.getYear())
                                .arg(record.getFixedPhoneUsers().getValue()).arg(record.getFixedPhoneUsers().getUnit())
                                .arg(record.getMobilePhoneUsers().getValue()).arg(record.getMobilePhoneUsers().getUnit())
                                .arg(record.getInternetUsers().getValue()).arg(record.getInternetUsers().getUnit())
                                .arg(record.getFixedAssetsInvestment().getValue()).arg(record.getFixedAssetsInvestment().getUnit())
                                .arg(record.getCommunicationIncome().getValue()).arg(record.getCommunicationIncome().getUnit())
                                .arg(record.getInfoServiceIncome().getValue()).arg(record.getInfoServiceIncome().getUnit())
                                .arg(record.getInfoProductIncome().getValue()).arg(record.getInfoProductIncome().getUnit());

        // 检查是否包含搜索文本（忽略大小写）
        if (recordString.contains(searchText, Qt::CaseInsensitive)) {
            filteredList.append(recordString);
            filteredRecords.append(record);
        }
    }

    // 更新模型
    listModel->setStringList(filteredList);

}


void MainWindow::onModifyButtonPushed()
{
    // 检查是否有且只有一条匹配记录
    if (filteredRecords.size() == 1) {
        // 执行修改操作
        dataRecord recordToModify = filteredRecords.first();
        
        // 在这里添加你修改记录的代码
        // 例如，弹出一个修改界面或直接修改记录

        // 举个例子:
        qDebug() << "修改记录：" << recordToModify.getRegion();
    } else {
        // 如果匹配的记录数不为1，则弹出提示
        QMessageBox::information(this, "修改失败", "匹配的记录不是唯一的，无法修改！");
    }
}


void MainWindow::onActionFindTriged()
{

    qDebug() << "button clicked";
}

void MainWindow::onActionChangeTriged()
{

    qDebug() << "button clicked";
}

void MainWindow::onActionStaticsTriged()
{

    qDebug() << "button clicked";
}

void MainWindow::onActionFileSaveTriged()
{
    // TODO: 保存数据到文件。
}

void MainWindow::onActionFileLoadTriged()
{
    // TODO: 从文件中读取到数据结构变量。
}