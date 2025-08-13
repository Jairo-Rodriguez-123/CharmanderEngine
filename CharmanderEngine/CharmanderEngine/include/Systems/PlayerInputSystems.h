#pragma once
#include "Prerequisites.h"
#include "ECS/A_Player.h"

/**
 * @struct PlayerInputConfig
 * @brief Holds configuration and references for player input handling.
 *
 * @details
 * Provides access to the controlled player actor and render window. This
 * config is passed to PlayerInputSystem for per-frame input processing.
 */
struct
  PlayerInputConfig {
  /** Pointer to the player actor being controlled. */
  EngineUtilities::TSharedPointer<A_Player> player;

  /** Pointer to the SFML render window used for input events. */
  sf::RenderWindow* renderWindow = nullptr;
};

/**
 * @class PlayerInputSystem
 * @brief Processes player input and updates the controlled player.
 *
 * @details
 * Depending on the control mode (Direct or TargetSeek), interprets input
 * and updates player position, velocity, or target. Uses the config passed
 * at construction to know which player to control and where to read input.
 */
class
  PlayerInputSystem {

public:
  /**
   * @brief Construct the input system with a configuration.
   * @param cfg Player and window references.
   */
  PlayerInputSystem(const PlayerInputConfig& cfg) : cfg(cfg) {}

  /**
   * @brief Virtual destructor (default).
   */
  ~PlayerInputSystem() = default;

  /**
   * @brief Per-frame input update.
   * @param dt Seconds elapsed since the last frame.
   */
  void
    update(float dt);

private:
  /** Configuration holding references for input processing. */
  PlayerInputConfig cfg;

  /**
   * @brief Process input for Direct control mode (WASD).
   * @param dt Seconds elapsed since the last frame.
   */
  void
    updateDirect(float dt);

  /**
   * @brief Process input for TargetSeek mode (mouse click to move).
   */
  void
    updateTargetSeek();
};