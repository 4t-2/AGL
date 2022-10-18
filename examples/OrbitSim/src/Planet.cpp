#include "../inc/Planet.hpp"
#include <math.h>

#define GRAV_CONST 0.00000000006673

Planet::Planet(agl::Texture texture, agl::Vec2f position, float mass, float radius, agl::Color color, bool fixed)
{
	shape.setTexture(&texture);
	this->setPosition(position);
	this->setMass(mass);
	this->setRadius(radius);
	this->setColor(color);
	this->setFixed(fixed);
}

void Planet::setPosition(agl::Vec2f position)
{
	this->position = position;
	shape.setPosition(position);

	return;
}

void Planet::setMass(float mass)
{
	this->mass = mass;

	return;
}

void Planet::setRadius(float radius)
{
	this->radius = radius;
	shape.setSize(agl::Vec2f{radius, radius});

	return;
}

void Planet::setColor(agl::Color color)
{
	shape.setColor(color);
}

void Planet::setFixed(bool fixed)
{
	this->fixed = fixed;
}

void Planet::setVelocity(agl::Vec2f velocity)
{
	this->velocity = velocity;
}

void Planet::updateAcceleration(Planet &planet)
{
	if (!fixed)
	{
		float mass = planet.getMass();

		agl::Vec2f offset = planet.getPosition();
		offset.x -= this->position.x;
		offset.y -= this->position.y;

		float distance = sqrt((offset.x * offset.x) + (offset.y * offset.y));

		float force = GRAV_CONST * ((this->mass * mass) / (distance * distance));
		force *= 10000000000;

		float totalOffset = abs(offset.x) + abs(offset.y);

		acceleration.x += (force / this->mass) * (offset.x / totalOffset);
		acceleration.y += (force / this->mass) * (offset.y / totalOffset);
	}
}

void Planet::updateVelocity()
{
	velocity.x += acceleration.x;
	velocity.y += acceleration.y;
	acceleration = {0, 0};
}

void Planet::updatePosition()
{
	agl::Vec2f oldPos = this->getPosition();
	agl::Vec2f newPos = {oldPos.x + velocity.x, oldPos.y + velocity.y};

	this->setPosition(newPos);
}

agl::Vec2f Planet::getPosition()
{
	return position;
}

agl::Vec2f Planet::getVelocity()
{
	return velocity;
}

agl::Vec2f Planet::getAcceleration()
{
	return acceleration;
}

float Planet::getMass()
{
	return mass;
}

agl::Circle *Planet::getShape()
{
	return &shape;
}
