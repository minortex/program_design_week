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
    qDebug() << "botton clicked";
    dataRecord record(
        region::Guangdong,
        2024,
        indicatorType::mobilePhoneUsers,
        "万户",
        149.34
    );
        qDebug() << "新记录创建:";
        qDebug() << "地区:" << static_cast<int>(record.getRegion());
        qDebug() << "年份:" << record.getYear();
        qDebug() << "指标类型:" << static_cast<int>(record.getIndicatorType());
        qDebug() << "单位:" << record.getUnit();
        qDebug() << "数值:" << record.getValue();
}

void MainWindow::onActionFindTriged()
{

    qDebug() << "botton clicked";
}

void MainWindow::onActionChangeTriged()
{

    qDebug() << "botton clicked";
}

void MainWindow::onActionStaticsTriged()
{

    qDebug() << "botton clicked";
}

void MainWindow::onActionFileSaveTriged()
{
    // TODO: 保存数据到文件。
}

void MainWindow::onActionFileLoadTriged()
{
    // TODO: 从文件中读取到数据结构变量。
}