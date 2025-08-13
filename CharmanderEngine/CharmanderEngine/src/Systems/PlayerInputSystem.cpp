#include "Systems/PlayerInputSystem.h"
#include "ECS/Transform.h"
#include <SFML/Window/Keyboard.hpp> 

// Main update: decides which control mode to use (Direct or TargetSeek)
void
PlayerInputSystem::update(float dt) {
  if (!cfg.player) return;

  if (cfg.player->getControlMode() == PlayerControlMode::Direct) {
    updateDirect(dt);
  }
  else {
    updateTargetSeek();
  }
}

// Direct control mode: uses WASD or arrow keys for movement
void
PlayerInputSystem::updateDirect(float dt) {
  EngineMathLib::CVector2 a(0.f, 0.f);

  // Forward / up
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
    sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    a.y -= cfg.player->getAcceleration();

  // Backward / down
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
    sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    a.y += cfg.player->getAcceleration();

  // Left
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
    sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    a.x -= cfg.player->getAcceleration();

  // Right
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
    sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    a.x += cfg.player->getAcceleration();

  // Update velocity with acceleration
  auto v = cfg.player->getVelocity();
  v += a * dt;

  // Apply friction if no input
  if (a.x == 0.f && a.y == 0.f) {
    v *= std::max(0.f, 1.f - cfg.player->getFriction() * dt);
  }

  // Limit speed to max speed
  float sp = v.length();
  if (sp > cfg.player->getMaxSpeed()) v = v.normalized() * cfg.player->getMaxSpeed();

  // Integrate position
  auto p = cfg.player->getPosition();
  p += v * dt;

  // Save new velocity and position
  cfg.player->setVelocity(v);
  cfg.player->setPosition(p);
}

// TargetSeek mode: sets target position on left mouse click
void
PlayerInputSystem::updateTargetSeek() {
  if (!cfg.renderWindow) return;
  if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
    auto mp = sf::Mouse::getPosition(*cfg.renderWindow);
    auto world = cfg.renderWindow->mapPixelToCoords(mp);
    cfg.player->setTarget({ world.x, world.y });
  }
}