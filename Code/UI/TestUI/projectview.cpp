#include "projectview.h"
#include "ui_projectview.h"
#include <QObject>
#include <QFileDialog>

ProjectView::ProjectView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjectView)
{
    ui->setupUi(this);

    QObject::connect(ui->dataUpload, SIGNAL(clicked()), this, SLOT(fileUpload()));
    QObject::connect(ui->matrixUpload, SIGNAL(clicked()), this, SLOT(fileUpload()));
    QObject::connect(ui->sortRules, SIGNAL(clicked()), this, SLOT(rulesInput()));
}

ProjectView::~ProjectView()
{
    delete ui;
}

void ProjectView::fileUpload() {
    QString dataFileName = QFileDialog::getOpenFileName(this, "Open a file", QDir::homePath());
}

void ProjectView::setProjectTitle(std::string title) {
    ui->projectName->setText(QString::fromStdString(title));
}


void ProjectView::rulesInput() {
    SortRules ruleInput;
    ruleInput.setModal(true);
    ruleInput.exec();
}
//void ProjectView::createProject() {
//    static int numProject = 0;
//    ++numProject;
//    QString temp = QString::fromStdString("Project " + std::to_string(numProject));
//    //ui->projectList->addItem(temp);
//}
//void ProjectView::addPage() {

//    static int p = 0;
//    ++p;
//    //    QPushButton *newButton = new QPushButton(QString::fromStdString("Okay Cool " + std::to_string(p)), ui->expStack);
//    //    //QLabel *label = new QLabel(this);
//    //    //label->setText(QString::fromStdString(to_string(p)));
//    //    ui->expStack->addWidget(newButton);
//    //    //ui->expStack->addWidget(label);
//    //    ui->expStack->setCurrentIndex(p);
//    //QObject::connect(newButton, SIGNAL(clicked()), this, SLOT(prevPage()));

//    ProjectView *newProject = new ProjectView();
//    //newProject->ui
//    //ui->expStack->addWidget(newProject);
//    //ui->expStack->setCurrentIndex(p);
//}
