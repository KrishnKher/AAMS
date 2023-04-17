#ifndef PROJECTVIEW_H
#define PROJECTVIEW_H

#include <QWidget>
#include "sortrules.h"

namespace Ui {
class ProjectView;
}

class ProjectView : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectView(QWidget *parent = nullptr);
    ~ProjectView();

    void setProjectTitle(std::string title);

private:
    Ui::ProjectView *ui;

private slots:
    void fileUpload();
    void rulesInput();
};

#endif // PROJECTVIEW_H
