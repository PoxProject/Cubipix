#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QLabel>
#include <QMovie>

namespace Ui {
class mapEditor;
}

class mapEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit mapEditor(QWidget *parent = 0);
    ~mapEditor();

private slots:

    void on_spawnButton_toggled(bool checked);

    void on_lavaButton_toggled(bool checked);

    void on_grassButton_toggled(bool checked);

    void on_endLevelButton_toggled(bool checked);

    void on_dirtButton_toggled(bool checked);

    void on_cloudButton_toggled(bool checked);

    void on_brickButton_toggled(bool checked);

private:
    Ui::mapEditor *ui;
    QGraphicsScene *scene;
    int pixelMap;
    int defaultHeight;
    void LoadMaterials();
    void resizeEvent(QResizeEvent *event);
};

#endif // MAPEDITOR_H
