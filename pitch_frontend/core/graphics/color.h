#ifndef COLOR_H
#define COLOR_H

class Color
{
public:
    Color(float red, float green, float blue, float alpha);
    Color(const Color& rhs);
    Color(Color&& rhs) = default;
    ~Color() = default;

    Color& operator=(const Color& rhs);
    Color& operator=(Color&& rhs) = default;

    float r() const noexcept;
    float g() const noexcept;
    float b() const noexcept;
    float a() const noexcept;

    static Color red(float alpha = 1.0f) noexcept;
    static Color green(float alpha = 1.0f) noexcept;
    static Color blue(float alpha = 1.0f) noexcept;
    static Color black(float alpha = 1.0f) noexcept;
    static Color white(float alpha = 1.0f) noexcept;
    static Color greyscale(float value, float alpha = 1.0f) noexcept;

private:
    float values_[4];
};

#endif //COLOR_H
