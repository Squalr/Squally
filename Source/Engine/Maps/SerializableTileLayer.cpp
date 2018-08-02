#include "SerializableTileLayer.h"

const std::string SerializableTileLayer::KeyPropertyWidth = "width";
const std::string SerializableTileLayer::KeyPropertyHeight = "height";
const std::string SerializableTileLayer::KeyPropertyType = "type";
const std::string SerializableTileLayer::KeyPropertyObjectify = "objectify";
const std::string SerializableTileLayer::KeyPropertyEncoding = "encoding";
const std::string SerializableTileLayer::KeyPropertyEncodingValue = "csv";

SerializableTileLayer* SerializableTileLayer::deserialize(cocos_experimental::TMXLayer* initTileLayer)
{
	SerializableTileLayer* instance = new SerializableTileLayer(initTileLayer);

	instance->autorelease();

	return instance;
}

SerializableTileLayer::SerializableTileLayer(cocos_experimental::TMXLayer* initTileLayer) : SerializableLayer(new ValueMap(initTileLayer->getProperties()), initTileLayer->getLayerName(), nullptr)
{
	this->tileLayer = initTileLayer;

	// Can be a nullptr if the layer is empty
	if (this->tileLayer != nullptr)
	{
		// Layer name is not intrinsically in properties -- manually add it
		(*this->properties)[SerializableTileLayer::KeyPropertyName] = Value(this->tileLayer->getLayerName());

		// Check for the objectify flag. This basically converts all tiles in the layer into individual sprites. Cocos2d-x is garbage and does not allow
		// for dynamic Z sorting on a tile layer, because the tiles are sprite batch rendered instead of as individual sprites.
		// Objectifying comes at a severe performance penalty, so we have to be very careful which layers this gets done on -- ideally only for things like walls and small mountains and things
		if (GameUtils::keyExists(this->properties, SerializableTileLayer::KeyPropertyObjectify) && this->properties->at(SerializableTileLayer::KeyPropertyObjectify).asBool())
		{
			for (int x = 0; x < this->tileLayer->getLayerSize().width; x++)
			{
				for (int y = 0; y < this->tileLayer->getLayerSize().width; y++)
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
	layerElement->SetAttribute(SerializableTileLayer::KeyPropertyName.c_str(), this->properties->at(SerializableTileLayer::KeyPropertyName).asString().c_str());
	layerElement->SetAttribute(SerializableTileLayer::KeyPropertyWidth.c_str(), Value(mapUnitSize.width).asString().c_str());
	layerElement->SetAttribute(SerializableTileLayer::KeyPropertyHeight.c_str(), Value(mapUnitSize.height).asString().c_str());

	tinyxml2::XMLElement* dataElement = documentRoot->NewElement("data");
	dataElement->SetAttribute(SerializableTileLayer::KeyPropertyEncoding.c_str(), SerializableTileLayer::KeyPropertyEncodingValue.c_str());

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
	if (GameUtils::keyExists(this->properties, SerializableTileLayer::KeyPropertyType))
	{
		return this->properties->at(SerializableTileLayer::KeyPropertyType).asString();
	}

	return "";
}
