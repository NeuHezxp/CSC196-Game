#include "Player.h"

#include "Laser.h"
#include "Framework/Actor.h"
#include "Framework/Scene.h"
#include "Input/InputSystem.h"

#include "Laser.h"
#include "SpaceGame.h"
#include "Framework/Game.h"

void Player::Update(float dt)
{
	Actor::Update(dt);

	//movement
	float rotate = 0;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
	m_transform.rotation += rotate * m_turnRate * kiko::g_time.GetDeltaTime();

	float thrust = 0;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;

	kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * thrust * kiko::g_time.GetDeltaTime();
	///for out of bounds
	m_transform.position.x = kiko::Wrap(m_transform.position.x, (float)kiko::g_renderer.getWidth());
	m_transform.position.y = kiko::Wrap(m_transform.position.y, (float)kiko::g_renderer.getHeight());
	//Actor::Update(dt);

	//fire weapon
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
	{
		//create weapon
		kiko::Transform transform{m_transform.position, m_transform.rotation, 1};
		std::unique_ptr<kiko::Laser> laser = std::make_unique<kiko::Laser>(400.0f, transform, m_model);
		laser->m_tag = "PlayerLaser";
		m_scene->Add(std::move(laser));
	}
}

void Player::OnCollision(Actor* other)
{
	if (other->m_tag == "Enemy") // could be a enemies bullet
	{
		m_health -= 25;
		if (m_health <= 0)
		{
			m_game->setLives(m_game->Getlives() - 1);
			dynamic_cast<SpaceGame*>(m_game)->SetState(SpaceGame::eState::PlayerDead);

			m_destroyed;
		}
	}
}