#pragma once
#include "Framework/Game.h"
#include "Renderer/Text.h"
#include <memory>

class SpaceGame : public kiko::Game
{
public:
	enum class eState
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		PlayerDead,
		GameOver
	};

public:

	// Inherited via Game
	virtual bool Initialize() override;
	virtual bool Shutdown() override;

	virtual void Update(float dt) override;
	virtual void Draw(kiko::Renderer& renderer) override;

	void SetState(eState state) { m_state = state; }

private:
	eState m_state = eState::Title;
	float m_spawnTimer = 0;
	float m_spawnTime = 3.0f; //3 secs spawn enemy

	std::shared_ptr<kiko::Font> m_font;
	std::unique_ptr<kiko::Text> m_scoreText;
	std::unique_ptr<kiko::Text> m_titleText;
};
