#include "mapeditor.h"
#include "ui_mapeditor.h"

mapEditor::mapEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mapEditor)
{

    ui->setupUi(this);
    scene = new QGraphicsScene();
    pixelMap = 32;
    defaultHeight = 25;
    defaultwidth = 300;


    ui->mapEditorGraphicsView->setGeometry(0,0,this->width(),this->height());
    ui->mapEditorGraphicsView->setScene(scene);
    ui->widget->setGeometry((this->width()/2)-(ui->widget->width()/2),0,ui->widget->width(),ui->widget->height());


    //LoadMaterials();
    //drawLines();
}

mapEditor::~mapEditor()
{
    delete ui;
}

void mapEditor::resizeEvent(QResizeEvent *event)
{
    ui->mapEditorGraphicsView->setGeometry(0,0,this->width(),this->height());
    ui->widget->setGeometry((this->width()/2)-(ui->widget->width()/2),0,ui->widget->width(),ui->widget->height());
    //drawLines();

}

void mapEditor::mouseMoveEvent( QMouseEvent* event )
{

}

void mapEditor::mousePressEvent( QMouseEvent* event )
{
    qDebug() << "mouse" << checkedBlock << event->pos().x() << event->pos().y() << event->pos().x()/32 << event->pos().y()/32;
    int x = event->pos().x()/32, y = event->pos().y()/32;
    QGraphicsProxyWidget *proxyWidgetItem;
    QLabel *label;
    QMovie *lavaMovie = new QMovie(":/files/images/textures/lava.gif");
    QMovie *endMovie = new QMovie(":/files/images/textures/end.gif");

    QPixmap cloud(":/files/images/textures/cloud.png");
    QPixmap grass(":/files/images/textures/grass.png");
    QPixmap dirt(":/files/images/textures/dirt.png");
    QPixmap brick(":/files/images/textures/brick.png");
    QPixmap spawn(":/files/images/textures/spawn.jpg");

    switch (checkedBlock)
    {
    case 1:
        itemgrille = scene->addPixmap(grass);
        itemgrille->setPos(x * pixelMap, y * pixelMap);

        break;
    case 2:
        itemgrille = scene->addPixmap(dirt);
        itemgrille->setPos(x * pixelMap, y * pixelMap);

        break;
    case 3:
        itemgrille = scene->addPixmap(brick);
        itemgrille->setPos(x * pixelMap, y * pixelMap);

        break;
    case 4:
        itemgrille = scene->addPixmap(spawn);
        itemgrille->setPos(x * pixelMap, y * pixelMap);

        break;
    case 6:
        qDebug() << "lava";

        label = new QLabel();
        label->setMovie(lavaMovie);

        lavaMovie->start();

        proxyWidgetItem = scene->addWidget(label);
        proxyWidgetItem->setPos(x * pixelMap, y * pixelMap);

        break;
    case 7:
        qDebug() << "end";

        label = new QLabel();
        label->setMovie(endMovie);

        endMovie->start();

        proxyWidgetItem = scene->addWidget(label);
        proxyWidgetItem->setPos(x * pixelMap, (y * pixelMap) - 64);

        break;
    case 8:
        itemgrille = scene->addPixmap(cloud);
        itemgrille->setPos(x * pixelMap, y * pixelMap);

        break;
    default:
            qDebug() << "defaul";
        break;
    }

}

void mapEditor::on_spawnButton_toggled(bool checked)
{
    drawLines();
    ui->lavaButton->setChecked(false);
    ui->brickButton->setChecked(false);
    ui->cloudButton->setChecked(false);
    ui->dirtButton->setChecked(false);
    ui->endLevelButton->setChecked(false);
    ui->grassButton->setChecked(false);
    ui->spawnButton->setChecked(checked);
    checkedBlock = 4;

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
    checkedBlock = 6;
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
    checkedBlock = 1;
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
    checkedBlock = 7;
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
    checkedBlock = 2;
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
    checkedBlock = 8;
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
    checkedBlock = 3;
}

void mapEditor::drawLines()
{
    qDebug() << "test1";

    //scene->clear();

    QPixmap backgoundGrilleR(":/files/images/textures/backgroundEditor.png");

    for (int x=0; x<defaultwidth;x++)
    {
        for (int y=0;y<defaultHeight;y++)
        {
            itemgrille = scene->addPixmap(backgoundGrilleR);
            itemgrille->setPos(x*pixelMap,y*pixelMap);
        }

    }
    //on trace les pixmap

    //on remet le list des element !

}
