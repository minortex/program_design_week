#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "datarecord.h"
#include "addrecords.h"
#include <QDebug>
#include <QAction>
#include <QDialog>

#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QMessageBox>
#include <QFileDialog>

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
    // 创建一个文件对话框来选择保存位置
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Records"), "", tr("JSON Files (*.json);;All Files (*)"));

    // 如果用户没有选择文件，直接返回
    if (fileName.isEmpty()) {
        return;
    }

    // 打开文件进行写入
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, tr("Error"), tr("Unable to open file for saving"));
        return;
    }

    // 创建一个 QJsonArray 来存储所有记录
    QJsonArray jsonArray;

    // 将 m_records 中的每一项转换为 JSON 对象并添加到 jsonArray 中
    for (const dataRecord& record : m_records) {
        jsonArray.append(record.toJson());
    }

    // 创建一个 QJsonDocument 来封装 QJsonArray
    QJsonDocument doc(jsonArray);

    // 将 JSON 文档写入文件
    file.write(doc.toJson());

    // 关闭文件
    file.close();
}

void MainWindow::onActionFileLoadTriged()
{
    // TODO: 从文件中读取到数据结构变量。
    // 1. 打开文件对话框，选择文件
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt);;All Files (*.*)"));

    // 如果用户没有选择文件，则返回
    if (fileName.isEmpty()) {
        return;
    }

    // 2. 打开文件
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // 打开文件失败，处理错误
        qDebug() << "Failed to open file:" << fileName;
        return;
    }

    // 3. 读取文件内容
    QTextStream in(&file);
    QStringList dataLines;

    // 逐行读取文件数据，并存入 dataLines 中
    while (!in.atEnd()) {
        QString line = in.readLine();
        dataLines.append(line);  // 这里可以根据需要处理每行数据，或者加载到数据结构中
    }

    // 4. 处理数据（将其加载到你的数据结构中）
    // 假设你有一个 QList<QString> 用来存储这些数据
    QList<QString> loadedData;
    for (const QString &line : dataLines) {
        // 在这里进行数据的解析与存储
        loadedData.append(line);
    }

    // 打印加载的数据（调试用）
    qDebug() << "Loaded data:" << loadedData;

    // 5. 关闭文件
    file.close();
}
