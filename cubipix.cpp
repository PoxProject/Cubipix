#include "cubipix.h"
#include "ui_cubipix.h"

Cubipix::Cubipix(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Cubipix)
{
    ui->setupUi(this);

    ui->homeWidget->setGeometry(0, 0, this->width(), this->height());
    ui->customLevelWidget->setGeometry(0, 0, this->width(), this->height());
    ui->levelsWidget->setGeometry(0, 0, this->width(), this->height());
    ui->gameWidget->setGeometry(0, 0, this->width(), this->height());
    ui->multiplayerModeWidget->setGeometry(0, 0, this->width(), this->height());
    ui->multiplayerPartsWidget->setGeometry(0, 0, this->width(), this->height());
    ui->exitGameWidget->setGeometry(0, 0, this->width(), this->height());
    ui->finishPartWidget->setGeometry(0, 0, this->width(), this->height());

    ui->titleGameLabel->move((this->width() / 2) - ui->titleGameLabel->width(), (this->width() / 2) - 550);
    ui->homeButtonsWidget->move((this->width() / 2) - ui->homeButtonsWidget->width(), (this->width() / 2) - 400);

    ui->customLevelWidget->hide();
    ui->levelsWidget->hide();
    ui->gameWidget->hide();
    ui->multiplayerModeWidget->hide();
    ui->multiplayerPartsWidget->hide();
    ui->exitGameWidget->hide();
    ui->finishPartWidget->hide();

    ui->playersListMultiplayerWidget->hide();

    ui->infoPlayer1Widget->hide();
    ui->infoPlayer2Widget->hide();

    ui->healthPlayer1ProgressBar->setTextVisible(false);
    ui->healthPlayer1ProgressBar->setRange(0, 10);

    ui->healthPlayer2ProgressBar->setTextVisible(false);
    ui->healthPlayer2ProgressBar->setRange(0, 10);

    ui->healthPlayerResultProgressBar->setTextVisible(false);
    ui->healthPlayerResultProgressBar->setRange(0, 10);

    playersClass = new QVector<Player *>();

    multiplayer = 0;
    exit = 0;
}

Cubipix::~Cubipix()
{
    delete ui;
}

void Cubipix::on_playLevelButton_clicked()
{
    QGridLayout *layout = new QGridLayout();

    int colonne = 0, line = 0;

    for(int i = 0; i < 80; i++)
    {
        QPushButton *button = new QPushButton();

        button->setText(QString::number(i + 1));
        button->resize(100, 100);

        layout->addWidget(button, line, colonne);

        connect(button, SIGNAL(clicked()), this, SLOT(buttonLevelClicked()));

        if(colonne == 9)
        {
            colonne = 0;
            line++;
        }
        else
        {
            colonne++;
        }
    }

    ui->listButtonLevelsScrollArea->setLayout(layout);

    ui->homeWidget->hide();
    ui->gameWidget->hide();
    ui->levelsWidget->show();
}

void Cubipix::on_mapEditorButton_clicked()
{
    mapEditor *editor = new mapEditor();
    editor->show();
}

void Cubipix::on_backLevelsButton_clicked()
{
    ui->levelsWidget->hide();
    ui->gameWidget->hide();
    ui->multiplayerModeWidget->hide();
    ui->homeWidget->show();
}

void Cubipix::on_customLevelButton_clicked()
{
    ui->customLevelListWidget->clear();

    QDir dirCustomMaps("customMaps");
    dirCustomMaps.setFilter(QDir::Files | QDir::NoSymLinks);

    QStringList listFilters;
    listFilters << "*.map";

    dirCustomMaps.setNameFilters(listFilters);

    QFileInfoList list = dirCustomMaps.entryInfoList();

    for (int i=0;i<list.length();i++)
    {
        QFileInfo info = list.at(i);

        ui->customLevelListWidget->addItem(info.fileName());
    }

    ui->customLevelWidget->show();
}

