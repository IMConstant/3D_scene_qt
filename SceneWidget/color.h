#ifndef COLOR_H
#define COLOR_H


namespace gl {

struct Color {
    float r;
    float g;
    float b;
    float a;

    Color() = default;
    Color(float _r, float _g, float _b, float _a = 1.0f);

    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color Black;
    static const Color White;
    static const Color Yellow;
    static const Color Transparent;
    static const Color Cyan;
    static const Color Gray;
};

} // namespace gl

#endif // COLOR_H
