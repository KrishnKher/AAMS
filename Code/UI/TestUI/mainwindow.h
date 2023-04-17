
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QWidget>
#include <QObject>
#include <QListWidget>
#include "projectview.h"
#include "sortrules.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void login();
    void logout();
    void fileUpload();
    void createProject();
    void nextPage();
    void addPage();
    void goTo(QListWidgetItem *item);

private:
    QLabel *label;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
