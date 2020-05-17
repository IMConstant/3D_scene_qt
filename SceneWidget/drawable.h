#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "renderer.h"

namespace gl {
class RenderOptions;
class Renderer;

class Drawable {
    friend class Renderer;
    friend class RenderGroup;

public:
    Drawable();

protected:
    virtual void draw(Renderer &renderer, RenderOptions options) const = 0;
};

}

#endif // DRAWABLE_H
