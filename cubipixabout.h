#ifndef CUBIPIXABOUT_H
#define CUBIPIXABOUT_H

#include <QDialog>

namespace Ui {
class CubipixAbout;
}

class CubipixAbout : public QDialog
{
    Q_OBJECT

public:
    explicit CubipixAbout(QWidget *parent = 0);
    ~CubipixAbout();

private:
    Ui::CubipixAbout *ui;
};

#endif // CUBIPIXABOUT_H
