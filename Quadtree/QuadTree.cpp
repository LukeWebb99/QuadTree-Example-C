#include "QuadTree.h"
#include<iostream>

QuadTree::QuadTree()
{
    boundary = Rectangle(200, 200, 200, 200);
    capacity = 1;
    divided = false;

    northWest = nullptr;
    northEast = nullptr;
    southWest = nullptr;
    southEast = nullptr;
}

QuadTree::QuadTree(Rectangle* _boundary, unsigned int _capacity) {

    boundary = *_boundary;
    capacity = _capacity;
    divided = false;

    northWest = nullptr;
    northEast = nullptr;
    southWest = nullptr;
    southEast = nullptr;
}

QuadTree::~QuadTree()
{
    points.clear();

    if (divided) {
        northWest->ClearTree();
        delete northWest;
        northEast->ClearTree();
        delete northEast;
        southWest->ClearTree();
        delete southWest;
        southEast->ClearTree();
        delete southEast;
    }
}

bool QuadTree::Insert(Point* p) {

    if (!boundary.containsPoint(p)) {
        return false;
    }

    if (points.size() != capacity) {
        points.push_back(p);
        return true;
    }
    else {

        if (!divided) {
            Subdivide();
        }

        if ((northWest->boundary.x + southEast->boundary.x) / 2 >= p->GetX())
        {
            // Indicates northWestTree 
            if ((northWest->boundary.y + southEast->boundary.y) / 2 >= p->GetY())
            {
                northWest->Insert(p);
                return true;
            }

            // Indicates southWestTree 
            else
            {
                southWest->Insert(p);
                return true;
            }
        }
        else
        {
            // Indicates topRightTree 
            if ((northWest->boundary.y + southEast->boundary.y) / 2 >= p->GetY())
            {
                northEast->Insert(p);
                return true;
            }

            // Indicates southEastTree 
            else
            {
                southEast->Insert(p);
                return true;
            }
        }
    }
}

void QuadTree::Subdivide() {

    int x = boundary.x;
    int y = boundary.y;
    int w = boundary.w / 2;
    int h = boundary.h / 2;

    Rectangle ne(x + w, y - h, w, h);
    northEast = new QuadTree(&ne, capacity);
    Rectangle nw(x - w, y - h, w, h);
    northWest = new QuadTree(&nw, capacity);
    Rectangle se(x + w, y + h, w, h);
    southEast = new QuadTree(&se, capacity);
    Rectangle sw(x - w, y + h, w, h);
    southWest = new QuadTree(&sw, capacity);

    divided = true;

}

void QuadTree::Query(Rectangle& range, std::vector<Point*>& found)
{

    if (!boundary.Intersects(range)) {
        return;
    }
    else {
        for (size_t i = 0; i < points.size(); i++) {
            if (range.containsPoint(points[i])) {
                found.push_back(points[i]);
            }
        }
        
        if (divided) {
            northWest->Query(range, found);
            northEast->Query(range, found);
            southWest->Query(range, found);
            southEast->Query(range, found);
        }
    }

}

void QuadTree::Query(sCircle& range, std::vector<Point*>& found)
{
    if (!range.Intersects(boundary)) {
        return;

    } else {

        for (size_t i = 0; i < points.size(); i++) {
            if (range.containsPoint(points[i])) {
                found.push_back(points[i]);
            }
        }

        if (divided) {
            northWest->Query(range, found);
            northEast->Query(range, found);
            southWest->Query(range, found);
            southEast->Query(range, found);
        }
    }
}

void QuadTree::Draw(sf::RenderTarget& target) {

 /*   for (auto& p : points) {
        p->Draw(target);
    }*/

    sf::RectangleShape* Rect = new sf::RectangleShape();
    Rect->setPosition(sf::Vector2f(boundary.x, boundary.y));
    Rect->setOrigin(sf::Vector2f(boundary.w, boundary.h));
    Rect->setSize(sf::Vector2f(boundary.w * 2, boundary.h * 2));
    Rect->setFillColor(sf::Color(0, 0, 0, 0));
    Rect->setOutlineColor(sf::Color::White);
    Rect->setOutlineThickness(1);
    target.draw(*Rect);
    delete Rect;

    if (divided) {
        northEast->Draw(target);
        northWest->Draw(target);
        southEast->Draw(target);
        southWest->Draw(target);
    }
}

void QuadTree::ClearTree()
{

}   