#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datarecord.h"
#include "addrecords.h"
#include "editrecords.h"
#include <QDebug>
#include <QAction>
#include <QDialog>
#include <qabstractitemmodel.h>
#include <qpushbutton.h>
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

    // 初始化按钮状态
    ui->deleteButton->setEnabled(false);
    ui->modifyButton->setEnabled(false);
    ui->listView->setModel(listModel);
    // 创建记录
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::onActionNewTriged);
    connect(ui->newButton, &QPushButton::clicked, this, &MainWindow::onActionNewTriged);
    connect(ui->actionStatics, &QAction::triggered, this, &MainWindow::onActionStaticsTriged);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::onActionFileSaveTriged);
    connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::onActionFileLoadTriged);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::onSearchButtonClicked);
    connect(ui->modifyButton, &QPushButton::clicked, this, &MainWindow::onModifyButtonPushed);
    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteButtonPushed);
    
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
    ui->deleteButton->setEnabled(true);
    ui->modifyButton->setEnabled(true);
    QString searchText = ui->searchLineEdit->text(); // 获取搜索框输入
    QStringList filteredList;

    filteredRecords.clear(); // 清空之前的匹配记录

    for (dataRecord &record : m_records) {
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
            filteredRecords.append(&record); // 存储指向原始记录的指针
        }
    }

    // 如果没有找到结果
    if (filteredList.isEmpty()) {
        QMessageBox::information(this, "搜索结果", "没有找到匹配的记录！");
        return;
    }

    // 更新模型并显示在列表中
    listModel->setStringList(filteredList);
    ui->listView->setModel(listModel); // 显示结果列表
}



void MainWindow::onModifyButtonPushed()
{
    // 检查是否有且只有一条匹配记录,这个是cli的要求，我们这里可以选中就暂时注释掉了。
    // if (filteredRecords.size() != 1)
    // {
    //     QMessageBox::information(this, "修改失败", "匹配的记录不是唯一的，无法修改！");
    //     return;
    // }
    QModelIndex selectedIndex = ui->listView->selectionModel()->currentIndex(); // 获取用户选中的项

    if (!selectedIndex.isValid()) {
        QMessageBox::warning(this, "修改记录", "请先选择要修改的记录！");
        return;
    }
        // 找到选中的记录在 filteredRecords 中的索引
    int selectedRow = selectedIndex.row();
    dataRecord* recordtoModify = filteredRecords[selectedRow]; // 获取指针指向的原始记录

    // 从 m_records 中找到该记录并传入
    auto it = std::find_if(m_records.begin(), m_records.end(),
                        [&](const dataRecord& record) {
                               return &record == recordtoModify; // 找到与指针相同的原始记录
                        });
    // 将找到的记录地址传递给对话框
    editRecords dialog(&(*it), this); // 将记录的指针和主窗口作为参数
    int result = dialog.exec();
    if(result == QDialog::Accepted) {
        qDebug() << "Dialog accepted!";
        updateListView();
    } else {
        qDebug() << "Dialog rejected!";
    }
}

void MainWindow::onDeleteButtonPushed()
{
    QModelIndex selectedIndex = ui->listView->selectionModel()->currentIndex(); // 获取用户选中的项

    if (!selectedIndex.isValid()) {
        QMessageBox::warning(this, "删除记录", "请先选择要删除的记录！");
        return;
    }

    // 检查是否有且只有一条匹配记录,这个是cli的要求，我们这里可以选中就暂时注释掉了。
    // if (filteredRecords.size() != 1)
    // {
    //     QMessageBox::information(this, "删除失败", "匹配的记录不是唯一的，无法删除！");
    //     return;
    // }

    // 找到选中的记录在 filteredRecords 中的索引
    int selectedRow = selectedIndex.row();
    dataRecord* recordToDelete = filteredRecords[selectedRow]; // 获取指针指向的原始记录

    // 从 m_records 中找到该记录并删除
    auto it = std::find_if(m_records.begin(), m_records.end(),
                            [&](const dataRecord& record) {
                               return &record == recordToDelete; // 找到与指针相同的原始记录
                            });

    if (it != m_records.end()) {
        m_records.erase(it); // 删除该记录
    }

    // 从 filteredRecords 和 filteredList 中同步删除
    filteredRecords.removeAt(selectedRow);
    listModel->removeRow(selectedRow);

    // 提示删除成功
    QMessageBox::information(this, "删除记录", "记录已成功删除！");
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