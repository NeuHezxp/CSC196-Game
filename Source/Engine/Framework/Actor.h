#pragma once
#include "Renderer/Model.h"
#include "Core/Core.h"


namespace kiko
{
	class Scene;

	class Actor
	{
	public:
		Actor() = default;
		Actor(const Transform& transform) :
			m_transform{ transform } {}
		Actor(const Transform& transform, std::shared_ptr<Model> model) :
			m_transform{ transform },
			m_model{ model }

		{}
		virtual  void Update(float dt); //dt for delta time /// pure virtual aka: abstract
		virtual  void Draw(Renderer& renderer);

		float GetRadius() { return (m_model) ? m_model->GetRadius() * m_transform.scale : 0; }
		virtual	void OnCollision(Actor* other) {}

		class Scene* m_scene = nullptr;
		class Game* m_game = nullptr;

		friend class Scene;

		kiko::Transform m_transform;
		std::string m_tag;
		float m_lifespan = -1.0f;

	protected:
		bool m_destroyed = false; //flag

		std::shared_ptr<Model> m_model;

	};
}
