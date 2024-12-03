#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qvector.h>
#include "datarecord.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QVector<dataRecord>& getRecords();
    void addRecord(const dataRecord &record);

private slots: 
    void onActionNewTriged();
    void onActionFindTriged();
    void onActionChangeTriged();
    void onActionStaticsTriged();
    void onActionFileSaveTriged();
    void onActionFileLoadTriged();

private:
    QVector<dataRecord> m_records;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
