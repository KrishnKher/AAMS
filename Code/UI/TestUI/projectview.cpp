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
