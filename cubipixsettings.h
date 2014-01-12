#ifndef CUBIPIXSETTINGS_H
#define CUBIPIXSETTINGS_H

#include <QWidget>

namespace Ui {
class CubipixSettings;
}

class CubipixSettings : public QWidget
{
    Q_OBJECT

public:
    explicit CubipixSettings(QWidget *parent = 0);
    ~CubipixSettings();

private slots:
    void on_saveSettingsButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::CubipixSettings *ui;
};

#endif // CUBIPIXSETTINGS_H
