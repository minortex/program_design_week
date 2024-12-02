#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qvector.h>
#include "datarecord.h"
#include <qstringlistmodel.h>

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
    void updateListView();

private slots: 
    void onActionNewTriged();
    void onActionStaticsTriged();
    void onActionFileSaveTriged();
    void onActionFileLoadTriged();
    void onSearchButtonClicked();
    void onModifyButtonPushed();
    void onDeleteButtonPushed();

private:
    QVector<dataRecord> m_records;
    QStringListModel *listModel;
    QVector<dataRecord*> filteredRecords;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
