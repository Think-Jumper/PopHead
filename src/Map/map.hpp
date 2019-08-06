#pragma once

#include "Utilities/xml.hpp"
#include "chunkMap.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>

namespace ph{

class GameData;

struct TilesData 
{
	unsigned firstGlobalTileId;
	std::vector<unsigned> ids;
	std::vector<sf::FloatRect> bounds;
};

struct TilesetsData 
{
	std::vector<unsigned> firstGlobalTileIds;
	std::vector<unsigned> tileCounts;
	std::vector<unsigned> columnsCounts;
	std::vector<TilesData> tilesData;
	std::string tilesetFileName;
};

class Map
{
public:
    Map();

	void loadFromFile(const std::string& filename);

    void draw(sf::RenderTarget& target, const sf::RenderStates states, const sf::FloatRect cameraBounds) const;

	void setGameData(GameData* const gameData) { mGameData = gameData; };

private:
	void checkMapSupport(const Xml& mapNode) const;

	sf::Vector2u getMapSize(const Xml& mapNode) const;

	sf::Vector2u getTileSize(const Xml& mapNode) const;

	std::vector<Xml> getTilesetNodes(const Xml& mapNode) const;

	auto getTilesetsData(const std::vector<Xml>& tilesetNodes) const -> const TilesetsData;

	auto getTilesData(const std::vector<Xml>& tileNodes) const -> TilesData;

	std::vector<Xml> getLayerNodes(const Xml& mapNode) const;

	void createChunkMap(const TilesetsData& tilesets, const sf::Vector2u mapSize, const sf::Vector2u tileSize);

	void createAllLayers(const std::vector<Xml>&, const TilesetsData& tilesets,
		                 const sf::Vector2u mapSize, const sf::Vector2u tileSize);

	std::vector<unsigned> toGlobalTileIds(const Xml& dataNode) const;

	void createLayer(const std::vector<unsigned>& globalTileIds, const TilesetsData& tilesets,
	                 const sf::Vector2u mapSize, const sf::Vector2u tileSize);

	bool hasTile(unsigned globalTileId) const { return globalTileId != 0; }

	std::size_t findTilesetIndex(const unsigned globalTileId, const TilesetsData& tilesets) const;

	std::size_t findTilesIndex(const unsigned firstGlobalTileId, const std::vector<TilesData>& tilesData) const;

	void loadCollisionBodies(const unsigned tileId, const TilesData& tilesData, sf::Vector2f position);

private:
	inline static const std::string pathToTilesetsDirectory = "textures/map/";
	inline static const std::string pathToMapNotEmbeddedTilesets = "";
	std::unique_ptr<ChunkMap> mChunkMap;
	GameData* mGameData;
};

}
