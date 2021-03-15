#include "Tools.h"

Point::Point()
{
    x = 0;
    y = 0;
    radius = 0;
    highlight = false;
}

Point::Point(float _x, float _y, float _radius)
{
    x = _x;
    y = _y;
    radius = _radius;
    highlight = false;
}

Point::~Point()
{
}

float Point::GetX()
{
    return x;
}

float Point::GetY()
{
    return y;
}

void Point::SetX(float newX)
{
    x = newX;
}

void Point::SetY(float newY)
{
    y = newY;
}

float Point::GetRadius()
{
    return radius;
}

bool Point::GetHighlight()
{
    return highlight;
}

bool Point::Intersects(Point& other)
{
    float dist = std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2) * 1.0);
    if (dist < (radius + other.radius)) {
        return true;
    }
    else {
        return false;
    }
}

void Point::Move(float _x, float _y)
{
    x += _x;
    y += _y;
}

void Point::Draw(sf::RenderTarget& target)
{
    sf::CircleShape circ(radius);
    circ.setOrigin(circ.getRadius(), circ.getRadius());
    circ.setPosition(x, y);
    circ.setOutlineThickness(0);
    if (highlight) {
        circ.setFillColor(sf::Color(255, 255, 255));
    }
    else {
        circ.setFillColor(sf::Color(100, 100, 100));
    }
    target.draw(circ);
}

void Point::SetHighlight(bool highlightValue)
{
    highlight = highlightValue;
}

Rectangle::Rectangle() {
    x = 0;
    y = 0;
    w = 0;
    h = 0;
}

Rectangle::Rectangle(float _x, float _y, float _w, float _h) {
    x = _x;
    y = _y;
    w = _w;
    h = _h;
    
}

Rectangle::~Rectangle()
{
}

bool Rectangle::containsPoint(Point* p) {

    if  (p->GetX() >= x - w &&
        p->GetX() <= x + w &&
        p->GetY() >= y - h &&
        p->GetY() <= y + h) {
        return true;
    }
    return false;
}

bool Rectangle::Intersects(Rectangle& range) {

    return !(
        range.x - range.w > x + w ||
        range.x + range.w < x - w ||
        range.y - range.h > y + h ||
        range.y + range.h < y - h);

}

sCircle::sCircle()
{
    x = 0;
    y = 0;
    radius = 1;
}

sCircle::sCircle(float _x, float _y, float _radius)
{
    x = _x;
    y = _y;
    radius = _radius;
}

bool sCircle::containsPoint(Point* p)
{
    float dist = std::pow((x - p->GetX()), 2) + std::pow((y - p->GetY()), 2);
    return dist <= (radius * radius);
}

bool sCircle::Intersects(Rectangle& range)
{
    float xDist = std::abs(range.x - x);
    float yDist = std::abs(range.y - y);

    float edges = std::pow((xDist - range.w), 2) + std::pow((yDist - range.h), 2);

    // no intersection
    if (xDist > (radius + range.w) || yDist > (radius + range.h))
        return false;

    // intersection within the circle
    if (xDist <= range.w || yDist <= range.h)
      return true;

    // intersection on the edge of the circle
    return (edges <= (radius*radius));
 
    return false;
}
