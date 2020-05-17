#include "view.h"


namespace gl {

View::View() :
    m_viewPort(QRect(0, 0, 800, 600)),
    m_angle(55.0f),
    m_xScale(QVector2D(-1.0f, 1.0f)),
    m_yScale(QVector2D(-1.0f, 1.0f)) {

}

void View::setAngle(float value) {
    m_angle = value;
}

void View::setViewPort(QRect viewPort) {
    m_viewPort = viewPort;
}

QRect View::getViewPort() const {
    return m_viewPort;
}

float View::getAngle() const {
    return m_angle;
}

QVector2D View::getXScale() const {
    return m_xScale;
}

QVector2D View::getYScale() const {
    return m_yScale;
}


const View View::Default = View();

} // namespace gl
