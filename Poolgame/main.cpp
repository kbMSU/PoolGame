/**
  *     Written by Tim Burr
  *     2018/05/18
  */

#include <QObject>
#include "dialog.h"
#include "game.h"
#include "utils.h"
#include "gamebuilder.h"
#include "stagetwobuilder.h"
#include <QApplication>
#include <QFile>
#include <iostream>
#include <QString>
#include <QJsonObject>
#include <ctime>
#include <QJsonDocument>
#include <QtQuick>
#include <QtQml>
#include <QDir>

QJsonObject loadConfig() {
    // load json from config file
    QFile conf_file(config_path);
    conf_file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString content = conf_file.readAll();
    conf_file.close();
    QJsonObject config = QJsonDocument::fromJson(content.toUtf8()).object();
    return config;
}

int main(int argc, char *argv[])
{
    QJsonObject conf = loadConfig();

    // seed our RNG
    srand(time(nullptr));

    // create our game based on our config
    GameDirector director(&conf);
    // use builder2 if we're stage 2 or 3 (defaults to false), otherwise use stage 1 builder
    // my stage 3 does not change the config file in any meaningful way and so does not need a new builder
    bool stage2 = conf.value("stage2").toBool(false);
    bool stage3 = conf.value("stage3").toBool(false);
    if (stage3) {
        director.setStage(3);
        director.setBuilder(new StageTwoBuilder());
    } else if (stage2) {
        director.setStage(2);
        director.setBuilder(new StageTwoBuilder());
    } else {
        // set and transfer ownership of this builder to the director
        director.setBuilder(new StageOneBuilder());
    }

    Game* game = director.createGame();

    // display our dialog that contains our game and run
    QApplication a(argc, argv);

    Dialog w(game, nullptr);

    return a.exec();
}
