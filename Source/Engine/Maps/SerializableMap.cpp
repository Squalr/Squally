#include "SerializableMap.h"

#include "cocos/2d/CCFastTMXLayer.h"
#include "cocos/2d/CCFastTMXTiledMap.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/platform/CCFileUtils.h"

#include <tinyxml2/tinyxml2.h>

#include "Engine/Events/DeserializationEvents.h"
#include "Engine/Maps/ObjectifiedTile.h"
#include "Engine/Maps/SerializableLayer.h"
#include "Engine/Maps/SerializableTileLayer.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"

#include "Resources/MapResources.h"

const std::string SerializableMap::KeyTypeCollision = "collision";

using namespace cocos2d;

SerializableMap::SerializableMap(std::string mapFileName, const std::vector<SerializableLayer*>& layers,
		Size unitSize, Size tileSize, MapOrientation orientation)
{
	this->collisionLayers = std::vector<SerializableTileLayer*>();
	this->tileLayers = std::vector<SerializableTileLayer*>();
	this->levelMapFileName = mapFileName;
	this->serializableLayers = layers;
	this->mapUnitSize = unitSize;
	this->mapTileSize = tileSize;
	this->orientation = orientation;

	for (auto it = layers.begin(); it != layers.end(); it++)
	{
		this->addChild(*it);
	}

	if (this->orientation == MapOrientation::Isometric)
	{
		this->isometricMapPreparation();
	}
}

SerializableMap::~SerializableMap()
{
}

SerializableMap* SerializableMap::deserialize(std::string mapFileName)
{
	cocos_experimental::TMXTiledMap* mapRaw = cocos_experimental::TMXTiledMap::create(mapFileName);
	std::map<int, SerializableLayer*> deserializedLayerMap = std::map<int, SerializableLayer*>();
	std::vector<cocos_experimental::TMXLayer*> tileLayers = std::vector<cocos_experimental::TMXLayer*>();
	std::vector<SerializableLayer*> deserializedLayers = std::vector<SerializableLayer*>();

	// Callback to receive deserialized layers as they are parsed by their deserializers
	auto onDeserializeCallback = [&](DeserializationEvents::LayerDeserializationArgs args)
	{
		deserializedLayerMap.emplace(args.layerIndex, args.serializableLayer);
	};

	// Fire event requesting the deserialization of this layer -- the appropriate deserializer class should handle it
	for (auto it = mapRaw->getObjectGroups().begin(); it != mapRaw->getObjectGroups().end(); it++)
	{
		DeserializationEvents::TriggerRequestLayerDeserialize(DeserializationEvents::LayerDeserializationRequestArgs(
			*it,
			DeserializationEvents::DeserializationMapMeta(
				Size(mapRaw->getMapSize().width * mapRaw->getTileSize().width, mapRaw->getMapSize().height * mapRaw->getTileSize().height),
				mapRaw->getMapOrientation() == MapOrientation::Isometric
			),
			onDeserializeCallback
		));
	}

	// Pull out tile layers
	for (auto it = mapRaw->getChildren().begin(); it != mapRaw->getChildren().end(); it++)
	{
		cocos_experimental::TMXLayer* tileLayer = dynamic_cast<cocos_experimental::TMXLayer*>(*it);

		if (tileLayer != nullptr)
		{
			tileLayers.push_back(tileLayer);
		}
	}

	// Deserialize tiles (separate step from pulling them out because deserialization removes the child and would ruin the getChildren() iterator)
	for (auto it = tileLayers.begin(); it != tileLayers.end(); it++)
	{
		deserializedLayerMap.emplace((*it)->layerIndex, SerializableTileLayer::deserialize((*it)));
	}

	// Convert from map to ordered vector
	for (auto it = deserializedLayerMap.begin(); it != deserializedLayerMap.end(); it++)
	{
		deserializedLayers.push_back(it->second);
	}
	
	SerializableMap* instance = new SerializableMap(mapFileName, deserializedLayers, mapRaw->getMapSize(), mapRaw->getTileSize(), (MapOrientation)mapRaw->getMapOrientation());

	instance->autorelease();

	return instance;
}

