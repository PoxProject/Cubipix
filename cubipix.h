#ifndef CUBIPIX_H
#define CUBIPIX_H

#include "map.h"
#include "mapeditor.h"
#include "cubipixsettings.h"
#include "cubipixabout.h"
#include <QMainWindow>
#include <QKeyEvent>
#include <QGridLayout>
#include <QMessageBox>
#include <QtNetwork>
#include <QStandardItemModel>
#include <QMap>
#include <QScrollBar>
#include <QDesktopWidget>

namespace Ui {
class Cubipix;
}

class Cubipix : public QMainWindow
{
    Q_OBJECT

public:
    explicit Cubipix(QWidget *parent = 0);
    ~Cubipix();

private slots:
    void on_playLevelButton_clicked();

    void on_backLevelsButton_clicked();

    void on_mapEditorButton_clicked();

    void buttonLevelClicked();

    void on_customLevelButton_clicked();

    void on_playCustomLevelButton_clicked();

    void on_cancelCustomLevelButton_clicked();

    void on_randomLevelButton_clicked();

    void startMap(QGraphicsScene *scene);
    void updateMap(QGraphicsScene *scene);

    void updateView(int scrollValueWidth, int scrollValueHeight);

    void updateHealth(Player *player);

    void finishPart(Player *player);

    void on_multiplayerButton_clicked();

    void on_backMultiplayerButton_clicked();

    void on_startLocalPartMultiplayerButton_clicked();

    void on_loginButton_clicked();

    void replyLogin(QNetworkReply *reply);

    void on_logoutButton_clicked();

    void addItemsPartsMultiplayerTable();

    void getListParts();

    void replyListParts(QNetworkReply *reply);

    void on_partsMultiplayerTable_doubleClicked(const QModelIndex &index);

    void serverConnected();

    void serverDisconnected();

    void receiveDataServer();

    void sendDataServer(int health, int posX, int posY);

    void serverError(QAbstractSocket::SocketError error);

    void setListPlayers();

    void exitGameWindow();

    void on_backGameButton_clicked();

    void on_settingsGameButton_clicked();

    void on_exitGameButton_clicked();

    void on_continuerResultButton_clicked();

    void on_settingsButton_clicked();

    void on_aboutButton_clicked();

private:
    Ui::Cubipix *ui;

    QVector<Player *> *playersClass;

    Map *map;

    QNetworkAccessManager *manager;

    bool isPlaying;
    bool isMultiplaying;

    bool isExit;

    int userId;
    QString username;

    int rowPlayer;

    int partId;
    int levelId;

    QMap<QString, int> listPlayers;

    QStandardItemModel *model;

    bool editing = false;

    QTcpSocket *socket;
    quint16 sizeMessage;

    int exit;

    void resizeEvent(QResizeEvent *);

    void keyPressEvent(QKeyEvent *);

    void keyReleaseEvent(QKeyEvent *);

    void connectToServer();

    void logC(QString text);
};

#endif // CUBIPIX_H
