#include "Enemy.h"

#include "Laser.h"
#include "Player.h"
#include "Framework/Scene.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Enemy.h"
#include "Laser.h"
#include "Framework/Game.h"
#include "SpaceGame.h"
#include "Audio/AudioSystem.h"
#include "Framework/Emitter.h"

void Enemy::Update(float dt)
{
	Actor::Update(dt);

	kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	Player* player = m_scene->GetActor<Player>();
	if (player)
	{
		kiko::Vector2 direction = player->m_transform.position - m_transform.position;
		m_transform.rotation = direction.Angle() + kiko::HalfPi;

		float angle = kiko::vec2::SignedAngle(forward, direction.Normalized());

		//causing issues for some reason
		if (std::fabs(angle) < kiko::DegreesToRadians(30.0f))
		{
			//decrement the time and reset the timer // use fire timer  => 0 reset the fire timer
			if (m_fireTimer <= 0)
			{
				m_fireTimer = m_firerate;
				//create weapon
				kiko::Transform transform{m_transform.position, m_transform.rotation, .5f};
			std::unique_ptr<kiko::Laser> laser = std::make_unique<kiko::Laser>(400.0f, transform, m_model);
				m_scene->Add(std::move(laser));
			}
			else
			{
				m_fireTimer -= dt; // subtracting dt from m_fireTimer
			}
		}
	}

	m_transform.position += forward * m_speed * kiko::g_time.GetDeltaTime();
	m_transform.position.x = kiko::Wrap(m_transform.position.x, static_cast<float>(kiko::g_renderer.getWidth()));
	m_transform.position.y = kiko::Wrap(m_transform.position.y, static_cast<float>(kiko::g_renderer.getHeight()));
}

void Enemy::OnCollision(Actor* other)
{
	//dynamic_cast<Player*>(other); //can check for type

	if (other->m_tag == "PlayerLaser")
	{
		m_game->AddPoints(100);
		m_destroyed = true;
		kiko::g_audioSystem.PlayOneShot("explosion");

		////create explosion on death
		//kiko::EmitterData data;
		//data.burst = true;
		//data.burstCount = 100;
		//data.spawnRate = 0;
		//data.angle = 0;
		//data.angleRange = kiko::Pi;
		//data.lifetimeMin = 0.5f;
		//data.lifetimeMax = 1.5f;
		//data.speedMin = 50;
		//data.speedMax = 250;
		//data.damping = 0.5f;
		//data.color = kiko::Color{ 1, 0, 0, 1 };
		//kiko::Transform transform{ m_transform.position, 0, 1 };
		//auto emitter = std::make_unique<kiko::Emitter>(transform, data);
		//emitter->m_lifespan = 1.0f;
		//m_scene->Add(std::move(emitter));
	}
}