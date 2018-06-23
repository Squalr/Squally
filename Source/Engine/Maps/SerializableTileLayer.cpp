#include "SerializableTileLayer.h"

const std::string SerializableTileLayer::KeyPropertyWidth = "width";
const std::string SerializableTileLayer::KeyPropertyHeight = "height";
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
	// Can be a nullptr if the layer is empty
	if (initTileLayer != nullptr)
	{
		// Layer name is not intrinsically in properties -- manually add it
		(*this->properties)[SerializableTileLayer::KeyPropertyName] = Value(initTileLayer->getLayerName());

		initTileLayer->retain();
		initTileLayer->getParent()->removeChild(initTileLayer);
		this->addChild(initTileLayer);
	}
	
	this->tileLayer = initTileLayer;
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
