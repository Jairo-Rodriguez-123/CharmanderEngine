#pragma once
#include "Prerequisites.h"
#include "Window.h"
#include "CShape.h"
#include "ECS/Actor.h"
#include "ECS/A_Player.h"
#include "EngineGUI.h"
#include <vector>

namespace {
  /*
    *  @brief Calculates the Euclidean distance between two 2D points.
  */
  inline float Distance(const sf::Vector2f& a, const sf::Vector2f& b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
  }
}

/**
* @class BaseApp
* @brief Abstracts the main application logic and lifecycle management.
* The BaseApp class provides a framework for initializing, running, updating,
* rendering, and destroying a graphical application. It manages the main window
* and a primary circle shape, and defines the main loop structure for derived applications.
* Usage:
*   - Call init() to set up resources before running the application.
*   - Use run() to start the main loop, which handles events, updates logic, and renders frames.
*   - Override update() and render() in derived classes to implement custom behavior.
*   - Call destroy() to release resources before exiting.
*
* @see Window
* @see sf::CircleShape
*/
class
  BaseApp {
public:
  /**
  * @brief Default constructor for BaseApp.
  * Initializes a new instance of the BaseApp class.
  */
  BaseApp() = default;

  /**
  * @brief Destructor for BaseApp.
  * Cleans up resources used by the BaseApp instance.
  */
  ~BaseApp();

  /**
  * @brief Runs the main application loop.
  * This function starts the application's main loop, handling events,
  * updating logic, rendering, and managing the application's lifecycle.
  *
  * @return The exit code of the application.
  */
  int
    run();

  /**
  * @brief Initializes the application and its resources.
  * This function sets up all necessary resources and states required
  * for the application to run. It should be called before entering the main loop.
  *
  * @return true if initialization was successful, false otherwise.
  */
  bool
    init();

  /**
  * @brief Updates the application logic.
  * This function processes input, updates game logic, and handles
  * any per-frame updates required by the application.
  */
  void
    update();

  /**
  * @brief Renders the current frame.
  * This function draws all visual elements to the window for the current frame.
  * It should be called once per frame after update().
  */
  void
    render();

  /**
  * @brief Releases all resources and cleans up the application.
  * This function is responsible for freeing resources and performing
  * any necessary cleanup before the application exits.
  */
  void
    destroy();

  /*
    *  @brief Renders the timer on the screen.
  */
  void
    renderTimer();

  /*
    *  @brief Updates the podium standings based on current actor positions.
  */
  void
    updatePodium();

  /*
    *  @brief Renders the laps window for the specified actor.
    *  @param actor Shared pointer to the actor whose laps are displayed.
  */
  void
    renderLapsWindow(const EngineUtilities::TSharedPointer<Actor>& actor);

  /*
    *  @brief Renders the podium window showing the current race standings.
  */
  void
    renderPodiumWindow();

private:

  std::vector<EngineUtilities::TSharedPointer<Actor>> m_actors; ///< List of actors managed by the application.
  /**
  * @brief Gets the pointer to the main application window.
  *
  * @return Pointer to the Window instance managed by the application.
  */
  //Window* m_window;
  EngineUtilities::TSharedPointer<Window> m_windowPtr;

  /**
  * @brief Gets the pointer to the main circle shape used in the application.
  *
  * @return Pointer to the sf::CircleShape instance managed by the application.
  */
  //sf::CircleShape* m_circle;
  //EngineUtilities::TSharedPointer<CShape> m_shapePtr;

  /*
   *  @brief Pointer to the main circle actor used in the application.
  */
  EngineUtilities::TSharedPointer<Actor> m_ACircle;

  /*
    *  @brief List of waypoints as 2D vectors for path following or navigation.
  */
  std::vector<sf::Vector2f> m_waypoints;

  /*
    *  @brief List of shape components representing the path waypoints.
  */
  std::vector<EngineUtilities::TSharedPointer<CShape>> m_path; ///< List of waypoints forming the path.

  /*
    *  @brief Index of the current waypoint in the path.
  */
  int m_currentWaypointIndex = 0; ///< Index of the current waypoint in the path.

  /*
     *  @brief Pointer to the track actor managed by the application.
  */
  EngineUtilities::TSharedPointer<Actor> m_track;

  //EngineUtilities::TSharedPointer<Actor> m_checks;

  /*
    *  @brief Engine GUI manager for handling GUI rendering and updates.
  */
  EngineGUI m_engineGUI;

  /*
     *  @brief Application timer for tracking elapsed time.
  */
  sf::Clock m_appTimer;

  /*
     *  @brief Pointer to the player actor instance.
  */
  EngineUtilities::TSharedPointer<A_Player> m_player;
};