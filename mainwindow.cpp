#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "datarecord.h"
#include "addrecords.h"
#include <QDebug>
#include <QAction>
#include <QDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // KDE6的全局菜单栏好像无法显示，这里先使用非原生菜单栏
    ui->menubar->setVisible(true);
    menuBar()->setNativeMenuBar(false);
    qDebug() << "MenuBar visible:" << ui->menubar->isVisible();

    // 创建记录
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::onActionNewTriged);
    connect(ui->actionFind, &QAction::triggered, this, &MainWindow::onActionFindTriged);
    connect(ui->actionChange, &QAction::triggered, this, &MainWindow::onActionChangeTriged);
    connect(ui->actionStatics, &QAction::triggered, this, &MainWindow::onActionStaticsTriged);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::onActionFileSaveTriged);
    connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::onActionFileLoadTriged);
    
}
QVector<dataRecord>& MainWindow::getRecords()
{
    return m_records; // 返回引用，供外部修改
}

void MainWindow::addRecord(const dataRecord &record)
{
    m_records.append(record); // 添加记录
}

MainWindow::~MainWindow()
{
    delete ui;
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