void Cubipix::on_playCustomLevelButton_clicked()
{
    if(ui->customLevelListWidget->currentItem()->text() != "")
    {
        Player *player = new Player(1, 1, "User", 1, 0, 0);

        playersClass->clear();

        playersClass->append(player);

        map = new Map();

        connect(map, SIGNAL(startMap(QGraphicsScene*)), this, SLOT(startMap(QGraphicsScene*)));
        connect(map, SIGNAL(updateMap(QGraphicsScene*)), this, SLOT(updateMap(QGraphicsScene*)));
        connect(map, SIGNAL(updateView(int,int)), this, SLOT(updateView(int,int)));
        connect(map, SIGNAL(updateHealth(Player*)), this, SLOT(updateHealth(Player*)));
        connect(map, SIGNAL(finishPart(Player*)), this, SLOT(finishPart(Player*)));

        map->updateValueSizeMapView(this->width(), this->height());

        if(map->playCustomLevel(ui->customLevelListWidget->currentItem()->text()))
        {
            map->spawnPlayer(playersClass->at(0));

            ui->namePlayer1Label->setText(playersClass->at(0)->getUsername());
            ui->healthPlayer1ProgressBar->setValue(playersClass->at(0)->getHealth());

            ui->infoPlayer1Widget->show();

            setListPlayers();

            ui->homeWidget->hide();
            ui->levelsWidget->hide();
            ui->gameWidget->show();
        }
        else
        {
            QMessageBox::critical(this, "Erreur", "Une erreur s'est produite lors de la génération de la map. Réessayez ou contactez un administrateur.");
        }
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Aucun niveau personnalisé n'a été séléctionné.");
    }
}

void Cubipix::on_cancelCustomLevelButton_clicked()
{
    ui->customLevelWidget->hide();
}

void Cubipix::on_randomLevelButton_clicked()
{
    QMessageBox::information(this, "Information", "Cette fonctionnalité n'est pas encore disponible.");
}

void Cubipix::buttonLevelClicked()
{
    QPushButton *button = (QPushButton*)sender();

    qDebug() << button->text();

    Player *player = new Player(1, 1, "User", 1, 0, 0);

    playersClass->clear();

    playersClass->append(player);

    map = new Map();

    connect(map, SIGNAL(startMap(QGraphicsScene*)), this, SLOT(startMap(QGraphicsScene*)));
    connect(map, SIGNAL(updateMap(QGraphicsScene*)), this, SLOT(updateMap(QGraphicsScene*)));
    connect(map, SIGNAL(updateView(int,int)), this, SLOT(updateView(int,int)));
    connect(map, SIGNAL(updateHealth(Player*)), this, SLOT(updateHealth(Player*)));
    connect(map, SIGNAL(finishPart(Player*)), this, SLOT(finishPart(Player*)));

    map->updateValueSizeMapView(this->width(), this->height());

    if(map->playLevel(button->text().toInt()))
    {
        map->spawnPlayer(playersClass->at(0));

        ui->namePlayer1Label->setText(playersClass->at(0)->getUsername());
        ui->healthPlayer1ProgressBar->setValue(playersClass->at(0)->getHealth());

        ui->infoPlayer1Widget->show();

        setListPlayers();

        ui->homeWidget->hide();
        ui->levelsWidget->hide();
        ui->gameWidget->show();
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Une erreur s'est produite lors de la génération de la map. Réessayez ou contactez un administrateur.");
    }
}

