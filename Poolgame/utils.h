#pragma once

#include <QVector2D>
#include <limits>
#include <functional>
#include <QMouseEvent>
#include <memory>
#include <type_traits>
#include <iostream>
#include <QDir>

/* filename of the config file */
constexpr char config_path[] = "config/config.json";
/* filename of the file to store the highscore */
constexpr char highscore_path[] = "highscore.json";
/* filename of the file to export the state */
constexpr char export_path[] = "save.json";
/* the path to the start screen QML */
const QString start_screen_path = "config/start.qml";
/* the path to the confirm scren QML */
const QString confirm_screen_path = "config/QuitConfirm.qml";
/* the path to the menu screen QML */
const QString menu_screen_path = "config/menu.qml";

constexpr int animFrameMS = 16;
constexpr int drawFrameMS = 16;

constexpr double DOUBLEINF = std::numeric_limits<double>::max();
