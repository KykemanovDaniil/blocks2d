#pragma once
#include <SFML/Graphics.hpp>

class Camera {
public:
    Camera() = default;

    // ZOOM
    void setZoom(float zoom) noexcept;
    float getZoom() const noexcept { return m_zoom; }
    float getCurrentZoom() const noexcept { return m_currentZoom; }

    // LERP
    void setLerp(float lerp) noexcept { m_lerp = lerp; }
    float getLerp() const noexcept { return m_lerp; }

    // CENTER
    void setCenter(const sf::Vector2f center) noexcept;

    // SIZE
    void setSize(const sf::Vector2f size) noexcept;

    // VIEW
    void setView(sf::RenderTarget& target) noexcept;

    // BASE SIZE
    sf::Vector2f getBaseSize() const noexcept { return m_baseSize; }

    // OTHER
    void updateLerp(const sf::Vector2f target, float deltaTime) noexcept;

private:
    float m_zoom{1.0f};
    float m_currentZoom{1.0f};
    float m_lerp{7.0f};
    sf::Vector2f m_baseSize{1280, 720};

    sf::View m_view;
};
