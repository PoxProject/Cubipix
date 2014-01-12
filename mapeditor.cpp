#include "mapeditor.h"
#include "ui_mapeditor.h"

mapEditor::mapEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mapEditor)
{
    ui->setupUi(this);

    setWindowTitle(QString("Editeur de map - Cubipix"));

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
    ui->loadMapWidget->setGeometry(0,0, this->width(),this->height());
    ui->loadMap->setGeometry((this->width()/2)-(ui->loadMap->width()/2),(this->height()/2)-(ui->loadMap->height()/2), ui->loadMap->width(),ui->loadMap->height());
    ui->loadMapWidget->hide();
    //drawLines();

    ui->dirtButton->setChecked(true);

    checkedBlock = 2;
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

    ui->loadMapWidget->setGeometry(0,0, this->width(),this->height());
    ui->loadMap->setGeometry((this->width()/2)-(ui->loadMap->width()/2),(this->height()/2)-(ui->loadMap->height()/2), ui->loadMap->width(),ui->loadMap->height());


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

    QPixmap backgoundGrilleR(":/files/images/textures/backgroundEditor.png");
    QList<int> temp;

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

        if(!QFileInfo::exists("customMaps/" + temporyFileName))
        {
            QFile file("customMaps/" + temporyFileName);
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

            ui->saveWidget->hide();
        }
        else
        {
            QMessageBox::critical(this, "Erreur", "Un fichier existe déjà avec ce nom.");
        }
    }
    else
    {
        QMessageBox::critical(this,"Erreur", "Vous devez renseigner un nom de fichier.");
    }
}

void mapEditor::on_openMapFile_clicked()
{
    ui->fileList->clear();

    QDir recoredDir("customMaps");
    recoredDir.setFilter(QDir::Files | QDir::NoSymLinks);
    QStringList listFilters;
    listFilters << "*.map";
    recoredDir.setNameFilters(listFilters);
    QFileInfoList list = recoredDir.entryInfoList();
    for (int i=0;i<list.length();i++)
    {
        QFileInfo info = list.at(i);
        ui->fileList->addItem(info.fileName());
    }
    ui->loadMapWidget->show();
}

void mapEditor::on_loadMapButton_clicked()
{
    if(ui->fileList->currentItem()->text() != "")
    {
        scene->clear();
        drawLines();

        QString filename = ui->fileList->currentItem()->text(), path = "customMaps/"+filename;
        ui->loadMapWidget->hide();
        ui->fileList->clear();
        qDebug() << filename;
        ui->FileNameLineEdit->setText(QFileInfo(path).baseName());
        QFile inputFile(path);

        if(inputFile.open(QIODevice::ReadOnly) && inputFile.exists())
        {
            QGraphicsItem *item;
            QGraphicsProxyWidget *proxyWidgetItem;
            QLabel *label;

            QMovie *lavaMovie = new QMovie(":/files/images/textures/lava.gif");
            QMovie *endMovie = new QMovie(":/files/images/textures/end.gif");

            QPixmap cloud(":/files/images/textures/cloud.png");
            QPixmap grass(":/files/images/textures/grass.png");
            QPixmap dirt(":/files/images/textures/dirt.png");
            QPixmap brick(":/files/images/textures/brick.png");
            QPixmap spawn(":/files/images/textures/spawn.jpg");
            QList<int> temp;
            int numberLineTotal = 0;

            QTextStream in(&inputFile);
            mapState.clear();

            while (!in.atEnd())
            {
                in.readLine();
                numberLineTotal++;
            }
            in.seek(0);
            // 5 ligne lue dans le vide
            in.readLine();in.readLine();in.readLine();in.readLine();in.readLine();
            for (int y=0;y<(numberLineTotal-10);y++)
            {

               QString line = in.readLine();
               qDebug() << line << " " << line.length();

               for(int i =0;i<line.length();i++)
               {
                   switch (QString(line.at(i)).toInt())
                   {
                   case 1:
                       item = scene->addPixmap(grass);
                       item->setPos(i * pixelMap, y * pixelMap);
                       temp.append(1);
                       break;
                   case 2:
                       item = scene->addPixmap(dirt);
                       item->setPos(i * pixelMap, y * pixelMap);
                       temp.append(2);
                       break;
                   case 3:
                       item = scene->addPixmap(brick);
                       item->setPos(i * pixelMap, y * pixelMap);
                       temp.append(3);
                       break;
                   case 4:
                       item = scene->addPixmap(spawn);
                       item->setPos(i * pixelMap, y * pixelMap);
                       temp.append(4);
                       break;
                   case 6:
                       qDebug() << "lava";

                       label = new QLabel();
                       label->setMovie(lavaMovie);

                       lavaMovie->start();

                       proxyWidgetItem = scene->addWidget(label);
                       proxyWidgetItem->setPos(i * pixelMap, y * pixelMap);
                       temp.append(6);
                       break;
                   case 7:
                       qDebug() << "end";

                       label = new QLabel();
                       label->setMovie(endMovie);

                       endMovie->start();

                       proxyWidgetItem = scene->addWidget(label);
                       proxyWidgetItem->setPos(i * pixelMap, (y * pixelMap) - 64);
                       temp.append(7);
                       break;
                   case 8:
                       item = scene->addPixmap(cloud);
                       item->setPos(i * pixelMap, y * pixelMap);
                       temp.append(8);
                       break;
                   default:
                       temp.append(0);
                       break;
                   }
               }

               mapState.append(temp);
               temp.clear();
            }

            inputFile.close();
        }
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Aucune map n'a été séléctionnée.");
    }
}

void mapEditor::on_cancelLoadMapButton_clicked()
{
    ui->loadMapWidget->hide();
    ui->fileList->clear();
}

void mapEditor::on_newMapButton_clicked()
{
    drawLines();
}
