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

    void on_spawnButton_clicked();

    void on_lavaButton_clicked();

    void on_grassButton_clicked();

    void on_endLevelButton_clicked();

    void on_dirtButton_clicked();

    void on_cloudButton_clicked();

    void on_brickButton_clicked();

    void on_pushButton_clicked();

    void on_saveButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::mapEditor *ui;
    QGraphicsScene *scene;
    int pixelMap;
    int defaultHeight, defaultwidth;
    void resizeEvent(QResizeEvent *event);
    void mouseMoveEvent( QMouseEvent* event );
    void mousePressEvent(QMouseEvent* event);
    void drawLines();

    QList<QList<int> > mapState;

    QGraphicsItem *itemgrille;

    int checkedBlock = 0;

};

#endif // MAPEDITOR_H
