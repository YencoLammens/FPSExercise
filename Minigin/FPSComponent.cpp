#include "FPSComponent.h"
#include "Renderer.h"
#include <SDL_ttf.h>
#include <stdexcept>

dae::FPSComponent::FPSComponent(std::shared_ptr<Font> font)
	: m_font(font), m_frameCount(0), m_elapsedTime(0), m_fps(0), m_needsUpdate(true)
{
	m_transform.SetPosition(10, 10, 0);
	m_lastTime = std::chrono::high_resolution_clock::now();
}

void dae::FPSComponent::Update()
{
    m_frameCount++;
	auto currentTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> deltaTime = currentTime - m_lastTime;

    if (deltaTime.count() >= 0.1f)
    {
        m_fps = m_frameCount / deltaTime.count();
        m_frameCount = 0;
        m_lastTime = currentTime;
        m_needsUpdate = true;
    }

    if (m_needsUpdate)
    {
        UpdateFPS();
        m_needsUpdate = false;
    }
}

void dae::FPSComponent::FixedUpdate()
{
   
}

void dae::FPSComponent::Render() const
{
    if (m_textTexture)
    {
        const auto pos = m_transform.GetPosition();
        Renderer::GetInstance().RenderTexture(*m_textTexture, pos.x , pos.y);
    }
}

dae::BaseComponent::Type dae::FPSComponent::GetType() const
{
    return BaseComponent::Type::FPS;
}

void dae::FPSComponent::UpdateFPS()
{
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(1) << m_fps;
    m_text = stream.str() + " FPS";

    const auto surface = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), SDL_Color{ 255, 255, 255 });
    if (surface == nullptr)
    {
        throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
    }
    auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surface);
    if (texture == nullptr)
    {
        SDL_FreeSurface(surface);
        throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
    }
    SDL_FreeSurface(surface);
    m_textTexture = std::make_shared<Texture2D>(texture);
}
