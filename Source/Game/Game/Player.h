#pragma once
#include "Framework/Actor.h"

class Player : public kiko::Actor
{
public:
	Player(float speed, float turnRate, const kiko::Transform& transform, std::shared_ptr<kiko::Model> model) :
		Actor{ transform, model },
		m_speed{ speed },
		m_turnRate{ turnRate }//without it calls the default constructor
	{}

	void Update(float dt) override; //dt for delta time
	void OnCollision(Actor* other) override;

protected:
	float m_speed = 0;
	float m_turnRate = 0;
	int m_health = 100;
};
