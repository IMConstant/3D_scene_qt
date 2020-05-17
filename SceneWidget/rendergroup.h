#ifndef RENDERGROUP_H
#define RENDERGROUP_H


#include "drawable.h"
#include "transformable.h"


namespace gl {

class RenderGroup : public Drawable, public Transformable {
    QVector<Drawable *> m_items;

public:
    RenderGroup();

    void add(Drawable *item);

protected:
    void draw(Renderer &renderer, RenderOptions options) const;
};

} // namespace gl

#endif // RENDERGROUP_H