void Cubipix::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    ui->homeWidget->setGeometry(0, 0, this->width(), this->height());
    ui->customLevelWidget->setGeometry(0, 0, this->width(), this->height());
    ui->levelsWidget->setGeometry(0, 0, this->width(), this->height());
    ui->gameWidget->setGeometry(0, 0, this->width(), this->height());
    ui->mapView->setGeometry(0, 0, this->width(), this->height());
    ui->multiplayerModeWidget->setGeometry(0, 0, this->width(), this->height());
    ui->multiplayerPartsWidget->setGeometry(0, 0, this->width(), this->height());
    ui->exitGameWidget->setGeometry(0, 0, this->width(), this->height());
    ui->finishPartWidget->setGeometry(0, 0, this->width(), this->height());

    ui->titleGameLabel->move((this->width() / 2) - ui->titleGameLabel->width(), (this->height() / 2) - 220);
    ui->homeButtonsWidget->move((this->width() / 2) - (ui->homeButtonsWidget->width() - 38), (this->height() / 2) - 100);

    //exitGameWidget
    ui->backGameButton->move(((this->width() / 2) - 111), (this->height() / 2) - 140);
    ui->settingsGameButton->move(((this->width() / 2) - 111), (this->height() / 2) - 60);
    ui->exitGameButton->move(((this->width() / 2) - 111), this->height() / 2);
    ui->resultGameGroupBox->move((this->width() / 2) - 260, (this->height() / 2) - 200);

    ui->playersListMultiplayerWidget->move((this->width() - 191), 20);

    ui->infoPlayer2Widget->move((this->width() - 191), 20);

    if(map)
    {
        map->updateValueSizeMapView(this->width(), this->height());
    }
}

void Cubipix::keyPressEvent(QKeyEvent *event)
{
    if(exit == 0)
    {
        if(event->key() == Qt::Key_Q)
        {
            //qDebug() << "gauche";

            map->startMoveLeft(playersClass->at(0));
        }

        if(event->key() == Qt::Key_D)
        {
            //qDebug() << "droite" ;

            //map->moveRight(playersClass->at(0));

            map->startMoveRight(playersClass->at(0));
        }

        if(event->key() == Qt::Key_Z)
        {
            //qDebug() << "sauter";

            map->jump(playersClass->at(0));
        }

        if(event->key() == Qt::Key_U)
        {
            //qDebug() << "player2";

            //map->moveRight(playersClass->at(1));
        }

        if(event->key() == Qt::Key_R)
        {
            map->startShotWeapon(playersClass->at(0));
        }

        if(multiplayer == 1)
        {
            //qDebug() << "sendInformationsPlayer";

            sendDataServer(playersClass->at(0)->getHealth(), playersClass->at(0)->getPosX(), playersClass->at(0)->getPosY());
        }
    }

    if(event->key() == Qt::Key_Escape)
    {
        exitGameWindow();
    }
}

void Cubipix::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Q)
    {
        map->stopMoveLeft(playersClass->at(0));
    }

    if(event->key() == Qt::Key_D)
    {
        map->stopMoveRight(playersClass->at(0));
    }

    if(event->key() == Qt::Key_Z)
    {
        map->jump(playersClass->at(0));
    }

    if(event->key() == Qt::Key_R)
    {
        map->stopShotWeapon(playersClass->at(0));
    }
}

void Cubipix::startMap(QGraphicsScene *scene)
{
    logC("startMap");

    ui->mapView->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute | Qt::AlignBottom);
    ui->mapView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->mapView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->mapView->setScene(scene);
}

void Cubipix::updateMap(QGraphicsScene *scene)
{
    logC("updateMap");

    ui->mapView->setScene(scene);
}

void Cubipix::updateView(int scrollValueWidth, int scrollValueHeight)
{
    ui->mapView->horizontalScrollBar()->setValue(scrollValueWidth);
    ui->mapView->verticalScrollBar()->setValue(scrollValueHeight);
}

void Cubipix::updateHealth(Player *player)
{
    //qDebug() << "updateHealth";

    ui->healthPlayer1ProgressBar->setValue(player->getHealth());
}

void Cubipix::finishPart(Player *player)
{
    logC("finishPart");

    exit = 1;

    if(player->getHealth() > 0)
    {
        ui->mentionResultLabel->setText("Vous avez gagné !");
    }
    else
    {
        ui->mentionResultLabel->setText("Vous avez perdu !");
    }

    ui->pixmapPlayerResultLabel->setPixmap(player->getSkin());

    ui->usernamePlayerResultLabel->setText(player->getUsername());
    ui->healthPlayerResultProgressBar->setValue(player->getHealth());

    ui->mapView->setEnabled(false);
    ui->finishPartWidget->show();
}

