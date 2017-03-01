#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QLineEdit>
#include<QLabel>
#include<QTimer>
#include<QPushButton>
#include <QHBoxLayout>
#include <QCalendarWidget>
#include<QGroupBox>
#include<QStackedWidget>
#include<QStackedLayout>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void resizeEvent(QResizeEvent* evt)override;
    void addWidget();

 private slots:
    void showTime();
    void clickedSlot_EXIT();
    void clickedSlot_LOGIN();
};

#endif // MAINWINDOW_H
