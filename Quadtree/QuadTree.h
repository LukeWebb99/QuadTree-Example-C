#pragma once
#include "Tools.h"

class QuadTree
{
public:
    QuadTree();
    QuadTree(Rectangle* _boundary, unsigned int _capacity);
    ~QuadTree();

    bool Insert(Point* p);
    void Subdivide();
    void Query(Rectangle& range, std::vector<Point*>& found);
    void Query(sCircle& range, std::vector<Point*>& found);
    void Draw(sf::RenderTarget& target);
    void ClearTree();

private:
    Rectangle boundary;
    unsigned int capacity;
    std::vector<Point*> points;
    bool divided;

    QuadTree* northWest;
    QuadTree* northEast;
    QuadTree* southWest;
    QuadTree* southEast;
};