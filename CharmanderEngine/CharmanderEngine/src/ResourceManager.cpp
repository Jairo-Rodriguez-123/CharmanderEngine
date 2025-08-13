#include "ResourceManager.h"

bool
ResourceManager::loadTexture(const std::string& fileName,
	const std::string& extension) {

	if (m_textures.find(fileName) != m_textures.end()) {
		return true;
	}

	auto texture = EngineUtilities::MakeShared<Texture>(fileName, extension);
	m_textures[fileName] = texture;
	return true;
}

EngineUtilities::TSharedPointer<Texture>
ResourceManager::getTexture(const std::string& fileName) {

	auto it = m_textures.find(fileName);
	if (it != m_textures.end()) {
		return it->second;
	}

	std::cerr << "[ResourceManager] Texture not found: "
		<< fileName << ". Using default texture. \n";

	const std::string defaultKey = "Default";

	auto defaultIt = m_textures.find(defaultKey);
	if (defaultIt != m_textures.end()) {
		return defaultIt->second;
	}

	auto defaultTexture = EngineUtilities::MakeShared<Texture>(defaultKey, "png");
	m_textures[defaultKey] = defaultTexture;
	return defaultTexture;
}