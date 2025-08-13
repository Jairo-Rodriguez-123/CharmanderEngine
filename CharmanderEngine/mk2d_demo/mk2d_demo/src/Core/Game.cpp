#include "Game.hpp"
#include "../Core/ResourceManager.hpp"
#include <imgui.h>
#include <cmath>

static sf::Texture& loadCharTex(const std::string& rel){
  return ResourceManager::I().texture(rel);
}

Game::Game(sf::RenderWindow& win):window(win){
  // Cargar pista (usa imagen + path interno simple)
  track.loadMarioCircuit3(); // textura: assets/textures/tracks/mario_circuit_3.png

  // Player: Toad
  {
    auto& tex = loadCharTex("textures/characters/toad.png");
    player.setTexture(tex, 16, 16, 6, {8,8});
    player.kin.pos = track.startPosition();
    player.kin.heading = track.startHeadingRad();
    player.kin.maxSpeed = 320.f;
    player.kin.accel    = 540.f;
  }
  // Bot: Koopa
  {
    auto& tex = loadCharTex("textures/characters/koopa_troopa.png");
    bot.setTexture(tex, 16, 16, 6, {8,8});
    bot.kin.pos = track.startPosition() + sf::Vector2f{36.f,36.f};
    bot.kin.heading = track.startHeadingRad();
    bot.kin.maxSpeed = 310.f;
    bot.kin.accel    = 520.f;
  }
}

void Game::update(float dt){
  timer.update(dt);
  // input jugador
  float th=0.f, st=0.f;
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) th+=1.f;
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) th-=1.f;
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) st-=1.f;
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) st+=1.f;
  player.kin.integrate(dt, th, st);
  player.update(dt);

  // Bot con steering (follow path + arrive)
  auto [bth,bst] = botAI.update(dt, bot.kin.pos, bot.kin.vel, bot.kin.heading, track.path(), player.kin.pos);
  bot.kin.integrate(dt, bth, bst);
  bot.update(dt);
}

void Game::render(sf::RenderWindow& win){
  track.draw(win, showDebug);
  player.draw(win);
  bot.draw(win);
  hud.draw(player.kin.speed, lap, totalLaps, timer.lapTime, timer.bestLap, &showDebug);
}
