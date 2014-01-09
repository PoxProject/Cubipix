#include "mapeditor.h"
#include "ui_mapeditor.h"

mapEditor::mapEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mapEditor)
{
    ui->setupUi(this);
    pixelMap = 32;
    defaultHeight = 16;
    scene = new QGraphicsScene();
    QPixmap background(":/files/images/textures/background.png");
    scene->setBackgroundBrush(background);
    ui->mapEditorGraphicsView->setGeometry(0,0,this->width(),this->height());
    ui->mapEditorGraphicsView->setScene(scene);
    ui->widget->setGeometry((this->width()/2)-(ui->widget->width()/2),0,ui->widget->width(),ui->widget->height());

    LoadMaterials();
}

mapEditor::~mapEditor()
{
    delete ui;
}
void mapEditor::LoadMaterials()
{
    QGraphicsItem *item;
    QGraphicsProxyWidget *proxyWidgetItem;
    QLabel *label;

    //Load Textures

    QMovie *lavaMovie = new QMovie(":/files/images/textures/lava.gif");
    QMovie *endMovie = new QMovie(":/files/images/textures/end.gif");

    QPixmap cloud(":/files/images/textures/cloud.png");
    QPixmap grass(":/files/images/textures/grass.png");
    QPixmap dirt(":/files/images/textures/dirt.png");
    QPixmap brick(":/files/images/textures/brick.png");
    QPixmap spawn(":/files/images/textures/spawn.jpg");

    // adding grass to list
   /* item = scene->addPixmap(grass);
    item->setPos(ui->mapEditorGraphicsView->width()-10-pixelMap, 10+pixelMap);
    item = scene->addPixmap(dirt);
    item->setPos(ui->blockSelectGraphicsView->width()-10-pixelMap, 15+2*pixelMap);
    item = scene->addPixmap(cloud);
    item->setPos(ui->blockSelectGraphicsView->width()-10-pixelMap, 15+3*pixelMap);
    item = scene->addPixmap(brick);
    item->setPos(ui->blockSelectGraphicsView->width()-10-pixelMap, 15+4*pixelMap);
    item = scene->addPixmap(spawn);
    item->setPos(ui->blockSelectGraphicsView->width()-10-pixelMap, 15+5*pixelMap);*/


}
void mapEditor::resizeEvent(QResizeEvent *event)
{
    ui->mapEditorGraphicsView->setGeometry(0,0,this->width(),this->height());
    ui->widget->setGeometry((this->width()/2)-(ui->widget->width()/2),0,ui->widget->width(),ui->widget->height());

}

void mapEditor::on_spawnButton_toggled(bool checked)
{
    ui->lavaButton->setChecked(false);
    ui->brickButton->setChecked(false);
    ui->cloudButton->setChecked(false);
    ui->dirtButton->setChecked(false);
    ui->endLevelButton->setChecked(false);
    ui->grassButton->setChecked(false);
    ui->spawnButton->setChecked(checked);
}

void mapEditor::on_lavaButton_toggled(bool checked)
{
    ui->lavaButton->setChecked(checked);
    ui->brickButton->setChecked(false);
    ui->cloudButton->setChecked(false);
    ui->dirtButton->setChecked(false);
    ui->endLevelButton->setChecked(false);
    ui->grassButton->setChecked(false);
    ui->spawnButton->setChecked(false);
}

void mapEditor::on_grassButton_toggled(bool checked)
{
    ui->lavaButton->setChecked(false);
    ui->brickButton->setChecked(false);
    ui->cloudButton->setChecked(false);
    ui->dirtButton->setChecked(false);
    ui->endLevelButton->setChecked(false);
    ui->grassButton->setChecked(checked);
    ui->spawnButton->setChecked(false);
}

void mapEditor::on_endLevelButton_toggled(bool checked)
{
    ui->lavaButton->setChecked(false);
    ui->brickButton->setChecked(false);
    ui->cloudButton->setChecked(false);
    ui->dirtButton->setChecked(false);
    ui->endLevelButton->setChecked(checked);
    ui->grassButton->setChecked(false);
    ui->spawnButton->setChecked(false);
}

void mapEditor::on_dirtButton_toggled(bool checked)
{
    ui->lavaButton->setChecked(false);
    ui->brickButton->setChecked(false);
    ui->cloudButton->setChecked(false);
    ui->dirtButton->setChecked(checked);
    ui->endLevelButton->setChecked(false);
    ui->grassButton->setChecked(false);
    ui->spawnButton->setChecked(false);
}

void mapEditor::on_cloudButton_toggled(bool checked)
{
    ui->lavaButton->setChecked(false);
    ui->brickButton->setChecked(false);
    ui->cloudButton->setChecked(checked);
    ui->dirtButton->setChecked(false);
    ui->endLevelButton->setChecked(false);
    ui->grassButton->setChecked(false);
    ui->spawnButton->setChecked(false);
}

void mapEditor::on_brickButton_toggled(bool checked)
{
    ui->lavaButton->setChecked(false);
    ui->brickButton->setChecked(checked);
    ui->cloudButton->setChecked(false);
    ui->dirtButton->setChecked(false);
    ui->endLevelButton->setChecked(false);
    ui->grassButton->setChecked(false);
    ui->spawnButton->setChecked(false);
}
