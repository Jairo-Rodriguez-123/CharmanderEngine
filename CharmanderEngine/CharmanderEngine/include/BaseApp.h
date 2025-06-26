#pragma once
#include <Prerequisites.h>
#include "Window.h"
#include "CShape.h"

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

private:
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
  EngineUtilities::TSharedPointer<CShape> m_shapePtr;
};