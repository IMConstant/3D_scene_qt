#include "color.h"


namespace gl {

Color::Color(float _r, float _g, float _b, float _a) :
    r(_r), g(_g), b(_b), a(_a) {}

Color const Color::Red         = Color(1.0f, 0.0f, 0.0f);
Color const Color::Green       = Color(0.0f, 1.0f, 0.0f);
Color const Color::Blue        = Color(0.0f, 0.0f, 1.0f);
Color const Color::Black       = Color(0.0f, 0.0f, 0.0f);
Color const Color::White       = Color(1.0f, 1.0f, 1.0f);
Color const Color::Yellow      = Color(1.0f, 1.0f, 0.0f);
Color const Color::Transparent = Color(0.0f, 0.0f, 0.0f, 0.0f);
Color const Color::Cyan        = Color(0, 1.0f, 1.0f);
Color const Color::Gray        = Color(1.0f, 1.0f, 1.0f);

} // namespace gl
