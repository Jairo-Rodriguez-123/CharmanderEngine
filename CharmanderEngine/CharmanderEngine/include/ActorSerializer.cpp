#include "ActorSerializer.h"
#include <fstream>

bool
ActorSerializer::saveActorsToFile(const std::string& filename, const std::vector<EngineUtilities::TSharedPointer<Actor>>& actors) {
  std::ofstream file(filename);
  if (!file.is_open()) return false;
  for (auto& actor : actors) {
    file << actor->getName() << ","; // Nombre
    auto transform = actor->getComponent<Transform>();
    if (transform) {
      auto pos = transform->getPosition();
      auto scale = transform->getScale();
      file << pos.x << "," << pos.y << "," << scale.x << "," << scale.y << "\n";
    }
  }
  file.close();
  return true;
}

bool
ActorSerializer::loadActorsFromFile(const std::string& filename, std::vector<EngineUtilities::TSharedPointer<Actor>>& actors) {
  std::ifstream file(filename);
  if (!file.is_open()) return false;
  actors.clear();
  std::string line;
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string name;
    float px, py, sx, sy;
    if (std::getline(ss, name, ',') &&
      (ss >> px) && ss.ignore(1) &&
      (ss >> py) && ss.ignore(1) &&
      (ss >> sx) && ss.ignore(1) &&
      (ss >> sy)) {
      auto actor = EngineUtilities::MakeShared<Actor>(name);
      actor->getComponent<Transform>()->setPosition(sf::Vector2f(px, py));
      actor->getComponent<Transform>()->setScale(sf::Vector2f(sx, sy));
      actors.push_back(actor);
    }
  }
  file.close();
  return true;
}