bool SerializableMap::serialize()
{
	tinyxml2::XMLDocument* documentRoot = new (std::nothrow)tinyxml2::XMLDocument();
	tinyxml2::XMLDeclaration* declaration = documentRoot->NewDeclaration(("xml version=" + StrUtils::quote("1.0") + " encoding=" + StrUtils::quote("UTF-8")).c_str());
	documentRoot->LinkEndChild(declaration);

	tinyxml2::XMLElement* mapElement = documentRoot->NewElement("map");
	mapElement->SetAttribute("version", "1.0");
	mapElement->SetAttribute("tiledversion", "1.0.3");

	if (this->isPlatformer())
	{
		mapElement->SetAttribute("orientation", "orthogonal");
	}
	else if (this->isIsometric())
	{
		mapElement->SetAttribute("orientation", "isometric");
	}

	mapElement->SetAttribute("renderorder", "right-down");
	mapElement->SetAttribute("width", std::to_string((int)this->getMapUnitSize().width).c_str());
	mapElement->SetAttribute("height", std::to_string((int)this->getMapUnitSize().height).c_str());
	mapElement->SetAttribute("tilewidth", std::to_string((int)this->getMapTileSize().width).c_str());
	mapElement->SetAttribute("tileheight", std::to_string((int)this->getMapTileSize().height).c_str());

	// TODO: This is not isometric friendly
	Sprite* tileMap = Sprite::create(MapResources::TileMap);

	tinyxml2::XMLElement* tileSetElement = documentRoot->NewElement("tileset");
	tileSetElement->SetAttribute("firstgid", "1");
	tileSetElement->SetAttribute("name", "TileMap");
	tileSetElement->SetAttribute("tilewidth", std::to_string((int)this->getMapTileSize().width).c_str());
	tileSetElement->SetAttribute("tileheight", std::to_string((int)this->getMapTileSize().height).c_str());
	tileSetElement->SetAttribute("tilecount", std::to_string(0).c_str()); // Unused
	tileSetElement->SetAttribute("columns", std::to_string((int)tileMap->getContentSize().width / (int)this->getMapTileSize().width).c_str());

	tinyxml2::XMLElement* gridElement = documentRoot->NewElement("grid");
	gridElement->SetAttribute("width", std::to_string(64).c_str()); // Unused
	gridElement->SetAttribute("height", std::to_string(64).c_str()); // Unused
	tileSetElement->LinkEndChild(gridElement);

	tinyxml2::XMLElement* imageElement = documentRoot->NewElement("image");
	imageElement->SetAttribute("source", ("../" + StrUtils::replaceAll(MapResources::TileMap, "\\", "/")).c_str());
	imageElement->SetAttribute("width", std::to_string((int)tileMap->getContentSize().width).c_str());
	imageElement->SetAttribute("height", std::to_string((int)tileMap->getContentSize().height).c_str());
	tileSetElement->LinkEndChild(imageElement);

	mapElement->LinkEndChild(tileSetElement);

	// Serialize all layers
	for (auto it = this->serializableLayers.begin(); it != this->serializableLayers.end(); it++)
	{
		(*it)->serialize(documentRoot, mapElement, this->getMapUnitSize(), this->getMapTileSize());
	}

	// TODO: count obj ids
	mapElement->SetAttribute("nextobjectid", std::to_string(366).c_str());

	documentRoot->LinkEndChild(mapElement);

	return tinyxml2::XML_SUCCESS == documentRoot->SaveFile(FileUtils::getInstance()->fullPathForFilename(this->levelMapFileName + ".dbg.tmx").c_str());
}

std::string SerializableMap::getMapFileName()
{
	return this->levelMapFileName;
}

void SerializableMap::hackerModeEnable()
{
	for (auto it = this->serializableLayers.begin(); it != this->serializableLayers.end(); it++)
	{
		if (!(*it)->isHackerModeIgnored())
		{
			(*it)->setVisible(false);
		}
	}
}

void SerializableMap::hackerModeDisable()
{
	for (auto it = this->serializableLayers.begin(); it != this->serializableLayers.end(); it++)
	{
		(*it)->setVisible(true);
	}
}

