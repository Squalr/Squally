#include "SerializableTileLayer.h"

#include "cocos/2d/CCFastTMXLayer.h"
#include "cocos/2d/CCFastTMXTiledMap.h"
#include "cocos/base/CCValue.h"

#include <tinyxml2.h>

#include "Engine/Maps/ObjectifiedTile.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

const std::string SerializableTileLayer::MapKeyPropertyWidth = "width";
const std::string SerializableTileLayer::MapKeyPropertyHeight = "height";
const std::string SerializableTileLayer::MapKeyPropertyType = "type";
const std::string SerializableTileLayer::MapKeyPropertyObjectify = "objectify";
const std::string SerializableTileLayer::MapKeyPropertyEncoding = "encoding";
const std::string SerializableTileLayer::MapKeyPropertyEncodingValue = "csv";

SerializableTileLayer* SerializableTileLayer::deserialize(cocos_experimental::TMXLayer* initTileLayer)
{
	SerializableTileLayer* instance = new SerializableTileLayer(initTileLayer);

	instance->autorelease();

	return instance;
}

SerializableTileLayer::SerializableTileLayer(cocos_experimental::TMXLayer* initTileLayer) : SerializableLayer(initTileLayer->getProperties(), initTileLayer->getLayerName())
{
	this->tileLayer = initTileLayer;

	// Can be a nullptr if the layer is empty
	if (this->tileLayer != nullptr)
	{
		// Layer name is not intrinsically in properties -- manually add it
		this->properties[SerializableTileLayer::MapKeyPropertyName] = Value(this->tileLayer->getLayerName());

		// Check for the objectify flag. This basically converts all tiles in the layer into individual sprites. Cocos2d-x is garbage and does not allow
		// for dynamic Z sorting on a tile layer, because the tiles are sprite batch rendered instead of as individual sprites.
		// Objectifying comes at a severe performance penalty, so we have to be very careful which layers this gets done on -- ideally only for things like walls and small mountains and things
		if (GameUtils::keyExists(this->properties, SerializableTileLayer::MapKeyPropertyObjectify) && this->properties.at(SerializableTileLayer::MapKeyPropertyObjectify).asBool())
		{
			for (int x = 0; x < this->tileLayer->getLayerSize().width; x++)
			{
				for (int y = 0; y < this->tileLayer->getLayerSize().height; y++)
				{
					Sprite* tile = this->tileLayer->getTileAt(Vec2(x, y));

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
			this->tileLayer->retain();
			this->tileLayer->getParent()->removeChild(this->tileLayer);
			this->addChild(this->tileLayer);
		}
	}
}

SerializableTileLayer::~SerializableTileLayer()
{
}

void SerializableTileLayer::serialize(tinyxml2::XMLDocument* documentRoot, tinyxml2::XMLElement* parentElement, Size mapUnitSize, Size mapTileSize)
{
	tinyxml2::XMLElement* layerElement = documentRoot->NewElement("layer");
	layerElement->SetAttribute(SerializableTileLayer::MapKeyPropertyName.c_str(), this->properties.at(SerializableTileLayer::MapKeyPropertyName).asString().c_str());
	layerElement->SetAttribute(SerializableTileLayer::MapKeyPropertyWidth.c_str(), Value(mapUnitSize.width).asString().c_str());
	layerElement->SetAttribute(SerializableTileLayer::MapKeyPropertyHeight.c_str(), Value(mapUnitSize.height).asString().c_str());

	tinyxml2::XMLElement* dataElement = documentRoot->NewElement("data");
	dataElement->SetAttribute(SerializableTileLayer::MapKeyPropertyEncoding.c_str(), SerializableTileLayer::MapKeyPropertyEncodingValue.c_str());

	if (this->tileLayer != nullptr)
	{
		std::string csvContent = "\n";

		for (int y = 0; y < mapUnitSize.height; y++)
		{
			for (int x = 0; x < mapUnitSize.width; x++)
			{
				csvContent += std::to_string(this->tileLayer->getTileGIDAt(Vec2(x, y))) + ",";
			}

			csvContent += "\n";
		}

		csvContent = csvContent.erase(csvContent.find_last_of(','), 1);

		tinyxml2::XMLText* csvText = documentRoot->NewText(csvContent.c_str());
		dataElement->LinkEndChild(csvText);
	}

	layerElement->LinkEndChild(dataElement);
	parentElement->LinkEndChild(layerElement);
}

std::string SerializableTileLayer::getType()
{
	if (GameUtils::keyExists(this->properties, SerializableTileLayer::MapKeyPropertyType))
	{
		return this->properties.at(SerializableTileLayer::MapKeyPropertyType).asString();
	}

	return "";
}

std::vector<std::vector<int>> SerializableTileLayer::getGidMap()
{
	std::vector<std::vector<int>> gidMap = std::vector<std::vector<int>>();

	if (this->tileLayer != nullptr)
	{
		int width = this->tileLayer->getLayerSize().width;
		int height = this->tileLayer->getLayerSize().height;

		for (int y = 0; y < height; y++)
		{
			std::vector<int> row = std::vector<int>();

			for (int x = 0; x < width; x++)
			{
				row.push_back(this->tileLayer->getTileGIDAt(Vec2(x, y)));
			}

			gidMap.push_back(row);
		}
	}

	return gidMap;
}
