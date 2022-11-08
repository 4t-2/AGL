#include "../../../AGL/agl.hpp"

class Planet
{
	private:
		agl::Vec<float, 2> position		= {0, 0};
		float			   mass			= 0;
		float			   radius		= 0;
		bool			   fixed		= 0;
		agl::Vec<float, 2> velocity		= {0, 0};
		agl::Vec<float, 2> acceleration = {0, 0};
		agl::Circle		   shape		= agl::Circle(24);

	public:
		Planet(agl::Texture texture, agl::Vec<float, 2> position, float mass, float radius, agl::Color color,
			   bool fixed);
		void setPosition(agl::Vec<float, 2> position);
		void setMass(float mass);
		void setRadius(float radius);
		void setColor(agl::Color color);
		void setFixed(bool fixed);

		void setVelocity(agl::Vec<float, 2> velocity);

		void updateAcceleration(Planet &planet);
		void updateVelocity();
		void updatePosition();

		agl::Vec<float, 2> getPosition();
		agl::Vec<float, 2> getVelocity();
		agl::Vec<float, 2> getAcceleration();
		float			   getMass();
		agl::Circle		  *getShape();
};
