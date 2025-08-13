#pragma once
#include "Prerequisites.h"

class
	EngineGUI;
/**
 * @class Window
 * @brief Manages an SFML window instance for rendering and input handling.
 *
 * This class encapsulates the SFML RenderWindow, handling its creation,
 * event processing, drawing operations, and cleanup.
 */
class
	Window {
public:

	/**
	 * @brief Default constructor.
	 */
	Window() = default;

	/**
	 * @brief Constructs a window with given width, height, and title.
	 * @param width Width of the window in pixels.
	 * @param height Height of the window in pixels.
	 * @param title Title of the window.
	 */
	Window(int width, int height, const std::string& title);

	/**
	 * @brief Destructor to clean up resources.
	 */
	~Window();

	/**
	 * @brief Processes window events such as input or close requests.
	 *
	 * This function should be called every frame to ensure window responsiveness.
	 */
	void
		handleEvents(EngineGUI& engineGUI);

	/**
	 * @brief Checks if the window is currently open.
	 * @return True if the window is open, false otherwise.
	 */
	bool
		isOpen() const;

	/**
	 * @brief Clears the window with the specified color.
	 * @param color The color to clear the window with (default is opaque black).
	 */
	void
		clear(const sf::Color& color = sf::Color(0, 0, 0, 255));

	/**
	 * @brief Draws a drawable object to the window.
	 * @param drawable The drawable object to render.
	 * @param states Render states to apply (default is sf::RenderStates::Default).
	 */
	void
		draw(const sf::Drawable& drawable,
			const sf::RenderStates& states = sf::RenderStates::Default);

	/**
	 * @brief Displays the rendered frame on the screen.
	 *
	 * This should be called after all draw calls to present the final image.
	 */
	void
		display();

	void
		update();

	void
		render();

	/**
	 * @brief Destroys the window and releases resources.
	 *
	 * Safe to call manually or will be called in the destructor.
	 */
	void
		destroy();

private:
	sf::View
		m_view; ///< Current view used for rendering.
public:
	sf::Time deltaTime; ///< Time elapsed since the last frame.
	sf::Clock
		m_clock; ///< Clock to measure time between frames.
	EngineUtilities::TUniquePtr
		<sf::RenderWindow> m_windowPtr; ///< Unique pointer to the SFML RenderWindow.
};