#include "mapeditor.h"
#include "ui_mapeditor.h"

mapEditor::mapEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mapEditor)
{

    ui->setupUi(this);
   // this->setMouseTracking(true);
    pixelMap = 32;
    defaultHeight = 25;
    defaultwidth = 300;
    ui->mapEditorGraphicsView->setGeometry(0,0,this->width(),this->height());
    scene = new QGraphicsScene();
    ui->mapEditorGraphicsView->setScene(scene);
    ui->widget->setGeometry((this->width()/2)-(ui->widget->width()/2),0,ui->widget->width(),ui->widget->height());
    ui->saveWidget->hide();
    QTimer::singleShot(50,this,SLOT(drawLines()));
    ui->loadingWidget->setGeometry(0,0, this->width(),this->height());
    ui->loading->setGeometry((this->width()/2)-(ui->groupSaveWidget->width()/2),(this->height()/2)-(ui->groupSaveWidget->height()/2), ui->groupSaveWidget->width(),ui->groupSaveWidget->height());
    ui->loadingWidget->show();
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
    ui->saveWidget->setGeometry(0,0, this->width(),this->height());
    ui->groupSaveWidget->setGeometry((this->width()/2)-(ui->groupSaveWidget->width()/2),(this->height()/2)-(ui->groupSaveWidget->height()/2), ui->groupSaveWidget->width(),ui->groupSaveWidget->height());
    ui->loadingWidget->setGeometry(0,0, this->width(),this->height());
    ui->loading->setGeometry((this->width()/2)-(ui->groupSaveWidget->width()/2),(this->height()/2)-(ui->groupSaveWidget->height()/2), ui->groupSaveWidget->width(),ui->groupSaveWidget->height());
    //drawLines();

}

void mapEditor::mouseMoveEvent( QMouseEvent *event )
{
    qDebug() << "testTrac";
  //  qDebug() << "mouse" << checkedBlock << event->pos().x() << event->pos().y() << event->pos().x()/32 << event->pos().y()/32;
  //  int x = event->pos().x()/32, y = event->pos().y()/32;

/*    if(mapState.at(y).at(x) == 0 && event->button() == Qt::LeftButton)
    {


    QGraphicsProxyWidget *proxyWidgetItem;
    QLabel *label;
    QMovie *lavaMovie = new QMovie(":/files/images/textures/lava.gif");
    QMovie *endMovie = new QMovie(":/files/images/textures/end.gif");

    QPixmap cloud(":/files/images/textures/cloud.png");
    QPixmap grass(":/files/images/textures/grass.png");
    QPixmap dirt(":/files/images/textures/dirt.png");
    QPixmap brick(":/files/images/textures/brick.png");
    QPixmap spawn(":/files/images/textures/spawn.jpg");


    mapState[y][x] = checkedBlock;


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
    else if (mapState.at(y).at(x) != 0 && event->button() == Qt::RightButton) {

        QPixmap backgoundGrilleR(":/files/images/textures/backgroundEditor.png");
        itemgrille = scene->addPixmap(backgoundGrilleR);
        itemgrille->setPos(x * pixelMap, y * pixelMap);
        mapState[y][x] = 0;
    }
    else
    {
        qDebug()<< "aleready block";
    }*/
}

