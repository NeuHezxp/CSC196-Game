#include "Text.h"
#include "Font.h"
#include <SDL2-2.28.0/include/SDL_ttf.h>
namespace kiko
{
	Text::~Text()
	{
		if (m_texture) SDL_DestroyTexture(m_texture);
	}
	void Text::Create(Renderer& renderer, const std::string& text, const Color& color)
	{
		if (m_texture) SDL_DestroyTexture(m_texture);
		SDL_Color c{ Color::toInt(color.r), Color::toInt(color.g), Color::toInt(color.b), Color::toInt(color.a) };
		SDL_Surface* surface = TTF_RenderText_Solid(m_font->m_ttfFont, text.c_str(), c);
		m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
		SDL_FreeSurface(surface);
	}
	void Text::Draw(Renderer& renderer, int x, int y)
	{
		int width, height;
		SDL_QueryTexture(m_texture, nullptr, nullptr, &width, &height);
		SDL_Rect rect{ x, y, width, height };
		SDL_RenderCopy(renderer.m_renderer, m_texture, NULL, &rect);
	}
}