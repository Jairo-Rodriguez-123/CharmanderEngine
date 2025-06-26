#pragma once
#include "Prerequisites.h"

/**
* @class Window
* @brief Encapsulates an SFML RenderWindow for rendering and window management.
* The Window class provides a high-level interface for creating and managing a graphical window
* using the SFML library. It supports window creation, event handling, drawing operations, and
* resource management. The class is designed to be used as the main rendering target in a graphical
* application, handling all window-related operations internally.
*
* Example usage:
* @code
* Window window(800, 600, "My Application");
* while (window.isOpen()) {
*   window.handleEvents();
*   window.clear();
*   // Draw your objects here
*   window.display();
* }
* @endcode
*/
class
  Window {
public:
  /**
  * @brief Default constructor for the Window class.
  * Constructs a Window object without initializing the underlying window.
  * The window must be initialized using the parameterized constructor before use.
  */
  Window() = default;

  /**
  * @brief Constructs a Window with the specified dimensions and title.
  * Initializes the window with the given width, height, and title.
  * Allocates the underlying SFML RenderWindow and prepares it for rendering.
  *
  * @param width  The width of the window in pixels.
  * @param height The height of the window in pixels.
  * @param title  The title of the window displayed in the title bar.
  */
  Window(int width, int height, const std::string& title);

  /**
  * @brief Destructor for the Window class.
  * Releases all resources associated with the window and destroys the underlying SFML RenderWindow.
  */
  ~Window();

  /**
  * @brief Handles window events such as input and window close requests.
  * This function processes all pending events for the window, such as keyboard and mouse input,
  * window resizing, and close events. It should be called once per frame in the main loop.
  */
  void
    handleEvents();

  /**
  * @brief Checks if the window is currently open.
  *
  * @return true if the window is open; false if it has been closed.
  */
  bool
    isOpen() const;

  /**
  * @brief Clears the window with the specified color.
  * This function fills the entire window with the given color, preparing it for new drawing operations.
  * It should be called at the beginning of each frame before any draw calls.
  *
  * @param color The color to use when clearing the window (default is opaque black).
  */
  void
    clear(const sf::Color& color = sf::Color(0, 0, 0, 255));

  /**
  * @brief Draws a drawable object to the window.
  * This function renders the specified drawable object (such as shapes, sprites, or text)
  * onto the window using the provided render states. The draw call is queued and will be
  * displayed after calling the display() method.
  *
  * @param drawable The drawable object to render (e.g., sf::Sprite, sf::Shape, sf::Text).
  * @param states   The render states to use for drawing (default is sf::RenderStates::Default).
  */
  void
    draw(const sf::Drawable& drawable,
      const sf::RenderStates& states = sf::RenderStates::Default);

  /**
  * @brief Displays the contents of the window on the screen.
  * This function swaps the back buffer with the front buffer, making everything
  * that has been drawn since the last call to display() visible on the window.
  * It should be called once per frame, after all draw calls.
  */
  void
    display();

  /**
  * @brief Destroys the window and releases associated resources.
  * This function closes the window and frees any resources allocated for it.
  * After calling destroy(), the window is no longer usable until re-initialized.
  */
  void
    destroy();

private:
  /**
  * @brief Pointer to the underlying SFML RenderWindow.
  * This member holds a pointer to the SFML sf::RenderWindow instance used for rendering
  * and window management. It is managed internally by the Window class and should not
  * be accessed directly by users of the class.
  */
  //sf::RenderWindow* m_window;
  EngineUtilities::TUniquePtr<sf::RenderWindow> m_windowPtr;
  sf::View m_view;
};