void mapEditor::mousePressEvent( QMouseEvent* event )
{

    qDebug() << "mouse" << checkedBlock << event->pos().x() << event->pos().y() << event->pos().x()/32 << event->pos().y()/32;
    int x = event->pos().x()/32, y = event->pos().y()/32;

    if(mapState.at(y).at(x) == 0 && event->button() == Qt::LeftButton)
    {


    QGraphicsProxyWidget *proxyWidgetItem;
    QLabel *label;
    QMovie *lavaMovie = new QMovie(":/files/images/textures/lava.gif");
    QMovie *endMovie = new QMovie(":/files/images/textures/end.gif");

    QPixmap cloud(":/files/images/textures/cloud.png");
    QPixmap grass(":/files/images/textures/grass.png");
    QPixmap dirt(":/files/images/textures/dirt.png");
    QPixmap brick(":/files/images/textures/brick.png");
    QPixmap spawn(":/files/images/textures/spawn.jpg");


    mapState[y][x] = checkedBlock;


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
    else if (mapState.at(y).at(x) != 0 && event->button() == Qt::RightButton) {

        QPixmap backgoundGrilleR(":/files/images/textures/backgroundEditor.png");
        itemgrille = scene->addPixmap(backgoundGrilleR);
        itemgrille->setPos(x * pixelMap, y * pixelMap);
        mapState[y][x] = 0;
    }
    else
    {
        qDebug()<< "aleready block";
    }
}

void mapEditor::on_spawnButton_clicked()
{
   // drawLines();
    ui->lavaButton->setChecked(false);
    ui->brickButton->setChecked(false);
    ui->cloudButton->setChecked(false);
    ui->dirtButton->setChecked(false);
    ui->endLevelButton->setChecked(false);
    ui->grassButton->setChecked(false);
    ui->spawnButton->setChecked(true);
    checkedBlock = 4;

}

void mapEditor::on_lavaButton_clicked()
{
    ui->lavaButton->setChecked(true);
    ui->brickButton->setChecked(false);
    ui->cloudButton->setChecked(false);
    ui->dirtButton->setChecked(false);
    ui->endLevelButton->setChecked(false);
    ui->grassButton->setChecked(false);
    ui->spawnButton->setChecked(false);
    checkedBlock = 6;
}

void mapEditor::on_grassButton_clicked()
{
    ui->lavaButton->setChecked(false);
    ui->brickButton->setChecked(false);
    ui->cloudButton->setChecked(false);
    ui->dirtButton->setChecked(false);
    ui->endLevelButton->setChecked(false);
    ui->grassButton->setChecked(true);
    ui->spawnButton->setChecked(false);
    checkedBlock = 1;
}

void mapEditor::on_endLevelButton_clicked()
{
    ui->lavaButton->setChecked(false);
    ui->brickButton->setChecked(false);
    ui->cloudButton->setChecked(false);
    ui->dirtButton->setChecked(false);
    ui->endLevelButton->setChecked(true);
    ui->grassButton->setChecked(false);
    ui->spawnButton->setChecked(false);
    checkedBlock = 7;
}

void mapEditor::on_dirtButton_clicked()
{
    ui->lavaButton->setChecked(false);
    ui->brickButton->setChecked(false);
    ui->cloudButton->setChecked(false);
    ui->dirtButton->setChecked(true);
    ui->endLevelButton->setChecked(false);
    ui->grassButton->setChecked(false);
    ui->spawnButton->setChecked(false);
    checkedBlock = 2;
}

void mapEditor::on_cloudButton_clicked()
{
    ui->lavaButton->setChecked(false);
    ui->brickButton->setChecked(false);
    ui->cloudButton->setChecked(true);
    ui->dirtButton->setChecked(false);
    ui->endLevelButton->setChecked(false);
    ui->grassButton->setChecked(false);
    ui->spawnButton->setChecked(false);
    checkedBlock = 8;
}

void mapEditor::on_brickButton_clicked()
{
    ui->lavaButton->setChecked(false);
    ui->brickButton->setChecked(true);
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
    ui->loadingWidget->hide();
    //scene->clear();
    QPixmap backgoundGrilleR(":/files/images/textures/backgroundEditor.png");
    QList<int> temp ;

    for (int y=0; y<defaultHeight;y++)
    {
        temp.clear();
        for (int x=0;x<defaultwidth;x++)
        {
            temp.append(0);
            itemgrille = scene->addPixmap(backgoundGrilleR);
            itemgrille->setPos(x*pixelMap,y*pixelMap);
        }
        mapState.append(temp);

    }
   // qDebug()<< mapState;

    //on remet le list des element !

}

void mapEditor::on_saveButton_clicked()
{
    ui->saveWidget->show();
}

void mapEditor::on_cancelButton_clicked()
{
    ui->saveWidget->hide();
}

void mapEditor::on_ValidButton_clicked()
{
    if (!QFile::exists("customMaps"))
    {
        QDir().mkdir("customMaps");
    }
    if (ui->FileNameLineEdit->text() != "")
    {
        QString temporyFileName = ui->FileNameLineEdit->text() + ".map";
        QFile file("customMaps/"+temporyFileName);
        QString line ;
        file.open(QIODevice::WriteOnly);
        QTextStream outStream(&file);

        for(int y= 0;y<5;y++)
        {
            line.clear();
            for(int x=0;x<mapState.at(0).length();x++)
            {
                line.append(QString::number(0));
            }
            outStream << line + "\n";
        }



        for (int y=0; y<mapState.length();y++)
        {
            line.clear();
            for (int x=0;x<mapState.at(y).length();x++)
            {
                line.append(QString::number(mapState.at(y).at(x)));
            }
            outStream << line + "\n";

        }

        for(int y= 0;y<5;y++)
        {
            line.clear();
            for(int x=0;x<mapState.at(0).length();x++)
            {
                if (y>2)
                line.append(QString::number(6));
                else
                line.append(QString::number(0));
            }
            outStream << line + "\n";
        }
        file.close();
    }
    else
    {
        QMessageBox::critical(this,"Erreur", "Vous devez remplir un nom de fichie");
    }
}
