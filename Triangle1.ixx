module;

#include <iostream>
#include <fstream>
#include <numbers>
#include <sstream>
export module Triangle1;

export class Triangle1
{
private:
    double side_a;
    double side_b;
    double side_c;
public:
    Triangle1();
    Triangle1(double a, double b, double c);
    friend std::ostream& operator<<(std::ostream& out, const Triangle1& triangle) {
        out << triangle.side_a << ' ' << triangle.side_b << ' ' << triangle.side_c << '\n';
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Triangle1& triangle) {
        in >> triangle.side_a >> triangle.side_b >> triangle.side_c;
        return in;
    }
    bool validate_triangle();
    std::string to_string();
    double get_side_a() const;
    double get_side_b() const;
    double get_side_c() const;
    void set_side_a(double value);
    void set_side_b(double value);
    void set_side_c(double value);

    int compare(const Triangle1& other);
    double perimeter() const;
    double area() const;
    //double height(double base) const;
    std::tuple<double, double, double> heights() const;

    std::string type() const;
    //double* angles() const;
    std::tuple<double, double, double> angles() const;
    bool operator==(const Triangle1& other) const;
    bool operator!=(const Triangle1& other) const;
    Triangle1 operator *(double scalar) const;
    Triangle1 operator /(double scalar) const;
    std::partial_ordering operator<=>(const Triangle1& other) const;
};

bool Triangle1::validate_triangle()
{
    bool res{ true };
    if ((side_a <= 0 || side_b <= 0 || side_c <= 0) ||
        (side_a + side_b <= side_c || side_a + side_c <= side_b || side_b + side_c <= side_a))
        res = false;
    return res;
}

Triangle1::Triangle1()
{
    side_a = side_b = side_c = {};
}

Triangle1::Triangle1(double a, double b, double c)
{
    side_a = { a };
    side_b = { b };
    side_c = { c };
    //validate_triangle();
}

std::string Triangle1::to_string()
{
    std::ostringstream str;
    str << side_a << " " << side_b << " " << side_c;
    return str.str();
}

double Triangle1::get_side_a() const
{
    return side_a;
}

double Triangle1::get_side_b() const
{
    return side_b;
}

double Triangle1::get_side_c() const
{
    return side_c;
}

int Triangle1::compare(const Triangle1& other)
{
    /*int res{};
    if (*this > other)
        res = 1;
    else
    {
        if (*this < other)
            res = 2;
        else
            res = 3;
    }
    return res;*/
    int res{ };
    std::partial_ordering id{ (*this) <=> other };
    if (id == std::partial_ordering::greater)
        res = 1;
    else
        if (id == std::partial_ordering::less)
            res = -1;
    return res;
}

double Triangle1::perimeter() const
{
    return side_a + side_b + side_c;
}

double Triangle1::area() const
{
    double s = perimeter() / 2;
    return std::sqrt(s * (s - side_a) * (s - side_b) * (s - side_c));
}



std::string Triangle1::type() const
{
    std::string type{};

    if (side_a == side_b && side_b == side_c)
        type = "Equilateral";
    else
    {
        if (side_a == side_b || side_a == side_c || side_b == side_c)
            type = "Isosceles";
        else
        {
            if ((side_a * side_a + side_b * side_b == side_c * side_c) || //
                (side_a * side_a + side_c * side_c == side_b * side_b) ||
                (side_b * side_b + side_c * side_c == side_a * side_a))
            {
                type = "Right-angled";
            }
            else type = "Scalene";
        }
    }
    return type;
}

std::tuple<double, double, double> Triangle1::angles() const
{  // Вычисление углов в радианах 
    double angleA = std::acos((side_b * side_b + side_c * side_c - side_a * side_a) / (2 * side_b * side_c));
    double angleB = std::acos((side_a * side_a + side_c * side_c - side_b * side_b) / (2 * side_a * side_c));
    double angleC = std::numbers::pi - angleA - angleB; // Сумма углов в треугольнике равна pi
    return std::make_tuple(angleA, angleB, angleC);
}

bool Triangle1::operator==(const Triangle1& other) const
{
    return std::abs(area() - other.area()) < 1e-9;
}

bool Triangle1::operator!=(const Triangle1& other) const
{
    return std::abs(area() - other.area()) > 1e-9;
}

Triangle1 Triangle1::operator*(double scalar) const
{
    return Triangle1(side_a * scalar, side_b * scalar, side_c * scalar);
}

Triangle1 Triangle1::operator/(double scalar) const
{
    return Triangle1(side_a / scalar, side_b / scalar, side_c / scalar);
}

std::partial_ordering Triangle1::operator<=>(const Triangle1& other) const
{
    std::partial_ordering res;
    if (area() != other.area())
        res = area() <=> other.area();
    return res;
}

void Triangle1::set_side_a(double value)
{
    side_a = value;
}

void Triangle1::set_side_b(double value)
{
    side_b = value;
}

void Triangle1::set_side_c(double value)
{
    side_c = value;
}

std::tuple<double, double, double> Triangle1::heights() const
{
    double area_tmp = area();
    return std::make_tuple((2 * area_tmp) / side_a, (2 * area_tmp) / side_b, (2 * area_tmp) / side_c);
}
