#include <iostream>
#include <SFML/Graphics.hpp>
#include <print>
#include <optional>

#include "src/core/Config.hpp"

#include "src/player/Player.hpp"
#include "src/camera/Camera.hpp"
#include "src/worldManager/TileData/TileData.hpp"
#include "src/worldManager/WorldManager.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({Config::windowW, Config::windowH}), "Blocks2d");
    window.setFramerateLimit(Config::windowFps);

    initBlockData();
    initWallData();

    sf::Clock clock;

    WorldManager worldManager;
    worldManager.loadAtlasTexture("res/textures/blockAtlas.png");
    worldManager.createWorld(500);

    Player player;
    Camera camera;
    camera.setZoom(1.0f);
        
    float fpsTimer = 0.0f;
    int frameCount = 0;
    int currentFps = 0;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        fpsTimer += deltaTime;
        frameCount++;

        if (fpsTimer >= 1.0f) {
            currentFps = frameCount;
            frameCount = 0;
            fpsTimer = 0.0f;
            std::println("FPS: {}", currentFps);
        }

        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* keyPressedEvent = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressedEvent->code == sf::Keyboard::Key::F8) {
                    window.close();
                }
            }
        }

        player.update(deltaTime);

        float zoomSpeed = 3.5f; 

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::O)) {
            camera.setZoom(camera.getZoom() - (zoomSpeed * camera.getZoom() * deltaTime));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::I)) {
            camera.setZoom(camera.getZoom() + (zoomSpeed * camera.getZoom() * deltaTime));
        }

        camera.updateLerp(player.getPosition(), deltaTime);

        // RENDER

        window.clear(sf::Color{82, 176, 255, 255});

        camera.setView(window);

        worldManager.draw(window, player, camera);

        player.draw(window);

        window.display();
    }

    return 0;
}