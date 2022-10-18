#include "../../../AGL/agl.hpp"

class Planet
{
	private:
		agl::Vec2f	position = {0, 0};
		float		mass = 0;
		float		radius = 0;
		bool		fixed = 0;
		agl::Vec2f	velocity = {0, 0};
		agl::Vec2f	acceleration = {0, 0};
		agl::Circle shape = agl::Circle(24);

	public:
		Planet(agl::Texture texture, agl::Vec2f position, float mass, float radius, agl::Color color, bool fixed);
		void setPosition(agl::Vec2f position);
		void setMass(float mass);
		void setRadius(float radius);
		void setColor(agl::Color color);
		void setFixed(bool fixed);

		void setVelocity(agl::Vec2f velocity);

		void updateAcceleration(Planet &planet);
		void updateVelocity();
		void updatePosition();

		agl::Vec2f getPosition();
		agl::Vec2f getVelocity();
		agl::Vec2f getAcceleration();
		float getMass();
		agl::Circle *getShape();
};