//Multiplayer

void Cubipix::on_multiplayerButton_clicked()
{
    ui->homeWidget->hide();
    ui->levelsWidget->hide();
    ui->gameWidget->hide();
    ui->multiplayerModeWidget->show();
}

void Cubipix::on_backMultiplayerButton_clicked()
{
    ui->multiplayerModeWidget->hide();
    ui->levelsWidget->hide();
    ui->gameWidget->hide();
    ui->homeWidget->show();
}

void Cubipix::on_startLocalPartMultiplayerButton_clicked()
{
    if(ui->namePlayer1LineEdit->text() != "" && ui->namePlayer2LineEdit->text() != "")
    {
        Player *player1 = new Player(1, 1, ui->namePlayer1LineEdit->text(), 1, 0, 0);
        Player *player2 = new Player(2, 2, ui->namePlayer2LineEdit->text(), 2, 0, 0);

        playersClass->clear();

        playersClass->append(player1);
        playersClass->append(player2);

        map = new Map();

        connect(map, SIGNAL(startMap(QGraphicsScene*)), this, SLOT(startMap(QGraphicsScene*)));
        connect(map, SIGNAL(updateMap(QGraphicsScene*)), this, SLOT(updateMap(QGraphicsScene*)));
        connect(map, SIGNAL(updateView(int,int)), this, SLOT(updateView(int,int)));
        connect(map, SIGNAL(updateHealth(Player*)), this, SLOT(updateHealth(Player*)));
        connect(map, SIGNAL(finishPart(Player*)), this, SLOT(finishPart(Player*)));

        map->updateValueSizeMapView(this->width(), this->height());

        if(map->playLevel(ui->mapMultiplayerSpinBox->value()))
        {
            map->spawnPlayer(playersClass->at(0));
            map->spawnPlayer(playersClass->at(1));

            ui->namePlayer1Label->setText(playersClass->at(0)->getUsername());
            ui->healthPlayer1ProgressBar->setValue(playersClass->at(0)->getHealth());

            ui->namePlayer2Label->setText(playersClass->at(1)->getUsername());
            ui->healthPlayer2ProgressBar->setValue(playersClass->at(1)->getHealth());

            ui->infoPlayer1Widget->show();
            ui->infoPlayer2Widget->show();

            setListPlayers();

            ui->multiplayerModeWidget->hide();
            ui->homeWidget->hide();
            ui->levelsWidget->hide();
            ui->gameWidget->show();
        }
        else
        {
            QMessageBox::critical(this, "Erreur", "Une erreur s'est produite lors de la génération de la map. Réessayez ou contactez un administrateur.");
        }
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Il est nécéssaire de renseigner deux noms de joueur.");
    }
}

void Cubipix::on_loginButton_clicked()
{
    logC("loginButton");

    if(ui->usernameLineEdit->text() != "" && ui->passwordLineEdit->text() != "")
    {
        QByteArray password;
        password.append(ui->passwordLineEdit->text());

        QByteArray passwordSHA1;
        passwordSHA1 = QCryptographicHash::hash(password, QCryptographicHash::Sha1);

        QString passwordCrypt;
        passwordCrypt = passwordSHA1.toHex();

        manager = new QNetworkAccessManager();
        manager->get(QNetworkRequest(QUrl("http://pox.alwaysdata.net/other/CubipixAPI/login.php?u=" + ui->usernameLineEdit->text() + "&p=" + passwordCrypt)));

        connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyLogin(QNetworkReply*)));
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Vous devez remplir tous les champs.");
    }
}

