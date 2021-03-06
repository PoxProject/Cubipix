#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QLabel>
#include <QMovie>
#include <QDebug>
#include <QMouseEvent>
#include <QGraphicsProxyWidget>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QTimer>

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

    void drawLines();

    void on_spawnButton_clicked();

    void on_lavaButton_clicked();

    void on_grassButton_clicked();

    void on_endLevelButton_clicked();

    void on_dirtButton_clicked();

    void on_cloudButton_clicked();

    void on_brickButton_clicked();

    void on_saveButton_clicked();

    void on_cancelButton_clicked();

    void on_ValidButton_clicked();

    void on_loadMapButton_clicked();

    void on_cancelLoadMapButton_clicked();

    void on_openMapFile_clicked();

    void on_newMapButton_clicked();

private:
    Ui::mapEditor *ui;
    QGraphicsScene *scene;
    int pixelMap;
    int defaultHeight, defaultwidth;
    void resizeEvent(QResizeEvent *event);
    void mouseMoveEvent( QMouseEvent* event );
    void mousePressEvent(QMouseEvent* event);

    QList<QList<int> > mapState;

    QGraphicsItem *itemgrille;

    int checkedBlock = 0;

};

#endif // MAPEDITOR_H
