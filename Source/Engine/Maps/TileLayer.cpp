#include "TileLayer.h"

#include "cocos/2d/CCFastTMXLayer.h"
#include "cocos/2d/CCFastTMXTiledMap.h"
#include "cocos/base/CCValue.h"

#include <tinyxml2.h>

#include "Engine/Maps/ObjectifiedTile.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

const std::string TileLayer::MapKeyTilemapType = "tilemap";
const std::string TileLayer::MapKeyPropertyWidth = "width";
const std::string TileLayer::MapKeyPropertyHeight = "height";
const std::string TileLayer::MapKeyPropertyType = "type";
const std::string TileLayer::MapKeyPropertyObjectify = "objectify";
const std::string TileLayer::MapKeyPropertyEncoding = "encoding";
const std::string TileLayer::MapKeyPropertyEncodingValue = "csv";

TileLayer* TileLayer::deserialize(cocos_experimental::TMXLayer* initTileLayer)
{
	TileLayer* instance = new TileLayer(initTileLayer);

	instance->autorelease();

	return instance;
}

TileLayer::TileLayer(cocos_experimental::TMXLayer* initTileLayer) : MapLayer(initTileLayer->getProperties(), initTileLayer->getLayerName(), TileLayer::MapKeyTilemapType)
{
	this->tileLayer = initTileLayer;
	this->objectified = GameUtils::getKeyOrDefault(this->properties, TileLayer::MapKeyPropertyObjectify, Value(false)).asBool();

	// Can be a nullptr if the layer is empty
	if (this->tileLayer != nullptr)
	{
		// Layer name is not intrinsically in properties -- manually add it
		this->properties[TileLayer::MapKeyPropertyName] = Value(this->tileLayer->getLayerName());

		// Check for the objectify flag. This basically converts all tiles in the layer into individual sprites. Cocos2d-x is garbage and does not allow
		// for dynamic Z sorting on a tile layer, because the tiles are sprite batch rendered instead of as individual sprites.
		// Objectifying comes at a severe performance penalty, so we have to be very careful which layers this gets done on -- ideally only for things like walls and small mountains and things
		if (this->objectified)
		{
			for (int x = 0; x < this->tileLayer->getLayerSize().width; x++)
			{
				for (int y = 0; y < this->tileLayer->getLayerSize().height; y++)
				{
					Sprite* tile = this->tileLayer->getTileAt(Vec2(float(x), float(y)));

					if (tile != nullptr)
					{
						this->addChild(ObjectifiedTile::create(tile, this->properties));
					}
				}
			}

			// Keep the tile layer around, just dont add it as a child since we dont need it as such
			this->tileLayer->retain();
		}
		else
		{
			GameUtils::changeParent(this->tileLayer, this, true);
		}
	}
}

TileLayer::~TileLayer()
{
	if (this->tileLayer != nullptr && this->tileLayer->getParent() == nullptr)
	{
		this->tileLayer->release();
	}
}

std::string TileLayer::getType()
{
	return GameUtils::getKeyOrDefault(this->properties, TileLayer::MapKeyPropertyType, Value("")).asString();
}

std::vector<std::vector<int>> TileLayer::getGidMap()
{
	std::vector<std::vector<int>> gidMap = std::vector<std::vector<int>>();

	if (this->tileLayer != nullptr)
	{
		int width = int(this->tileLayer->getLayerSize().width);
		int height = int(this->tileLayer->getLayerSize().height);

		for (int y = 0; y < height; y++)
		{
			std::vector<int> row = std::vector<int>();

			for (int x = 0; x < width; x++)
			{
				row.push_back(this->tileLayer->getTileGIDAt(Vec2(float(x), float(y))));
			}

			gidMap.push_back(row);
		}
	}

	return gidMap;
}

bool TileLayer::isObjectified()
{
	return this->objectified;
}
