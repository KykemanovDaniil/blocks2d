#include <SFML/Graphics.hpp>
#include "player/Player.hpp"
#include "math/random/Random.hpp"

void Player::setPosition(const sf::Vector2f& newPosition) {
    position = newPosition;
}

void Player::movementPlayer() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        position.y -= speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
        position.y += speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        position.x -= speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        position.x += speed;
    }
}

void Player::drawPlayer(sf::RenderWindow& window) {
    sf::RectangleShape playerTexture(sf::Vector2f{playerW, playerH});

    playerTexture.setOrigin({playerW / 2.0f, playerH / 2.0f});

    playerTexture.setFillColor(sf::Color::Red);

    playerTexture.setPosition(position);

    window.draw(playerTexture);
}