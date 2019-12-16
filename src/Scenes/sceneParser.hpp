#pragma once

#include "ECS/entitiesTemplateStorage.hpp"
#include "Resources/resourceHolder.hpp"
#include <entt/entity/registry.hpp>
#include <string>

namespace ph{

class GameData;
class Xml;
class CutSceneManager;

template <typename GuiParser, typename MapParser, typename AudioParser, typename EnttParser>
class SceneParser
{
public:
	SceneParser(GameData* const gameData, CutSceneManager& cutSceneManager, EntitiesTemplateStorage& templateStorage,
                entt::registry& gameRegistry, const std::string& sceneFileName, TextureHolder&);

private:
	template<typename Parser>
	void parse(GameData* const gameData, const Xml& sceneLinksNode, const std::string& categoryName);

	void parseEcsEntities(const Xml& sceneLinksNode, EntitiesTemplateStorage& templateStorage, entt::registry& gameRegistry,
                          TextureHolder& textureHolder);

	void parseAmbientLight(const Xml& sceneLinksNode);
	void parseMap(const Xml& sceneLinksNode, AIManager& aiManager, entt::registry& gameRegistry, EntitiesTemplateStorage& templates, TextureHolder& textures);
};

}
#include "sceneParser.inl"
