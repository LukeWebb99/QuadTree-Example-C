#include "Particle.h"
#include "Tools.h"

Particle::Particle()
{
	highlight = false;
	radius = 1;
	x = 0;
	y = 0;
}

Particle::Particle(float posX, float posY, int _radius) {
	highlight = false;
	radius = _radius;
	x = posX;
	y = posY;
}

Particle::~Particle()
{
}

bool Particle::Intersects(Particle& other)
{
	float dist = std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2) * 1.0);
	if (dist < (radius + other.radius)) {
		return true;
	} else {
		return false;
	}
}

void Particle::Draw(sf::RenderTarget& target)
{
	sf::CircleShape circ(radius);
	circ.setOrigin(circ.getRadius(), circ.getRadius());
	circ.setPosition(x, y);
	circ.setOutlineThickness(0);
	if (highlight) {
		circ.setFillColor(sf::Color(255, 255, 255));
	} else {
		circ.setFillColor(sf::Color(100, 100, 100));
	}
	target.draw(circ);
}

void Particle::Move(int _x, int _y)
{
	x += _x;
	y += _y;
}

void Particle::SetHighlight(bool value)
{
	highlight = value;
}

float Particle::GetParticleX()
{
	return x;
}

float Particle::GetParticleY()
{
	return y;
}

float Particle::GetRadius()
{
	return radius;
}
