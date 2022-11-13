#include "../inc/Planet.hpp"

#define GRAV_CONST 0.00000000006673

Planet::Planet(agl::Texture texture, agl::Vec<float, 2> position, float mass, float radius, agl::Color color,
			   bool fixed)
{
	shape.setTexture(&texture);
	this->setPosition(position);
	this->setMass(mass);
	this->setRadius(radius);
	this->setColor(color);
	this->setFixed(fixed);
}

void Planet::setPosition(agl::Vec<float, 2> position)
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
	shape.setSize(agl::Vec<float, 2>{radius, radius});

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

void Planet::setAccceleration(agl::Vec<float, 2> acceleration)
{
	this->acceleration = acceleration;
}

void Planet::setVelocity(agl::Vec<float, 2> velocity)
{
	this->velocity = velocity;
}

void Planet::updateAcceleration(Planet &planet)
{
	if (!fixed)
	{
		float mass = planet.getMass();

		agl::Vec<float, 2> offset = planet.getPosition() - position;

		float distance = agl::hypotenuse(offset);

		float force = ((this->mass * mass) / (distance * distance));
		force *= 1;

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
	agl::Vec<float, 2> oldPos = this->getPosition();
	agl::Vec<float, 2> newPos = {oldPos.x + velocity.x, oldPos.y + velocity.y};

	this->setPosition(newPos);
}

agl::Vec<float, 2> Planet::getPosition()
{
	return position;
}

agl::Vec<float, 2> Planet::getVelocity()
{
	return velocity;
}

agl::Vec<float, 2> Planet::getAcceleration()
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
