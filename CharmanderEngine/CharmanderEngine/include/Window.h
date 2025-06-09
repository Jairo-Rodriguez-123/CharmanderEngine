#pragma once
#include "Prerequisites.h"
/**
* @class Window
* @brief Represents a graphical window for rendering and event handling.
*
* The Window class provides an interface for creating and managing a graphical
* window using the SFML library. It supports rendering, event handling, and
* resource management.
*/
class
Window {
public:
  /**
  * @brief Default constructor for the Window class.
  * 
  * This constructor initializes a Window object with default values.
  */
  Window() = default;

  /**
  * @brief Parameterized constructor for the Window class.
  * 
  * This constructor creates a Window object with the specified width, height, and title.
  * 
  * @param width The width of the window in pixels.
  * @param height The height of the window in pixels.
  * @param title The title of the window as a string.
  */
  Window(int width, int height, const std::string& title);

  /**
  * @brief Destructor for the Window class.
  * 
  * This destructor ensures that all resources associated with the Window object
  * are properly released when the object is destroyed.
  */
  ~Window();

  /**
  * @brief Handles all the events for the window.
  * 
  * This method processes input events such as keyboard, mouse, and window events.
  * It ensures that the application responds appropriately to user interactions
  * and system messages.
  */
  void
  handleEvents();

  /**
  * @brief Checks if the window is currently open.
  * 
  * This method returns a boolean value indicating whether the window
  * is still open and operational. It is useful for determining if the
  * application should continue running or terminate.
  * 
  * @return true if the window is open, false otherwise.
  */
  bool 
  isOpen() const; 

  /**
  * @brief Clears the window with a specified color.
  * 
  * This method fills the entire window with the given color, effectively
  * resetting its contents. It is typically called at the beginning of
  * each frame before drawing new objects.
  * 
  * @param color The color to clear the window with. Defaults to black.
  */
  void
  clear(const sf::Color& color = sf::Color(0, 0, 0, 255));

  /**
  * @brief Draws a drawable object onto the window.
  * 
  * This method renders a drawable object, such as a sprite or shape,
  * onto the window. It can also accept custom render states for advanced
  * rendering configurations.
  * 
  * @param drawable The object to be drawn.
  * @param states Optional render states to apply during drawing. Defaults to sf::RenderStates::Default.
  */
  void 
  draw(const sf:: Drawable& drawable, 
      const sf:: RenderStates& states = sf::RenderStates::Default);

  /**
  * @brief Displays the contents of the window.
  * 
  * This method swaps the back buffer to the front, making all the
  * previously drawn objects visible on the screen. It is typically
  * called at the end of each frame.
  */
  void
  display();

  /**
  * @brief Destroys the window and releases its resources.
  * 
  * This method closes the window and cleans up any associated resources.
  * It should be called when the window is no longer needed to ensure
  * proper resource management.
  */
  void
  destroy();
private:
  /**
  * @brief Pointer to the SFML RenderWindow instance.
  * 
  * This member variable holds a pointer to the SFML RenderWindow object,
  * which represents the main window where all rendering operations occur.
  * It is used to manage the window's lifecycle and rendering context.
  */
  sf::RenderWindow* m_window;

  /**
  * @brief The current view of the window.
  * 
  * This member variable stores the SFML View object, which defines the
  * visible region of the window. It can be used to control the camera
  * position, zoom level, and other view-related properties.
  */
  sf::View m_view;

	

};