void Cubipix::replyLogin(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();

    QString answer(data);

    qDebug() << answer;

    if(answer != "false")
    {        
        QStringList infoUser = answer.split(";;");

        userId = infoUser.value(0).toInt();
        username = infoUser.value(1);

        qDebug() << userId;
        qDebug() << username;

        ui->usernameLineEdit->clear();
        ui->passwordLineEdit->clear();

        ui->usernameInfoLabel->setText("Bonjour, " + username + " !");

        addItemsPartsMultiplayerTable();
        getListParts();

        ui->multiplayerModeWidget->hide();
        ui->homeWidget->hide();
        ui->levelsWidget->hide();
        ui->gameWidget->hide();
        ui->multiplayerPartsWidget->show();

        logC("Logged : " + QString::number(userId) + " " + username);
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Votre pseudo ou mot de passe est incorrect.");
    }
}

void Cubipix::on_logoutButton_clicked()
{
    logC("logout");

    userId = NULL;
    username = "";

    ui->usernameInfoLabel->clear();
    ui->statutRemoteServerLabel->clear();

    ui->multiplayerPartsWidget->hide();
    ui->multiplayerModeWidget->hide();
    ui->gameWidget->hide();
    ui->levelsWidget->hide();
    ui->homeWidget->show();
}

void Cubipix::addItemsPartsMultiplayerTable()
{
    model = new QStandardItemModel(this);

    model->setHorizontalHeaderItem(0, new QStandardItem(QString("#")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Nom de la partie")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Map")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Joueurs")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("Admin")));
    model->setHorizontalHeaderItem(5, new QStandardItem(QString("Date de création")));
}

void Cubipix::getListParts()
{
    logC("getListParts");

    manager = new QNetworkAccessManager();
    manager->get(QNetworkRequest(QUrl("http://pox.alwaysdata.net/other/CubipixAPI/getListParts.php?all=true")));

    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyListParts(QNetworkReply*)));
}

void Cubipix::replyListParts(QNetworkReply *reply)
{
    logC("replyListParts");

    QByteArray data = reply->readAll();

    QString answer(data);

    if(answer != "nopart")
    {
        QStringList partsList = answer.split(";;");

        for(int i = 0; i < partsList.count(); i++)
        {
            QStringList infoPart = partsList.value(i).split("||");

            QStandardItem *id = new QStandardItem(infoPart.value(0));
            QStandardItem *name = new QStandardItem(infoPart.value(1));
            QStandardItem *map = new QStandardItem("Niveau " + infoPart.value(2));
            QStandardItem *players = new QStandardItem(infoPart.value(3));
            QStandardItem *owner = new QStandardItem(infoPart.value(4));
            QStandardItem *date = new QStandardItem(infoPart.value(5));

            model->appendRow(QList<QStandardItem *>() << id << name << map << players << owner << date);
        }
    }

    ui->partsMultiplayerTable->setModel(model);
}

void Cubipix::on_partsMultiplayerTable_doubleClicked(const QModelIndex &index)
{
    int id = ui->partsMultiplayerTable->model()->data(ui->partsMultiplayerTable->model()->index(index.row(), 0)).toInt();
    int level = ui->partsMultiplayerTable->model()->data(ui->partsMultiplayerTable->model()->index(index.row(), 0)).toInt();

    qDebug() << id;

    partId = id;
    levelId = 1;

    logC("playPart : " + QString::number(partId) + ", map : " + QString::number(levelId));

    connectToServer();
    sendDataServer(10, 0, 0);
}

