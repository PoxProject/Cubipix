#include "cubipixsettings.h"
#include "ui_cubipixsettings.h"

CubipixSettings::CubipixSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CubipixSettings)
{
    ui->setupUi(this);

    setWindowTitle(QString("Cubipix - Options"));
}

CubipixSettings::~CubipixSettings()
{
    delete ui;
}

void CubipixSettings::on_saveSettingsButton_clicked()
{
    this->close();
}

void CubipixSettings::on_cancelButton_clicked()
{
    this->close();
}
