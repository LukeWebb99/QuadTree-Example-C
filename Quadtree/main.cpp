#include <iostream>
#include <SFML/Graphics.hpp>
#include "Tools.h"
#include "QuadTree.h"

int main()
{
    srand(time(0));

    std::vector<Point*> particles;

    Rectangle* boundary = new Rectangle(400, 400, 400, 400);
    
    for (size_t i = 0; i < 600; i++) {
        Point* p = new Point(rand() % 400, rand() % 400, 4);
        particles.push_back(p);
       
    }

    std::vector<Point*> inRange;
    bool toggle = false;

    std::cout << "Right mouse to enable & Left mouse to disable\n";

    sf::RenderWindow window(sf::VideoMode(400, 400), "Quadtree");
    while (window.isOpen())
    {
        sf::Event event;
        float lastTime = 0;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Right && !toggle) {
                    std::cout << "Quadtree enabled\n";
                    toggle = true;
                } else if (event.mouseButton.button == sf::Mouse::Left && toggle) {
                    std::cout << "Quadtree disabled\n";
                    toggle = false;
                }
            }
        }

        QuadTree* qt = new QuadTree(boundary, 4);

        window.clear();
        
        for (size_t i = 0; i < particles.size(); i++) {
            particles[i]->Draw(window);
            particles[i]->SetHighlight(false);
            particles[i]->Move(rand() % 3 - 1, rand() % 3 - 1);
            qt->Insert(particles[i]);

            if (!particles[i]->GetHighlight()) {
                if (toggle) {
                    sCircle circle(particles[i]->GetX(), particles[i]->GetY(), particles[i]->GetRadius() * 2);
                    qt->Query(circle, inRange);
                    for (size_t j = 0; j < inRange.size(); j++) {
                        if ((particles[i]->GetX() != inRange[j]->GetX() && particles[i]->GetY() != inRange[j]->GetY()) && !particles[i]->GetHighlight() && particles[i]->Intersects(*inRange[j])) {
                            particles[i]->SetHighlight(true);
                            inRange[j]->SetHighlight(true);
                        }
                    }

                } else {
                    for (size_t j = 0; j < particles.size(); j++) {
                        if ((particles[i]->GetX() != particles[j]->GetX() && particles[i]->GetY() != particles[j]->GetY()) && particles[i]->Intersects(*particles[j])) {
                            particles[i]->SetHighlight(true);
                        }
                    }
                }
                inRange.clear();
            }
        }

        qt->Draw(window);

        window.display();
        delete qt;
    }

    return 0;
}