#pragma once
#include "Prerequisites.h"
#include "ECS/Texture.h"

/**
 * @class ResourceManager
 * @brief Singleton for managing shared game resources.
 *
 * @details
 * Stores and provides access to textures, avoiding duplicate loads.
 * Uses shared pointers to ensure resources are properly managed and
 * shared across systems without unnecessary copies.
 */
class
  ResourceManager {

public:
  /** @brief Default constructor. */
  ResourceManager() {}

  /** @brief Default destructor. */
  ~ResourceManager() {}

private:
  /** @brief Copy constructor deleted to enforce singleton pattern. */
  ResourceManager(const ResourceManager&) = delete;

  /** @brief Assignment operator deleted to enforce singleton pattern. */
  ResourceManager& operator=(const ResourceManager&) = delete;

public:
  /**
   * @brief Get the singleton instance of ResourceManager.
   * @return Reference to the singleton instance.
   */
  static ResourceManager&
    getInstance() {
    static ResourceManager instance;
    return instance;
  }

  /**
   * @brief Load a texture from file and store it.
   * @param filename File name without extension.
   * @param extension File extension (e.g., "png").
   * @return True if the texture was loaded successfully.
   */
  bool
    loadTexture(const std::string& filename,
      const std::string& extension);

  /**
   * @brief Retrieve a texture by file name.
   * @param fileName Name used when loading the texture.
   * @return Shared pointer to the Texture, or nullptr if not found.
   */
  EngineUtilities::TSharedPointer<Texture>
    getTexture(const std::string& fileName);

private:
  /** Map of loaded textures indexed by their file name. */
  std::unordered_map<std::string,
    EngineUtilities::TSharedPointer<Texture>> m_textures;
};