#pragma once
#include "Prerequisites.h"
#include "ECS/Actor.h"

class Window;
//class Actor;

/**
 * @class EngineGUI
 * @brief Handles the graphical user interface (GUI) for the engine, including initialization, rendering, event processing, and GUI styling.
 */
class
	EngineGUI {
public:
	/**
	* @brief Default constructor for EngineGUI.
	*/
	EngineGUI() = default;
	/**
	* @brief Default destructor for EngineGUI.
	*/
	~EngineGUI() = default;

	/**
	* @brief Initializes the GUI system with the provided window.
	* @param window Shared pointer to the main application window.
	*/
	void
		init(const EngineUtilities::TSharedPointer<Window>& window);

	/**
	* @brief Updates the GUI system.
	* @param window Shared pointer to the main application window.
	* @param deltaTime Time elapsed since the last update.
	*/
	void
		update(const EngineUtilities::TSharedPointer<Window>& window, sf::Time deltaTime);

	/**
	* @brief Renders the GUI elements to the provided window.
	* @param window Shared pointer to the main application window.
	*/
	void
		render(const EngineUtilities::TSharedPointer<Window>& window);

	/**
	* @brief Destroys and cleans up the GUI system.
	*/
	void
		destroy();

	/**
	* @brief Processes an SFML event for the GUI system.
	* @param window Reference to the SFML window.
	* @param event The SFML event to process.
	*/
	void
		processEvent(const sf::Window& window, const sf::Event& event);

	/**
	* @brief Sets up a grey color style for the GUI.
	*/
	void
		setupGreyGUIStyle();

	/**
	* @brief Sets up a dark color style for the GUI.
	*/
	void
		setupDarkGUIStyle();

	/**
	* @brief Renders the main menu bar of the GUI.
	*/
	void
		barMenu();

private:
	/**
	* @brief Index of the currently selected actor in the outliner. -1 if none is selected.
	*/
	int selectedActorIndex = -1;
};