#pragma once

#include "Prerequisites.h"
#include "Window.h"
#include "CShape.h"
#include "ECS/Actor.h"
#include <vector>
#include <string>
#include "EngineGUI.h"
#include "ECS/A_Racer.h"
#include "ECS/A_Player.h" /

/* Systems */
#include "Systems/PlayerInputSystems.h"
#include "Systems/SteerringSystem.h"
#include "Systems/WaypointFollowSystem.h"
#include "Systems/RaceSystem.h"
#include "Components/RaceCountdown.h"

/**
 * @class BaseApp
 * @brief Main application class for managing the game loop and state.
 *
 * @details
 * Handles initialization, updating, and rendering of the main window,
 * actors, systems, GUI panels, and race logic. Manages race states such
 * as countdown, start, and finish, as well as menu navigation.
 */
class
  BaseApp {

public:
  /** Default constructor. */
  BaseApp() = default;

  /** Destructor. Cleans up resources. */
  ~BaseApp();

  /**
   * @brief Runs the main application loop.
   * @return Exit code from the application.
   */
  int
    run();

  /**
   * @brief Initializes the application and resources.
   * @return True if initialization succeeded.
   */
  bool
    init();

  /** @brief Updates game logic and systems each frame. */
  void
    update();

  /** @brief Renders game scene and UI. */
  void
    render();

  /** @brief Destroys and cleans up resources. */
  void
    destroy();

private:
  /* === Window & Actors === */
  /** Main application window. */
  EngineUtilities::TSharedPointer<Window>   m_windowPtr;

  /** Track and player visual actors. */
  EngineUtilities::TSharedPointer<Actor>    m_ACircle;
  EngineUtilities::TSharedPointer<Actor>    m_ATrack;

  /** NPC racer and player-controlled racer. */
  EngineUtilities::TSharedPointer<A_Racer>  m_racerNPC;
  EngineUtilities::TSharedPointer<A_Player> m_player;

  /** List of NPC racers and all actors. */
  std::vector<EngineUtilities::TSharedPointer<A_Racer>> m_npcs;
  std::vector<EngineUtilities::TSharedPointer<Actor>>   actorsVector;

  /** GUI management instance. */
  EngineGUI m_engineGUI;

  /* === Waypoints === */
  /** List of track waypoints for AI navigation. */
  std::vector<sf::Vector2f> m_waypoints;

  /* === Systems === */
  /** Player input, steering, waypoint following, and race systems. */
  EngineUtilities::TUniquePtr<PlayerInputSystem>    m_playerInputSystem;
  EngineUtilities::TUniquePtr<SteeringSystem>       m_steeringSystem;
  EngineUtilities::TUniquePtr<WaypointFollowSystem> m_waypointFollowSystem;
  EngineUtilities::TUniquePtr<RaceSystem>           m_raceSystem;

  /* === Countdown & Race state === */
  /** Race countdown timer (default 3 seconds). */
  RaceCountdown m_countdown{ 3.f };

  /** Flags for race state. */
  bool m_raceArmed = false;   ///< Countdown running
  bool m_raceLive = false;    ///< GO! reached
  bool m_raceFinished = false;///< Race completed
  int  m_finalPlace = -1;     ///< Player finishing place
  int  m_lapsToWin = 3;       ///< Required laps to win
  bool m_npcFinished = false; ///< NPC has finished

  /* === Speeds === */
  /** Shared max speed for all racers and NPC speed scaling. */
  float m_sharedMaxSpeed = 260.f;
  float m_npcSpeedFactor = 0.95f;

  /* === Simple Main Menu === */
  /** Available menu pages. */
  enum class MenuPage { Main, PlayerColor, Track, Settings };

  /** Menu state variables. */
  bool     m_inMenu = true;     ///< While true, race updates are paused
  MenuPage m_menuPage = MenuPage::Main;
  int      m_colorIdx = 0;      ///< Color selection index (0..3)
  int      m_trackIdx = 0;      ///< Selected track index
  sf::Color m_colorOptions[4] = {
    sf::Color::Black,
    sf::Color::Green,
    sf::Color::Blue,
    sf::Color::Yellow
  };

  /* === HUD helpers (layout only, no game state changes) === */

  /**
   * @brief Returns display name for an index from RaceSystem standings.
   * @param idx Index in standings (0 = player, 1..N = NPCs).
   * @return C-string with the actor's display name.
   */
  const char*
    nameFromStandingsIndex(int idx) const;

  /**
   * @brief Draws the vertical standings cards on the left (rank + name).
   * @param order Vector of indices sorted by progress (0 = player).
   * @param slots Max number of rows/cards to draw.
   */
  void
    drawStandingsPortraits(const std::vector<int>& order, int slots) const;

  /**
   * @brief Draws the big position badge on the top-left (e.g., "1st").
   * @param place 1-based player position in current standings.
   */
  void
    drawPositionBadge(int place) const;

  /**
   * @brief Draws the lap banner on the top-center (e.g., "LAP 2/3").
   * @param lapHUD Visual lap number (1-based).
   * @param lapsToWin Total laps to finish.
   */
  void
    drawLapTopCenter(int lapHUD, int lapsToWin) const;

  /**
   * @brief Draws the time box top-right (TIME, BEST, CURRENT).
   * @param currentLap Current lap time in seconds.
   * @param bestLap Best lap time in seconds (-1 if no best yet).
   */
  void
    drawTimeBoxTopRight(float currentLap, float bestLap) const;

  /**
   * @brief Formats a time as "MM:SS.CC" or "--:--.--" if negative.
   */
  static std::string
    formatTime(float sec);

  /**
   * @brief Converts numeric place to an English ordinal string ("1st", ...).
   */
  static std::string
    ordinalString(int place);

  /* === Helpers === */
  /** @brief Resets race state and positions. */
  void
    resetRace();

  /** @brief Draws the main menu using ImGui. */
  void
    drawMainMenu();

  /** @brief Applies player color based on m_colorIdx. */
  void
    applyPlayerColor();

  /** @brief Starts the countdown sequence (3..2..1..GO). */
  void
    armAndStartCountdown();
};