void Cubipix::connectToServer()
{
    logC("connectToServer");

    ui->statutRemoteServerLabel->setText("Connexion en cours ...");

    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()), this, SLOT(serverConnected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(serverDisconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(receiveDataServer()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(serverError(QAbstractSocket::SocketError)));

    socket->abort();
    socket->connectToHost("127.0.0.1", 50885);

    sizeMessage = 0;
}

void Cubipix::serverConnected()
{
    logC("connected");

    ui->statutRemoteServerLabel->setText("Chargement en cours ...");

    multiplayer = 1;
    rowPlayer = 2;

    playersClass->clear();

    ui->statutRemoteServerLabel->setText("Connecté au serveur.");

    Player *player = new Player(userId, 1, username, 1, 0, 0);

    playersClass->append(player);

    map = new Map();

    connect(map, SIGNAL(startMap(QGraphicsScene*)), this, SLOT(startMap(QGraphicsScene*)));
    connect(map, SIGNAL(updateMap(QGraphicsScene*)), this, SLOT(updateMap(QGraphicsScene*)));
    connect(map, SIGNAL(updateView(int,int)), this, SLOT(updateView(int,int)));
    connect(map, SIGNAL(updateHealth(Player*)), this, SLOT(updateHealth(Player*)));
    connect(map, SIGNAL(finishPart(Player*)), this, SLOT(finishPart(Player*)));

    map->updateValueSizeMapView(this->width(), this->height());

    if(map->playLevel(levelId))
    {
        map->spawnPlayer(playersClass->at(0));

        ui->namePlayer1Label->setText(playersClass->at(0)->getUsername());
        ui->healthPlayer1ProgressBar->setValue(playersClass->at(0)->getHealth());

        ui->playersListMultiplayerWidget->show();

        ui->infoPlayer1Widget->show();

        ui->multiplayerPartsWidget->hide();
        ui->multiplayerModeWidget->hide();
        ui->homeWidget->hide();
        ui->levelsWidget->hide();
        ui->gameWidget->show();
    }
    else
    {
        ui->statutRemoteServerLabel->setText("Erreur : Impossible de générer la map.");

        QMessageBox::critical(this, "Erreur", "Une erreur s'est produite lors de la génération de la map. Réessayez ou contactez un administrateur");
    }
}

void Cubipix::serverDisconnected()
{
    logC("Disconnected");

    ui->statutRemoteServerLabel->setText("Déconnecté  du serveur.");
}

void Cubipix::receiveDataServer()
{
    logC("dataReceive");

    QDataStream in(socket);

    if (sizeMessage == 0)
    {
        if (socket->bytesAvailable() < (int)sizeof(quint16))
             return;

        in >> sizeMessage;
    }

    if (socket->bytesAvailable() < sizeMessage)
        return;

    QString message;
    in >> message;

    logC(message);

    QStringList infoPart = message.split(";;");

    if(partId == infoPart.value(0).toInt())
    {
        int numberPlayers = infoPart.value(1).toInt();

        logC("numberPlayers : " + QString::number(numberPlayers));

        qDebug() << numberPlayers;
        qDebug() << playersClass->count();

        for(int i = 0; i < numberPlayers; i++)
        {
            QStringList infoPlayer = infoPart.value(i + 2).split("||");

            if(infoPlayer.value(0).toInt() != userId)
            {
                if(listPlayers[infoPlayer.value(0)] == 0)
                {
                    logC("addPlayer");

                    qDebug() << "addPlayer";

                    int numberImage = i + 2;

                    Player *player = new Player(infoPlayer.value(0).toInt(), rowPlayer, infoPlayer.value(1), numberImage, infoPlayer.value(3).toInt(), infoPlayer.value(4).toInt());

                    logC("row : " + QString::number(rowPlayer));

                    rowPlayer++;

                    playersClass->append(player);

                    listPlayers.insert(infoPlayer.value(0), playersClass->count());

                    map->spawnPlayer(playersClass->at(playersClass->count() - 1));

                    logC(infoPlayer.value(0) + " " + infoPlayer.value(1));
                }
                else
                {
                    logC("updatePlayer");

                    qDebug() << "updatePlayer";
                    qDebug() << listPlayers[infoPlayer.value(0)] - 1;

                    playersClass->at(listPlayers[infoPlayer.value(0)] - 1)->updateHealth(infoPlayer.value(2).toInt());
                    playersClass->at(listPlayers[infoPlayer.value(0)] - 1)->updatePos(infoPlayer.value(3).toInt(), infoPlayer.value(4).toInt());

                    qDebug() << "player" << playersClass->at(listPlayers[infoPlayer.value(0)] - 1)->getUsername();

                    map->movePlayerMultiplayer(playersClass->at(listPlayers[infoPlayer.value(0)] - 1), listPlayers[infoPlayer.value(0)] - 1);

                    logC(infoPlayer.value(0) + " " + infoPlayer.value(1) + " " + infoPlayer.value(2) + " " + infoPlayer.value(3) + " " + infoPlayer.value(4));
                }
            }
            else
            {
                logC("myUser");

                qDebug() << "myUser";
            }

            setListPlayers();
        }

        qDebug() << "map" << listPlayers;
    }
    else
    {
        logC("errorPart");

        qDebug() << "errorPart";
    }

    ui->statutRemoteServerLabel->setText(message);

    sizeMessage = 0;
}

void Cubipix::sendDataServer(int health, int posX, int posY)
{
    logC("sendDataServer");

    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    QString messageToSend = QString::number(partId) + ";;" + QString::number(userId) + ";;" + username + ";;" + QString::number(health) + ";;" + QString::number(posX) + ";;" + QString::number(posY);

    out << (quint16) 0;
    out << messageToSend;
    out.device()->seek(0);
    out << (quint16) (paquet.size() - sizeof(quint16));

    socket->write(paquet);
}

void Cubipix::serverError(QAbstractSocket::SocketError error)
{
    logC("serverError");

    switch(error)
    {
        case QAbstractSocket::HostNotFoundError:
            ui->statutRemoteServerLabel->setText("Erreur : Host introuvable.");
            break;
        case QAbstractSocket::ConnectionRefusedError:
            ui->statutRemoteServerLabel->setText("Erreur : Connection refusée.");
            break;
        case QAbstractSocket::RemoteHostClosedError:
            ui->statutRemoteServerLabel->setText("Erreur : Connection coupée.");
            break;
        default:
            ui->statutRemoteServerLabel->setText("Erreur : " + socket->errorString() + ".");
    }
}

void Cubipix::setListPlayers()
{
    logC("setListPlayers");

    ui->playersListWidget->clear();

    int numberPlayer = 0;

    for(int i = 0; i < playersClass->count(); i++)
    {
        numberPlayer++;

        ui->playersListWidget->addItem(playersClass->at(i)->getUsername() + " - " + QString::number(playersClass->at(i)->getHealth()) + " vie(s)");
    }

    ui->numberPlayersLabel->setText(QString::number(numberPlayer));
}

void Cubipix::exitGameWindow()
{
    logC("exitGameWindow");

    if(exit == 1)
    {
        exit = 0;

        ui->exitGameWidget->hide();
        ui->mapView->setEnabled(true);
    }
    else
    {
        exit = 1;

        ui->mapView->setEnabled(false);
        ui->exitGameWidget->show();
    }
}

void Cubipix::on_backGameButton_clicked()
{
    exitGameWindow();
}

void Cubipix::on_settingsGameButton_clicked()
{
    QMessageBox::information(this, "Information", "Cette fonctionnalité n'est pas encore disponible.");
}

void Cubipix::on_exitGameButton_clicked()
{
    logC("exitGameButton");

    playersClass->clear();

    exitGameWindow();

    ui->mentionResultLabel->clear();

    ui->pixmapPlayerResultLabel->clear();

    ui->usernamePlayerResultLabel->clear();
    ui->healthPlayerResultProgressBar->setValue(10);

    ui->gameWidget->hide();
    ui->levelsWidget->hide();
    ui->finishPartWidget->hide();
    ui->multiplayerModeWidget->hide();
    ui->multiplayerPartsWidget->hide();
    ui->homeWidget->show();
}

void Cubipix::logC(QString text)
{
    ui->logCubipix->append(text);
}

void Cubipix::on_continuerResultButton_clicked()
{
    on_exitGameButton_clicked();
}

void Cubipix::on_settingsButton_clicked()
{
    CubipixSettings *settings = new CubipixSettings();
    settings->show();
}

void Cubipix::on_aboutButton_clicked()
{
    CubipixAbout *about = new CubipixAbout();
    about->show();
}