Size SerializableMap::getMapSize()
{
	Size unitSize = this->getMapUnitSize();
	Size tileSize = this->getMapTileSize();

	return Size(unitSize.width * tileSize.width, unitSize.height * tileSize.height);
}

Size SerializableMap::getMapUnitSize()
{
	return this->mapUnitSize;
}

Size SerializableMap::getMapTileSize()
{
	return this->mapTileSize;
}

bool SerializableMap::isIsometric()
{
	return this->orientation == MapOrientation::Isometric;
}
bool SerializableMap::isPlatformer()
{
	return this->orientation == MapOrientation::Platformer;
}

void SerializableMap::appendLayer(SerializableLayer* layer)
{
	this->serializableLayers.push_back(layer);
	this->addChild(layer);
}

void SerializableMap::onEnter()
{
	Node::onEnter();

	this->scheduleUpdate();
}

void SerializableMap::update(float dt)
{
	Node::update(dt);

	this->isometricZSort(this);
}

void SerializableMap::setCollisionLayersVisible(bool isVisible)
{
	for (auto it = this->collisionLayers.begin(); it != this->collisionLayers.end(); it++)
	{
		(*it)->setVisible(isVisible);
	}
}

void SerializableMap::isometricZSort(Node* node)
{
	if (this->orientation != MapOrientation::Isometric || node == nullptr)
	{
		return;
	}

	// Only z sort the objects in the map (top left lowest, bottom right highest)
	if (dynamic_cast<SerializableObject*>(node) != nullptr)
	{
		// Note: This sets local Z order, so make sure objects are on the same layer if you want them to dynamically sort.
		// TODO: This works for most cases but is incomplete
		Vec2 position = node->getParent()->convertToWorldSpace(node->getPosition());

		if (dynamic_cast<ObjectifiedTile*>(node) != nullptr)
		{
			position.y += this->mapTileSize.height;
		}

		node->setZOrder((int)(-position.y));
	}

	// Recurse
	for (auto it = node->getChildren().begin(); it != node->getChildren().end(); it++)
	{
		this->isometricZSort(*it);
	}
}

void SerializableMap::isometricMapPreparation()
{
	if (this->orientation != MapOrientation::Isometric)
	{
		return;
	}

	// Flatten tile layers so all children are the immediate child of the layer (needed for Z sorting)
	for (auto it = this->getChildren().begin(); it != this->getChildren().end(); it++)
	{
		if (dynamic_cast<SerializableTileLayer*>(*it) != nullptr)
		{
			//// GameUtils::flattenNode(dynamic_cast<SerializableTileLayer*>(*it));
		}
	}

	for (auto it = this->getChildren().begin(); it != this->getChildren().end(); it++)
	{
		// Tile layers:
		if (dynamic_cast<SerializableTileLayer*>(*it) != nullptr)
		{
			SerializableTileLayer* tileLayer = dynamic_cast<SerializableTileLayer*>(*it);

			if (tileLayer->getType() == SerializableMap::KeyTypeCollision)
			{
				// Pull out collision layer
				this->collisionLayers.push_back(tileLayer);
			}
			else
			{
				// Pull out standard tile layer
				this->tileLayers.push_back(tileLayer);
			}
		}
		// Object layers
		else if (dynamic_cast<SerializableLayer*>(*it) != nullptr)
		{
			SerializableLayer* objectLayer = dynamic_cast<SerializableLayer*>(*it);

			// Iterate through remaining layers to find the next tile layer
			for (auto itClone = std::vector<Node*>::iterator(it); itClone != this->getChildren().end(); itClone++)
			{
				SerializableTileLayer* nextTileLayer = dynamic_cast<SerializableTileLayer*>(*itClone);

				// Pull out objects and inject them into the next highest tile layer (allows for proper dynamic Z sorting)
				if (nextTileLayer != nullptr && nextTileLayer->getType() != SerializableMap::KeyTypeCollision)
				{
					cocos2d::Vector<Node*> children = objectLayer->getChildren();

					for (auto childIt = children.begin(); childIt != children.end(); childIt++)
					{
						GameUtils::changeParent(*childIt, nextTileLayer, true);
					}
				}
			}
		}

		this->setCollisionLayersVisible(false);
	}
}
