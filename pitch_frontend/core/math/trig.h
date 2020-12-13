#ifndef TRIG_H
#define TRIG_H

class Degree;

class Radian
{
public:
    constexpr Radian(float value);
    constexpr Radian(const Radian& value) = default;
    constexpr Radian(Radian&& value) = default;
    ~Radian() = default;

    constexpr Radian& operator=(const Radian&) = default;
    constexpr Radian& operator=(Radian&&) = default;

    constexpr Radian operator+(Radian rhs) const;
    constexpr Radian& operator+=(Radian rhs);

    constexpr Radian operator-(Radian rhs) const;
    constexpr Radian& operator-=(Radian rhs);

    constexpr Radian operator*(Radian rhs) const;
    constexpr Radian& operator*=(Radian rhs);

    constexpr Radian operator/(Radian rhs) const;
    constexpr Radian& operator/=(Radian rhs);

    [[nodiscard]] float asFloat() const noexcept;

    static Radian from(Degree degree);

private:
    float value_;
};

class Degree
{
public:
    constexpr Degree(float value);
    constexpr Degree(const Degree& value) = default;
    constexpr Degree(Degree&& value) = default;
    ~Degree() = default;

    constexpr Degree& operator=(const Degree&) = default;
    constexpr Degree& operator=(Degree&&) = default;

    constexpr Degree operator+(Degree rhs);
    constexpr Degree& operator+=(Degree rhs);

    constexpr Degree operator-(Degree rhs);
    constexpr Degree& operator-=(Degree rhs);

    constexpr Degree operator*(Degree rhs);
    constexpr Degree& operator*=(Degree rhs);

    constexpr Degree operator/(Degree rhs);
    constexpr Degree& operator/=(Degree rhs);

    [[nodiscard]] constexpr float asFloat() const noexcept;

    static Degree from(Radian radians);

private:

    float value_;
};

static constexpr auto pi = 3.14159265358979323846L;
static constexpr auto twoPi = 2.0 * pi;
static constexpr auto halfPi = pi / 2.0;

#endif //TRIG_H
