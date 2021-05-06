#include "texture_manager.h"

void TextureManager::Add(std::string key, Texture* texture) {
	textureMap[key] = texture;
}

Texture* TextureManager::Get(std::string key) {
	return textureMap[key];
}

void TextureManager::Free() {
	std::unordered_map<std::string, Texture*> empty;
	using std::swap;
	swap(textureMap, empty);
	// for (auto &pair : textureMap) {
	// 	// delete pair.second;
	// 	textureMap.erase(pair.first);
	// }
}

TextureManager::~TextureManager() {
	Free();
}
