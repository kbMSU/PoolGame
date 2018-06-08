#include "ball.h"
#include <iostream>

std::string Ball::ExportState() {
    std::string content = "";
    content += "{\"position\": {\"x\":"+std::to_string(m_pos.x())+",\"y\":"+std::to_string(m_pos.y())+"},";
    content += "\"velocity\": {\"x\":"+std::to_string(m_velocity.x())+",\"y\":"+std::to_string(m_velocity.y())+"},";
    content += "\"mass\":"+std::to_string(m_mass)+",";
    content += "\"colour\":\""+m_brush.color().name().toStdString()+"\",";
    content += "\"radius\":"+std::to_string(m_radius)+"}\n";
    return content;
}

std::string CompositeBall::ExportState() {
    std::string content = "";
    content += "{\"position\": {\"x\":"+std::to_string(m_pos.x())+",\"y\":"+std::to_string(m_pos.y())+"},";
    content += "\"velocity\": {\"x\":"+std::to_string(m_velocity.x())+",\"y\":"+std::to_string(m_velocity.y())+"},";
    content += "\"mass\":"+std::to_string(m_mass)+",";
    content += "\"colour\":\""+m_brush.color().name().toStdString()+"\",";
    content += "\"radius\":"+std::to_string(m_radius);
    if(m_strength < std::numeric_limits<double>::max()) {
        content += ",\"strength\":"+std::to_string(m_strength);
    }
    if(m_children.size() == 0) {
        content += "}\n";
        return content;
    } else {
        content += ",\n\"balls\": [\n";
        for(int i=0;i<m_children.size();i++) {
            content += m_children[i]->ExportState();
            if(i < m_children.size() - 1) {
                content += ",\n";
            }
        }
        content += "]\n}";
        return content;
    }
}

void StageOneBall::render(QPainter &painter, const QVector2D& offset) {
    // use our colour
    painter.setBrush(m_brush);
    // circle centered
    painter.drawEllipse((offset + m_pos).toPointF(), m_radius, m_radius);
}

void CompositeBall::render(QPainter &painter, const QVector2D& offset) {
    recursiveRender(painter, offset);
}

void CompositeBall::recursiveRender(QPainter &painter, const QVector2D &offset) {
    // use our colour
    painter.setBrush(m_brush);

    // circle centered, plus offset
    painter.drawEllipse((offset + m_pos).toPointF(), m_radius, m_radius);

    // render children potentially
    if (m_renderChildren) for (Ball* b : m_children) b->render(painter, offset + m_pos);
}

bool CompositeBall::applyBreak(const QVector2D &deltaV, std::vector<Ball *> &parentlist) {
    double energyOfCollision = m_mass*deltaV.lengthSquared();
    if (energyOfCollision >= m_strength) {
        if (m_children.empty()) return true;

        // undo the delta to find the precollision velocity
        QVector2D preCollisionVelocity = m_velocity - deltaV;
        double energyPerBall = energyOfCollision/m_children.size();
        QVector2D pointOfCollision((-deltaV.normalized())*m_radius);
        // explode balls away from point of impact
        for (Ball* b : m_children) {
            b->setVelocity(preCollisionVelocity +
                           sqrt(energyPerBall/b->getMass())*
                           (b->getPosition()-pointOfCollision).normalized());
            // move the ball to be absolute
            b->translate(m_pos);
            parentlist.push_back(b);
        }
        return true;
    }
    return false;
}
