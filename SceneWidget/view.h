#ifndef VIEW_H
#define VIEW_H

#include <QGL>
#include <QRect>
#include <QVector2D>


namespace gl {

class View {
    QRect m_viewPort;
    float m_angle;

    QVector2D m_xScale;
    QVector2D m_yScale;

public:
    View();

    void setAngle(float value);
    void setViewPort(QRect viewPort);

    QRect getViewPort() const;
    float getAngle() const;

    QVector2D getXScale() const;
    QVector2D getYScale() const;


    static const View Default;
};

}

#endif // VIEW_H
