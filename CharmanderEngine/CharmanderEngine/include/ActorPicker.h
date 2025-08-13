#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "ECS/Actor.h"
#include "CShape.h"

/**
 * @class ActorPicker
 * @brief Utility class to select actors in world space using the mouse.
 *
 * @details
 * Provides a static function to detect which actor (if any) is located
 * under the current mouse position, by checking bounding boxes of shapes
 * attached to the actors.
 */
class
  ActorPicker {

public:
  /**
   * @brief Pick an actor under the mouse position.
   *
   * @details
   * Translates mouse screen coordinates into world coordinates using the
   * provided render window. Then iterates through all given actors,
   * retrieving their CShape component, and checking if the shape's global
   * bounds contain the mouse point.
   *
   * @param windowPtr Pointer to the SFML RenderWindow.
   * @param actors List of shared pointers to actors.
   * @return Index of the first actor under the mouse, or -1 if none found.
   */
  static int
    pickActorUnderMouse(
      sf::RenderWindow* windowPtr,
      const std::vector<EngineUtilities::TSharedPointer<Actor>>& actors
    ) {
    // Get mouse position in world coordinates
    sf::Vector2i mousePos = sf::Mouse::getPosition(*windowPtr);
    sf::Vector2f mouseWorld = windowPtr->mapPixelToCoords(mousePos);

    // Iterate through actors and check if mouse is inside their shape bounds
    for (int i = 0; i < static_cast<int>(actors.size()); ++i) {
      auto shape = actors[i]->getComponent<CShape>();
      if (shape) {
        auto shapePtr = shape->getShapePtr();
        if (shapePtr &&
          shapePtr->getGlobalBounds().contains(mouseWorld)) {
          return i;
        }
      }
    }
    return -1;
  }
};