#include "ResourceManager.h"

bool
ResourceManager(const std::string& fileName,
  const std::string& extension) {
  // Verificar si la textura esta cargada
  if (m_textures.find(fileName) != m_textures.end()) {
    return true;
  }

  //Crear y cargar la textura
  auto texture = EngineUtilities::MakeShared<Texture>(fileName, extension);
  m_textures[fileName] = texture;
  return true;
}

EngineUtilities::TSharedPointer<texture>
ResourceManager::getTexture(const std::string& fileName) {
  //Buscar la textura
  auto it = m_textures.find(fileName);
  if (it != m_textures.end()) {
    return it->second;
  }

  //Mensaje de advertencia
  std::cerr << "[ResourceManager] Texture not found: " << fileName <<". Using default texture.\n";

  const std::string defaultKey = "Default";

  //Verificar si la textura por defecto esta cargada
  auto defaultIt = m_textures.find(defaultKey);
  if (defaultIt != m_textures.end()) {
    return defaultIt->second;
  }

  //Cargar la textura por defecto
  auto defaultTexture = EngineUtilities::MakeShared<Texture>(defaultKey, "png");

  m_textures[defaultKey] = defaultTexture;
  return defaultTexture;
}