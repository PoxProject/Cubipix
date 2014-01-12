#include "cubipixabout.h"
#include "ui_cubipixabout.h"

CubipixAbout::CubipixAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CubipixAbout)
{
    ui->setupUi(this);

    setWindowTitle(QString("Cubipix - A propos"));
}

CubipixAbout::~CubipixAbout()
{
    delete ui;
}
