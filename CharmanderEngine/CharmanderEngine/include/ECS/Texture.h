#pragma once
#include "../Prerequisites.h"
#include "Component.h"

/**
 * @class Texture
 * @brief Component that owns an sf::Texture loaded from disk.
 *
 * @details
 * Loads "<name>.<ext>" into an internal sf::Texture. On failure, logs
 * a message to std::cout. Acts as a data holder; drawing is done elsewhere.
 */
class
  Texture : public Component {

public:

  /**
   * @brief Default constructor; empty texture holder.
   */
  Texture() = default;

  /**
   * @brief Construct and load texture from "<name>.<ext>".
   * @param textureName File name without extension.
   * @param extension   Image extension (default "png").
   */
  Texture(const std::string& textureName,
    const std::string& extension = "png") :
    m_textureName(textureName),
    m_extension(extension),
    Component(TEXTURE) {
    if (!m_texture.loadFromFile(m_textureName + "." + m_extension)) {
      std::cout << "Error loading texture: " << m_textureName
        << "." << m_extension << std::endl;
    }
  }

  /**
   * @brief Virtual destructor.
   */
  virtual
    ~Texture() = default;

  /**
   * @brief Initialization hook (unused here).
   */
  void
    start() override {}

  /**
   * @brief Per-frame update hook (unused here).
   * @param deltaTime Seconds since last frame.
   */
  void
    update(float deltaTime) override {}

  /**
   * @brief Render hook (unused; this component is data only).
   * @param window Render window pointer.
   */
  void
    render(const EngineUtilities::TSharedPointer<Window>& window) override {}

  /**
   * @brief Destruction hook (unused here).
   */
  void
    destroy() override {}

  /**
   * @brief Access the internal sf::Texture.
   * @return Reference to the underlying texture.
   */
  sf::Texture&
    getTexture() { return m_texture; }

private:
  /** Texture resource loaded from file. */
  sf::Texture m_texture;

  /** Base file name without extension. */
  std::string m_textureName;

  /** File extension, e.g., "png" or "jpg". */
  std::string m_extension;
};