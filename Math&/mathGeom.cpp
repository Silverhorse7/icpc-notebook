#include <bits/stdc++.h>
#define EPS 1e-8
#define INF 1e18
using namespace std;
const int MAXN = 30;
inline int sgn(double x)
{
    return x < -EPS ? -1 : x > EPS ? 1 : 0;
}
inline double sqr(double x)
{
    return x * x;
}
#define cPoint const Point
#define cVector const Vector
#define cSeg const Segment
#define cCircle const Circle
struct Point
{
    double x, y;
    Point() {}
    Point(double x, double y) : x(x), y(y) {}
    Point(pair<double, double> p) : x(p.first), y(p.second) {}
    bool operator < (cPoint& rhs) const
    {
        if (sgn(x - rhs.x)) return x < rhs.x;
        else return y < rhs.y;
    }
    inline double angle() const
    {
        return atan2(y, x);
    }
    inline double length() const
    {
        return sqrt(sqr(x) + sqr(y));
    }
};
typedef Point Vector;
Vector operator + (cVector& lhs, cVector& rhs)
{
    return Vector(lhs.x + rhs.x, lhs.y + rhs.y);
}
Vector operator - (cVector& lhs, cVector& rhs)
{
    return Vector(lhs.x - rhs.x, lhs.y - rhs.y);
}
Vector operator * (cVector& v, double mul)
{
    return Vector(v.x * mul, v.y * mul);
}
Vector operator / (cVector& lhs, double rhs)
{
    return Vector(lhs.x / rhs, lhs.y / rhs);
}
inline double dot(cVector& a, cVector& b)
{//点积
    return a.x * b.x + a.y * b.y;
}
inline double cross(cVector& a, cVector& b)
{//叉积
    return a.x * b.y - a.y * b.x;
}
inline double dist(cPoint& a, cPoint& b)
{//两点距离
    return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}
Vector unit(cVector& v)
{//单位向量
    return v / v.length();
}
struct Segment
{
    Point s, e;
    Segment() {}
    Segment(Point s, Point e) : s(s), e(e) {}
    inline double length() const
    {
        return dist(s, e);
    }
};
double dist_to_line(cPoint& p, cSeg& l)
{//点到直线距离
    Vector u = p - l.s, v = p - l.e;
    return fabs(cross(u, v)) / l.length();
}
Point project_on_line(cPoint& p, cSeg& l)
{//点在直线上投影
    Vector v = l.e - l.s;
    return l.s + v * (dot(v, p - l.s) / dot(v, v));
}
bool point_on_segment(cPoint& p, cSeg& seg)
{//点在线段上
    Vector u = unit(p - seg.s), v = unit(p - seg.e);
    return sgn(dot(u, v)) <= 0;
}
struct Circle
{
    Point o;
    double r;
    Circle() {}
    Circle(Point o, double r) : o(o), r(r) {}
    Point point(double rad) const
    {
        return o + Vector(cos(rad), sin(rad)) * r;
    }
};
bool point_in_circle(cPoint& p, cCircle& cir)
{
    return sgn(cir.r - dist(p, cir.o)) >= 0;
}
int line_intersect_circle(cSeg& l, cCircle& cir,
    vector<Point>& res)
{//直线与圆交点
    Point p = project_on_line(cir.o, l);
    double d = dist_to_line(cir.o, l);
    if (sgn(d - cir.r) > 0) return 0;
    else if (sgn(d - cir.r) == 0)
    {
        res.push_back(p);
        return 1;
    }
    else
    {
        Vector v = unit(l.e - l.s);
        double l = sqrt(sqr(cir.r) - sqr(d));
        res.push_back(p - v * l);
        res.push_back(p + v * l);
        return 2;
    }
}
int circle_intersect(cCircle& a, cCircle& b, vector<Point>& res)
{//两圆交点
    double d = dist(a.o, b.o);
    if (sgn(d) == 0) return sgn(a.r - b.r) == 0 ? -1 : 0;
    else if (sgn(a.r + b.r - d) < 0 ||
        sgn(fabs(a.r - b.r) - d) > 0) return 0;
    else
    {
        double base = (b.o - a.o).angle();
        if (sgn(a.r + b.r - d) == 0)
        {
            res.push_back(a.point(base));
            return 1;
        }
        else
        {
            double delta = acos((sqr(a.r) + sqr(d) - sqr(b.r)) /
                (2 * a.r * d));
            res.push_back(a.point(base - delta));
            res.push_back(a.point(base + delta));
            return 2;
        }
    }
}
