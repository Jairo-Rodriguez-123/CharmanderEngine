#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../Core/Timer.hpp"
#include "../UI/HUD.hpp"
#include "../Physics/Kinematics.hpp"
#include "../AI/BotController.hpp"
#include "../Track/Track.hpp"
#include "../Entities/Kart.hpp"

class Game {
public:
  Game(sf::RenderWindow& win);
  void update(float dt);
  void render(sf::RenderWindow& win);
private:
  sf::RenderWindow& window;
  Timer timer;
  HUD hud;
  int lap=0, totalLaps=3;
  bool showDebug=false;
  // pista
  Track track;
  // jugador y bot
  Kart player, bot;
  BotController botAI;
};
