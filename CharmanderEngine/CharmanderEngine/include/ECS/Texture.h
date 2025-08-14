#pragma once
#include "../Prerequisites.h"
#include "Component.h"

/**
 * @class Texture
 * @brief Represents a texture component in the ECS, responsible for loading and managing an SFML texture.
 */
class
	Texture : public Component {
public:
	/**
	* @brief Default constructor for Texture.
	*/
	Texture() = default;

	/**
	* @brief Constructs a Texture with the specified name and extension.
	* @param textureName The base name of the texture file (without extension).
	* @param extension The file extension for the texture (default is "png").
	*
	* Loads the texture from file and prints an error message if loading fails.
	*/
	Texture(const std::string& textureName, const std::string& extension = "png")
		: m_textureName(textureName), m_extension(extension), Component(TEXTURE) {
		if (!m_texture.loadFromFile(m_textureName + "." + m_extension)) {
			std::cout << "Error loading texture: " <<
				m_textureName << "." << m_extension << std::endl;
		}
	}

	/**
	* @brief Virtual destructor for Texture.
	*/
	virtual
		~Texture() = default;

	/**
	* @brief Starts the texture component. Called once when the component is initialized.
	*/
	void
		start() override {};

	/**
	* @brief Updates the texture component.
	* @param deltaTime Time elapsed since last update.
	*/
	void
		update(float deltaTime) override {};

	/**
	* @brief Renders the texture component.
	* @param window Shared pointer to the Window where the component will be rendered.
	*/
	void
		render(const EngineUtilities::TSharedPointer<Window>& window) override {};

	/**
	* @brief Destroys the texture component and releases resources.
	*/
	void
		destroy() override {};

	/**
	* @brief Gets the underlying SFML texture.
	* @return Reference to the sf::Texture object.
	*/
	sf::Texture&
		getTexture() {
		return m_texture;
	}

private:
	/**
	* @brief The SFML texture managed by this component.
	*/
	sf::Texture m_texture;
	/**
	* @brief The base name of the texture file (without extension).
	*/
	std::string m_textureName;
	/**
	* @brief The file extension for the texture.
	*/
	std::string m_extension;
};