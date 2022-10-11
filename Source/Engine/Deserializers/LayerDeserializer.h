#pragma once

#include "cocos/base/CCValue.h"

#include "Engine/SmartNode.h"

class MapLayer;

class LayerDeserializer : public SmartNode
{
public:
	struct LayerDeserializationArgs
	{
		MapLayer* mapLayer = nullptr;
		int layerIndex = 0;

		LayerDeserializationArgs(MapLayer* mapLayer, int layerIndex) : mapLayer(mapLayer), layerIndex(layerIndex)
		{
		}
	};
	
	struct LayerDeserializationRequestArgs
	{
		const cocos2d::ValueMap& properties;
		const cocos2d::ValueVector& objects;
		int layerIndex = 0;
		std::string mapIdentifier;
		cocos2d::CSize mapSize;
		bool isIsometric = false;
		std::function<void(LayerDeserializer::LayerDeserializationArgs)> onDeserializeCallback = nullptr;

		LayerDeserializationRequestArgs(const cocos2d::ValueMap& properties,
			const cocos2d::ValueVector& objects,
			int layerIndex,
			std::string mapIdentifier,
			cocos2d::CSize mapSize,
			bool isIsometric,
			std::function<void(LayerDeserializer::LayerDeserializationArgs)> onDeserializeCallback,
			bool handled = false
		):
			properties(properties), objects(objects), layerIndex(layerIndex), mapIdentifier(mapIdentifier), mapSize(mapSize), isIsometric(isIsometric), onDeserializeCallback(onDeserializeCallback), handled(handled)
		{
		}

		void handle()
		{
			this->handled = true;
		}

		bool isHandled()
		{
			return this->handled;
		}

		private:
			bool handled = false;

	};

	virtual void deserialize(LayerDeserializer::LayerDeserializationRequestArgs* args) = 0;
	std::string getLayerType();

protected:
	LayerDeserializer(std::string layerType);
	virtual ~LayerDeserializer();

private:
	typedef SmartNode super;

	std::string layerType;
};
