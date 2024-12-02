#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "datarecord.h"
#include <QDebug>
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // KDE6的全局菜单栏好像无法显示，这里先使用非原生菜单栏
    ui->menubar->setVisible(true);
    menuBar()->setNativeMenuBar(false);
    qDebug() << "MenuBar visible:" << ui->menubar->isVisible();

    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::onActionNewTriged);
    connect(ui->actionFind, &QAction::triggered, this, &MainWindow::onActionNewTriged);
    connect(ui->actionChange, &QAction::triggered, this, &MainWindow::onActionNewTriged);
    connect(ui->actionStatics, &QAction::triggered, this, &MainWindow::onActionNewTriged);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::onActionNewTriged);
    connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::onActionNewTriged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onActionNewTriged()
{
// 先确定一些指标
ValueWithUnit fixedPhone(100.0, "万户");
ValueWithUnit mobilePhone(200.0, "万户");
ValueWithUnit internet(150.0, "万户");
ValueWithUnit fixedAssets(500.0, "万元");
ValueWithUnit communication(1000.0, "万元");
ValueWithUnit infoService(200.0, "万元");
ValueWithUnit infoProduct(300.0, "万元");

// 创建 dataRecord 对象
dataRecord record(
    "广东",       // 地区名称（QString）
    2024,         // 年份
    fixedPhone,    // 固定电话用户数
    mobilePhone,   // 移动电话用户数
    internet,      // 互联网用户数
    fixedAssets,   // 固定资产投入
    communication, // 通信业收入
    infoService,   // 信息服务收入
    infoProduct    // 信息产品收入
);

// 输出验证
qDebug() << "记录创建成功:";
qDebug() << "地区:" << record.getRegion(); 
qDebug() << "年份:" << record.getYear();
qDebug() << "移动电话用户:" << record.getMobilePhoneUsers().getValue() 
        << record.getMobilePhoneUsers().getUnit();
qDebug() << "信息产业收入:" << record.getInfoProductIncome().getValue() 
        << record.getInfoProductIncome().getUnit();

// 添加记录到 QVector 容器
m_records.append(record);

// 验证记录数
qDebug() << "当前记录数量" << m_records.size();

// 遍历记录
for (const auto& rec : m_records) {
    qDebug() << "地区:" << rec.getRegion()   // 输出地区名称（QString）
            << "年份:" << rec.getYear()
            << "移动电话用户:" << rec.getMobilePhoneUsers().getValue() 
            << rec.getMobilePhoneUsers().getUnit();
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