
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QObject>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->Login, SIGNAL(clicked()), this, SLOT(login()));
    //QObject::conenct(ui->Login, SIGNAL(clicked()), this, SLOT())
    QObject::connect(ui->Logout, SIGNAL(clicked()), this, SLOT(logout()));
    QObject::connect(ui->addProject, SIGNAL(clicked()), this, SLOT(createProject()));
    QObject::connect(ui->addProject, SIGNAL(clicked()), this, SLOT(addPage()));

    QObject::connect(ui->projectList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(goTo(QListWidgetItem*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::login()
{
    QString username = ui->username->text();
    QString password = ui->password->text();

    if(username != "root" || password != "root") {
        ui->warningSign->setText("Enter correct Username/Password");
    } else {
        ui->navigate->setCurrentIndex(1);
    }
}

void MainWindow::logout() {
    ui->navigate->setCurrentIndex(0);
}

void MainWindow::fileUpload() {
    QString dataFileName = QFileDialog::getOpenFileName(this, "Open a file", QDir::homePath());
}

void MainWindow::createProject() {
    static int numProject = 0;
    ++numProject;
    QString temp = QString::fromStdString("Project " + std::to_string(numProject));
    ui->projectList->addItem(temp);
}

void MainWindow::nextPage() {
    ui->navigate->setCurrentIndex(2);
}

void MainWindow::addPage() {

    static int p = 0;
    ++p;

    ProjectView *newProject = new ProjectView();
    newProject->setProjectTitle("Project " + std::to_string(p));
    //newProject->ui
    ui->expStack->addWidget(newProject);
    qDebug() << ui->expStack->count() << "\n";
    ui->expStack->setCurrentIndex(p);
}

void MainWindow::goTo(QListWidgetItem *item) {
    ui->expStack->setCurrentIndex(ui->projectList->row(item)+1);
    qDebug() << ui->projectList->row(item) << "\n";
}
