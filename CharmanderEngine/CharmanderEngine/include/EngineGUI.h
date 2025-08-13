#pragma once
#include "Prerequisites.h"
#include <vector>
class
  Window;

class
  Actor;

/**
 * @class EngineGUI
 * @brief Handles ImGui panels, menu, selection, and editor UI flow.
 *
 * @details
 * Provides lifecycle hooks (init/update/render/destroy), event handling,
 * menu bar, hierarchy and inspector panels, a simple console, outline draw
 * for selected actors, and a file manager for save/load operations.
 */
class
  EngineGUI {

public:
  /** @brief Default constructor. */
  EngineGUI() = default;

  /** @brief Default destructor. */
  ~EngineGUI() = default;

  /**
   * @brief Initialize GUI bindings and style for the given window.
   * @param window Shared pointer to the engine window.
   */
  void
    init(const EngineUtilities::TSharedPointer<Window>& window);

  /**
   * @brief Advance GUI state and panels.
   * @param window Shared pointer to the engine window.
   * @param deltaTime Frame delta time from the main loop.
   */
  void
    update(const EngineUtilities::TSharedPointer<Window>& window,
      sf::Time deltaTime);

  /**
   * @brief Render all GUI panels and overlays.
   * @param window Shared pointer to the engine window.
   */
  void
    render(const EngineUtilities::TSharedPointer<Window>& window);

  /**
   * @brief Release GUI resources and shutdown ImGui bindings.
   */
  void
    destroy();

  /**
   * @brief Handle a single SFML window event for ImGui input.
   * @param window Reference to SFML window.
   * @param event  SFML event to process.
   */
  void
    processEvent(const sf::Window& window, const sf::Event& event);

  /**
   * @brief Apply the VektorCore custom ImGui style.
   */
  void
    SetupVektorCoreGUIStyle();

  /**
   * @brief Draw the main menu bar (File, View, Tools, etc.).
   */
  void
    menuBar();

  /**
   * @brief Show the hierarchy panel with all actors in the scene.
   * @param actors Vector of shared pointers to actors.
   */
  void
    hierarchy(const std::vector<EngineUtilities::TSharedPointer<Actor>>& actors);

  /**
   * @brief Show the inspector panel for the selected actor.
   * @param actors Vector of shared pointers to actors.
   */
  void
    inspector(const std::vector<EngineUtilities::TSharedPointer<Actor>>& actors);

  /**
   * @brief Render a simple console panel for logs and commands.
   */
  void
    console();

  /**
   * @brief Draw an outline around the selected actor in the scene view.
   * @param renderWindow Pointer to the SFML render window.
   * @param actors Vector of shared pointers to actors.
   */
  void
    drawSelectedOutline(sf::RenderWindow* renderWindow,
      const std::vector<EngineUtilities::TSharedPointer<Actor>>& actors);

  /**
   * @brief File manager panel to save and load actors.
   * @param actors Vector of shared pointers to actors (mutable).
   */
  void
    fileManagerPanel(std::vector<EngineUtilities::TSharedPointer<Actor>>& actors);

  /** @brief Index of the currently selected actor, or -1 if none. */
  int selectedActorIndex = -1;
};