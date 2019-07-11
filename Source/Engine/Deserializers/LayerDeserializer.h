#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Value;
	typedef std::map<std::string, Value> ValueMap;
	typedef std::vector<Value> ValueVector;
}

class MapLayer;

class LayerDeserializer : public SmartNode
{
public:
	struct LayerDeserializationArgs
	{
		MapLayer* mapLayer;
		int layerIndex;

		LayerDeserializationArgs(MapLayer* mapLayer, int layerIndex) : mapLayer(mapLayer), layerIndex(layerIndex)
		{
		}
	};
	
	struct LayerDeserializationRequestArgs
	{
		const cocos2d::ValueMap& properties;
		const cocos2d::ValueVector& objects;
		int layerIndex;
		std::string mapIdentifier;
		cocos2d::Size mapSize;
		bool isIsometric;
		std::function<void(LayerDeserializer::LayerDeserializationArgs)> onDeserializeCallback;
		bool handled;

		LayerDeserializationRequestArgs(const cocos2d::ValueMap& properties,
			const cocos2d::ValueVector& objects,
			int layerIndex,
			std::string mapIdentifier,
			cocos2d::Size mapSize,
			bool isIsometric,
			std::function<void(LayerDeserializer::LayerDeserializationArgs)> onDeserializeCallback,
			bool handled = false
		):
			properties(properties), objects(objects), layerIndex(layerIndex), mapIdentifier(mapIdentifier), mapSize(mapSize), isIsometric(isIsometric), onDeserializeCallback(onDeserializeCallback), handled(handled)
		{
		}
	};

	virtual void deserialize(LayerDeserializer::LayerDeserializationRequestArgs* args) = 0;
	std::string getLayerType();

protected:
	LayerDeserializer(std::string layerType);
	~LayerDeserializer();

private:
	typedef SmartNode super;

	std::string layerType;
};
