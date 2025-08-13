#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../Core/ResourceManager.hpp"

struct Checkpoint { sf::Vector2f p; float r; };

class Track {
public:
  bool loadMarioCircuit3();
  void draw(sf::RenderWindow& win, bool debug=false);
  const std::vector<sf::Vector2f>& path() const { return m_path; }
  sf::Vector2f startPosition() const { return {80.f,640.f}; }
  float startHeadingRad() const { return 0.f; } // hacia la derecha
private:
  sf::Sprite sprite;
  std::vector<sf::Vector2f> m_path;
  std::vector<Checkpoint> m_checkpoints;
};
