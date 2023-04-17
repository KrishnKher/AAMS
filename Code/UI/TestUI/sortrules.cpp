#include "sortrules.h"
#include "ui_sortrules.h"
#include <QtWidgets>

SortRules::SortRules(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SortRules)
{
    ui->setupUi(this);

    QObject::connect(ui->addRule, SIGNAL(clicked()), this, SLOT(addRule()));
}

SortRules::~SortRules()
{
    delete ui;
}

void SortRules::addRule() {
    //QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(ui->ruleFrame->layout());
    static int cnt = 0;
    QHBoxLayout *newLayout = new QHBoxLayout(this);

    QStringList commands1 = { "Apple", "Banana", "Grapes", "Jackfruit" };
    QStringList commands2 = { "Ascending", "Descending"};
    QComboBox* combo1 = new QComboBox(this);
    QComboBox* combo2 = new QComboBox(this);
    combo1->addItems(commands1);
    combo2->addItems(commands2);

    newLayout->addWidget(combo1);
    newLayout->addWidget(combo2);
    newLayout->setAlignment(Qt::AlignTop);

    ui->verticalLayout->insertLayout(0, newLayout);
    ui->rules->setLayout(ui->verticalLayout);
    ++cnt;
}

void SortRules::deleteRule() {

}
