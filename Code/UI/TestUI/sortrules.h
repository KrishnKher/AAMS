#ifndef SORTRULES_H
#define SORTRULES_H

#include <QDialog>

namespace Ui {
class SortRules;
}

class SortRules : public QDialog
{
    Q_OBJECT

public:
    explicit SortRules(QWidget *parent = nullptr);
    ~SortRules();

private:
    Ui::SortRules *ui;

private slots:
    void addRule();
    void deleteRule();
};

#endif // SORTRULES_H
