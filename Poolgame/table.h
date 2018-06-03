#pragma once

#include <QColor>
#include <QPainter>

#include "pocket.h"

class Ball;

class Table {
protected:
    int m_width;
    int m_height;
    QBrush m_brush;
    double m_friction;
public:
    virtual ~Table() {}
    Table(int width, int height, QColor colour, double friction) :
        m_width(width), m_height(height),
        m_brush(colour), m_friction(friction) {}
    /*Table(Table& table) :
        m_width(table.getWidth()), m_height(table.getHeight()),
        m_brush(table.getBrush()), m_friction(table.getFriction()) {}*/
    /**
     * @brief render - draw the table to screen using the specified painter
     * @param painter - painter to use
     */
    virtual void render(QPainter& painter, const QVector2D& offset) = 0;

    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    double getFriction() const { return m_friction; }
    QBrush getBrush() const { return m_brush; }

    virtual bool sinks(Ball*) { return false; }
};

class StageOneTable : public Table
{
public:
    StageOneTable(int width, int height, QColor colour, double friction) :
        Table(width, height, colour, friction) {}
    /*StageOneTable(StageOneTable& table) : Table(table) {}*/

    /**
     * @brief render - draw the stageonetable to screen using the specified painter
     * @param painter - painter to use
     */
    void render(QPainter &painter, const QVector2D& offset) override;
};

class StageTwoTable : public Table {
protected:
    std::vector<Pocket*> m_pockets;

public:
    StageTwoTable(int width, int height, QColor colour, double friction) :
        Table(width, height, colour, friction) {}
    /*StageTwoTable(StageTwoTable& table) :
        Table(table), m_pockets(table.getPockets()) {}*/

    ~StageTwoTable();

    std::vector<Pocket*> getPockets() {return m_pockets;}

    /**
     * @brief render - draw the stageonetable to screen using the specified painter
     * @param painter - painter to use
     */
    void render(QPainter &painter, const QVector2D& offset) override;

    // sinky winky ball
    virtual bool sinks(Ball* b) override;

    /* self explanatory */
    void addPocket(Pocket* p) { m_pockets.push_back(p); }
};
