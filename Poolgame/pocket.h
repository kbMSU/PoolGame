#pragma once

#include <QVector2D>
#include <QPainter>
#include <QBrush>
#include <cmath>

class Pocket
{
    double m_radius;
    QVector2D m_pos;
    // default rendering colour for pockets is just black
    QBrush m_pocketBrush = QBrush(QColor("black"));

    size_t m_sunk = 0;
public:
    Pocket(double radius, QVector2D pos) : m_radius(radius), m_pos(pos) {}
    Pocket(Pocket& pocket) :
        m_radius(pocket.getRadius()),m_pos(pocket.getPosition()),
        m_pocketBrush(pocket.getBrush()),m_sunk(pocket.getSunk()) {}
    virtual ~Pocket() {}

    /**
     * @brief duplicate - Create a deep copy of the pocket
     * @return Pocket pointer
     */
    virtual Pocket* duplicate() { return new Pocket(*this); }

    /**
     * @brief ExportState - creates a string (formatted JSON) of the pocket
     * @return state as a string
     */
    virtual std::string exportState();

    /**
     * @brief render - draw the pocket to the screen with the provided brush and offset
     * @param painter - the brush to paint with
     * @param offset - the offset from the window
     */
    void render(QPainter& painter, const QVector2D& offset);

    /// whether this pocket contains the circle defined by the arguments
    bool contains(const QVector2D& center, const double& radius) {
        return ((center-m_pos).length() < fabs(radius - m_radius));
    }

    /** add whether this pocket has sunk a ball */
    void incrementSunk() { ++m_sunk; }

    double getRadius() {return m_radius;}
    QVector2D getPosition() {return m_pos;}
    QBrush getBrush() {return m_pocketBrush;}
    size_t getSunk() {return m_sunk;}
};
