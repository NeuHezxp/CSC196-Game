#include <iostream>
#include <thread>
#include <vector>
#include "Core/Core.h"
#include <Renderer/Renderer.h>
#include <Renderer/Model.h>
#include "Input/InputSystem.h"

using namespace std;

class Star
{
public:
	Star(const kiko::Vector2& pos, const kiko::Vector2& vel) :
		m_pos(pos),
		m_vel(vel)
	{}

	void Update()
	{
		m_pos += m_vel * kiko::g_time.GetDeltaTime();

	}

	void Draw(kiko::Renderer& renderer)
	{
		renderer.DrawPoint(m_pos.x, m_pos.y);
	}

public:
	kiko::vec2 m_pos;
	kiko::vec2 m_vel;
};
//leaving when adding in vector2.h before stream op for the number in {}
int main(int argc, char* argv[])
{
	//constexpr	float a = kiko::DegreesToRadians(180.0f);

	kiko::seedRandom((unsigned int)time(nullptr));
	kiko::setFilePath("assets");
	cout << kiko::getFilePath() << endl;

	kiko::Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("CSC196", 800, 600);

	kiko::InputSystem inputSystem;
	inputSystem.Initialize();

	kiko::Model model;
	model.Load("ship.txt");

	std::vector<Star> stars;

	kiko::Transform transform{{400, 300}, 0, 3};

	kiko::vec2 position{ 400, 300 };
	float speed = 200;
	float turnRate = kiko::DegreesToRadians(180);

	bool quit = false;
	while (!quit)
	{
		kiko::g_time.Tick();
		inputSystem.Update();

		if (inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE)) // using the escape key to break out of loop and exit program
		{
			quit = true;
		}

		float rotate = 0;
		if (inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
		if (inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
		transform.rotation += rotate * turnRate * kiko::g_time.GetDeltaTime();

		float thrust = 0;
		if (inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;

		kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);
		transform.position += forward * speed * thrust*  kiko::g_time.GetDeltaTime();
		transform.position.x = kiko::Wrap(transform.position.x, renderer.getWidth());
		transform.position.y = kiko::Wrap(transform.position.y, renderer.getHeight());





		///controlls for movement
		//kiko::vec2 direction;
		//if (inputSystem.GetKeyDown(SDL_SCANCODE_W)) direction.y = -1;
		//if (inputSystem.GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
		//if (inputSystem.GetKeyDown(SDL_SCANCODE_S)) direction.y = 1;
		//if (inputSystem.GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;

//		position += direction * speed * kiko::g_time.GetDeltaTime();

		// Check if the left mouse button is pressed
		if (inputSystem.GetMouseButtonDown(0))
		{
			std::cout << "Mouse pressed!!" << std::endl;
		}

		// Get the mouse position
		kiko::Vector2 mousePos = inputSystem.GetMousePosition();	
		std::cout << "Mouse position: (" << mousePos.x << ", " << mousePos.y << ")" << std::endl;


		// draw
		renderer.setColor(0, 0, 0, 0); // Sets color to black
		renderer.BeginFrame(); // Clears the screen, allows for less static

		renderer.setColor(kiko::random(256), kiko::random(256), kiko::random(256), 255);
		renderer.setColor(255, 255, 255, 255);
		// Update and draw stars
		for (auto& star : stars)
		{
			star.Update();

			if (star.m_pos.x >= renderer.getWidth())
				star.m_pos.x = 0;
			if (star.m_pos.y >= renderer.getHeight())
				star.m_pos.y = 0;

			
			renderer.DrawPoint(star.m_pos.x, star.m_pos.y);
		}

		// Draw model at the current position
		model.Draw(renderer, transform.position, transform.rotation , transform.scale);
		renderer.EndFrame();
	}

	return 0;
}

