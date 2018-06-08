#include "table.h"
#include "ball.h"
#include <iostream>

std::string Table::ExportState() {
    std::string content = "";
    content += "\"colour\": \"" + m_brush.color().name().toStdString() + "\",\n";
    content += "\"size\": {\n\"x\": " + std::to_string(m_width) + ",\n" + "\"y\": " + std::to_string(m_height) + "\n},\n";
    content += "\"friction\": " + std::to_string(m_friction) + "\n";
    return content;
}

std::string StageTwoTable::ExportState() {
    std::string content = Table::ExportState() + ",\n";
    content += "\"pockets\": [\n";
    for(int i=0;i<m_pockets.size();i++) {
        content += m_pockets[i]->ExportState();
        if(i < m_pockets.size()-1) {
            content += ",\n";
        }
    }
    content += "]\n";
    return content;
}

void StageOneTable::render(QPainter &painter, const QVector2D& offset) {
    // our table colour
    painter.setBrush(m_brush);
    // draw table
    painter.drawRect(offset.x(), offset.y(), this->getWidth(), this->getHeight());
}

void StageTwoTable::render(QPainter &painter, const QVector2D& offset) {
    // our table colour
    painter.setBrush(m_brush);
    // draw table
    painter.drawRect(offset.x(), offset.y(), this->getWidth(), this->getHeight());

    // render the pockets relative to this table
    for (Pocket* p : m_pockets) {
        p->render(painter, offset);
    }
}

StageTwoTable::~StageTwoTable() {
    for (Pocket* p : m_pockets) delete p;
}

bool StageTwoTable::sinks(Ball *b) {
    QVector2D absPos = b->getPosition();
    double radius = b->getRadius();
    // check whether any pockets consumes this ball
    for (Pocket* p : m_pockets) {
        // you sunk my scrabbleship
        if (p->contains(absPos, radius)) {
            p->incrementSunk();
            return true;
        }
    }
    return false;
}

int StageTwoTable::getScore() {
    int score = 0;
    for(Pocket* p : m_pockets) {
        score += p->getSunk();
    }
    return score;
}
