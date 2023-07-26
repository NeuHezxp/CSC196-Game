#include "SpaceGame.h"
#include "Framework/Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "Audio/AudioSystem.h"
#include "Framework/Emitter.h"
#include "Input/InputSystem.h"
#include "Renderer/ModelManager.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"
#include "Renderer/ModelManager.h"

bool SpaceGame::Initialize()
{
	// create font / text objects
	m_font = std::make_shared<kiko::Font>("arcadeclassic.ttf", 24);
	m_scoreText = std::make_unique<kiko::Text>(m_font);
	m_scoreText->Create(kiko::g_renderer, "Score 0000", kiko::Color{ 1, 1, 1, 1 });

	m_titleText = std::make_unique<kiko::Text>(m_font);
	m_titleText->Create(kiko::g_renderer, "asteroid", kiko::Color{ 1, 1, 1, 1 });

	//loading audio
	kiko::g_audioSystem.AddAudio("hit", "explosion.wav");
	//load background music
	kiko::g_audioSystem.AddAudio("background", "");

	//
	m_scene = std::make_unique<kiko::Scene>();
	kiko::Scene scene;

	return true;
}

bool SpaceGame::Shutdown()
{
	return false;
}

void SpaceGame::Update(float dt)
{
	switch (m_state)
	{
	case SpaceGame::eState::Title:
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::StartGame;
		}
		break;
	case SpaceGame::eState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		break;

	case SpaceGame::eState::StartLevel:
	{
		m_scene->RemoveAll();
		std::unique_ptr<Player> player = std::make_unique<Player>(200.0f, kiko::Pi, kiko::Transform{ {400, 300}, 0, 6 }, kiko::g_manager.Get("ship.txt"));
		player->m_tag = "Player";
		player->m_game = this;
		m_scene->Add(std::move(player));
	}
	m_state = eState::Game;
	break;

	case SpaceGame::eState::Game:
		m_spawnTimer += dt;

		///if pressing r restart game.
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_R))
		{
			

		}

		if (m_spawnTimer >= m_spawnTime)
		{
			// spawn timer back to 0
			m_spawnTimer = 0;
			// creates enemy after the timer hits 0
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(kiko::randomf(75.0f, 150.0f), kiko::Pi, kiko::Transform{ {kiko::random(kiko::g_renderer.getWidth()), kiko::random(kiko::g_renderer.getHeight())}, kiko::randomf(kiko::TwoPi), 4 }, kiko::g_manager.Get("ship.txt"));
			enemy->m_tag = "Enemy";
			enemy->m_game = this;
			m_scene->Add(std::move(enemy));

			/// pressed mouse spawns particle
			if (kiko::g_inputSystem.GetMouseButtonDown(0))
			{
				/// emitter stuff
				kiko::EmitterData data;
				data.burst = true;
				data.burstCount = 100;
				data.spawnRate = 200;
				data.angle = 0;
				data.angleRange = kiko::Pi;
				data.lifetimeMin = 0.5f;
				data.lifetimeMax = 1.5f; // Corrected the assignment here
				data.speedMin = 50;
				data.speedMax = 250;
				data.damping = 0.5f;
				data.color = kiko::Color{ 1, 0, 0, 1 };
				kiko::Transform transform{ {kiko::g_inputSystem.GetMousePosition() }, 0, 1 };
				auto emitter = std::make_unique<kiko::Emitter>(transform, data);
				emitter->m_lifespan = 1.0f;
				m_scene->Add(std::move(emitter));
			}
		}
		break;
	case SpaceGame::eState::PlayerDead:
		break;
	case SpaceGame::eState::GameOver:
		break;
	default:
		break;
	}
	m_scoreText->Create(kiko::g_renderer, std::to_string(m_score), { 1, 1, 1, 1 });
	m_scene->Update(dt);
}

void SpaceGame::Draw(kiko::Renderer& renderer)
{
	if (m_state == eState::Title)
	{
		m_titleText->Draw(renderer, 400, 300);
	}
	m_scoreText->Draw(renderer, 40, 40);
	m_scene->Draw(renderer);
	kiko::g_particleSystem.Draw(renderer);
}