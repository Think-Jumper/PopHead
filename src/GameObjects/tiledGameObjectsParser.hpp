#pragma once

#include <SFML/Graphics.hpp>
#include <optional>
#include <string>

namespace ph {

class GameData;
class GameObject;
class CutSceneManager;
class Xml;

class TiledGameObjectsParser
{
public:
	TiledGameObjectsParser(GameData* gameData, GameObject& root, CutSceneManager& cutSceneManager);

	void parseFile(const std::string& filePath) const;

private:
	Xml findGameObjects(const Xml& mapFile) const;
	void loadObjects(const Xml& gameObjects) const;
	void loadLayerObjects() const;
	void loadContainerObjects() const;
	bool isObjectOfType(const Xml& gameObjectNode, const std::string& typeName) const;
	void loadZombie(const Xml& zombieNode) const;
	void loadNpc(const Xml& npcNode) const;
	void loadSpawner(const Xml& spawnerNode) const;
	void loadEntrance(const Xml& entranceNode) const;
	std::optional<std::string> getSceneFileName(const std::string& scenePathRelativeToMapFile) const;
	void loadGate(const Xml& gateNode) const;
	void loadCar(const Xml& carNode) const;
	void loadCamera(const Xml& cameraNode) const;
	void loadPlayer(const Xml& playerNode) const;
	void loadCutScene(const Xml& cutSceneNode) const;
	void loadCrawlingNpc(const Xml& crawlingNpcNode) const;

	Xml getProperty(const Xml& objectNode, const std::string& propertyName) const;
	bool hasCustomProperty(const Xml& gameObjectNode, const std::string& propertyName) const;
	Xml getCustomProperties(const Xml& gameObjectNode, const std::string& name) const;
	Xml getDefaultProperties(const std::string& name, const std::string& propertyName) const;
	std::vector<Xml> getObjectTypeNodes() const;

	sf::Vector2f getPositionAttribute(const Xml& gameObjectNode) const;
	sf::Vector2f getSizeAttribute(const Xml& gameObjectNode) const;

private:
	GameData* const mGameData;
	GameObject& mRoot;
	CutSceneManager& mCutSceneManager;
	mutable bool mHasLoadedPlayer;
};

}