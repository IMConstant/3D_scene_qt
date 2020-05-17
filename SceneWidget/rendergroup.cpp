#include "rendergroup.h"


namespace gl {

RenderGroup::RenderGroup() : Transformable() {}

void RenderGroup::add(Drawable *item) {
    m_items.append(item);
}

void RenderGroup::draw(Renderer &renderer, RenderOptions options) const {
    for (Drawable *item: m_items) {
        item->draw(renderer, RenderOptions(options.transform * getTransform(), options.shaderProgram));
    }
}

} // namespace gl
