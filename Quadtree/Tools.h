#pragma once
#include <sfml/Graphics.hpp>

class Point
{
public:
	Point();
    Point(float _x, float _y, float _radius);
	~Point();

    float GetX();
    float GetY();

    void SetX(float newX);
    void SetY(float newY);

    float GetRadius();
    bool GetHighlight();

    bool Intersects(Point& other);
    void Move(float _x, float _y);
    void Draw(sf::RenderTarget& target);
    void SetHighlight(bool highlightValue);


private:
    float x, y, radius;
    bool highlight;
};

struct Rectangle {

    Rectangle();
    Rectangle(float _x, float _y, float _w, float _h);
    ~Rectangle();

    bool containsPoint(Point* p);
    bool Intersects(Rectangle& range);

    float x, y, w, h;
};

struct sCircle
{
    sCircle();
    sCircle(float _x, float _y, float _radius);

    bool containsPoint(Point* p);
    bool Intersects(Rectangle& range);

    float x, y, radius;
};
