//
// Created by Tim Valencony on 03/01/2022.
//

#ifndef SWITCH_H
#define SWITCH_H

#pragma once
#include <QtWidgets>

class Switch : public QAbstractButton {
Q_OBJECT
    Q_PROPERTY(int offset READ offset WRITE setOffset)
    Q_PROPERTY(QBrush brush READ brush WRITE setBrush)

public:
    Switch(QWidget* parent = nullptr);
    Switch(const QBrush& brush, QWidget* parent = nullptr);

    QSize sizeHint() const override;

    QBrush brush() const {
        return _brush;
    }
    void setBrush(const QBrush &brsh) {
        _brush = brsh;
    }

    int offset() const {
        return _x;
    }
    void setOffset(int o) {
        _x = o;
        update();
    }

protected:
    void paintEvent(QPaintEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
    void enterEvent(QEnterEvent*);

private:
    bool _switch;
    qreal _opacity;
    int _x, _y, _height, _margin;
    QBrush _thumb, _track, _brush;
    QPropertyAnimation *_anim = nullptr;
};
#endif //SWITCH_H
