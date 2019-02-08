#pragma once
#include "cocos/base/CCValue.h"
#include "cocos/math/CCGeometry.h"

class SerializableLayer;
class SerializableObject;

namespace cocos2d
{
	class TMXObjectGroup;
}

class DeserializationEvents
{
public:
	static const std::string RequestLayerDeserializeEvent;
	static const std::string RequestObjectDeserializeEvent;

	struct LayerDeserializationArgs
	{
		SerializableLayer* serializableLayer;
		int layerIndex;

		LayerDeserializationArgs(SerializableLayer* serializableLayer, int layerIndex) : serializableLayer(serializableLayer), layerIndex(layerIndex)
		{
		}
	};

	struct ObjectDeserializationArgs
	{
		SerializableObject* serializableObject;

		ObjectDeserializationArgs(SerializableObject* serializableObject) : serializableObject(serializableObject)
		{
		}
	};

	// Additional info used to help layer deserialization
	struct DeserializationMapMeta
	{
		std::string mapIdentifier;
		cocos2d::Size mapSize;
		bool isIsometric;

		DeserializationMapMeta(std::string mapIdentifier, cocos2d::Size mapSize, bool isIsometric) : mapIdentifier(mapIdentifier), mapSize(mapSize), isIsometric(isIsometric)
		{
		}
	};

	struct LayerDeserializationRequestArgs
	{
		cocos2d::TMXObjectGroup* objectGroup;
		DeserializationMapMeta mapMeta;
		std::function<void(LayerDeserializationArgs)> onDeserializeCallback;
		bool handled = false;

		LayerDeserializationRequestArgs(
			cocos2d::TMXObjectGroup* objectGroup,
			DeserializationMapMeta mapMeta,
			std::function<void(LayerDeserializationArgs)> onDeserializeCallback):
			objectGroup(objectGroup), mapMeta(mapMeta), onDeserializeCallback(onDeserializeCallback)
		{
		}
	};

	struct ObjectDeserializationRequestArgs
	{
		std::string typeName;
		cocos2d::ValueMap properties;
		std::function<void(ObjectDeserializationArgs)> onDeserializeCallback;
		bool handled = false;

		ObjectDeserializationRequestArgs(
			std::string typeName, 
			cocos2d::ValueMap properties,
			std::function<void(ObjectDeserializationArgs)> onDeserializeCallback):
			typeName(typeName), properties(properties), onDeserializeCallback(onDeserializeCallback)
		{
		}
	};

	static void TriggerRequestLayerDeserialize(LayerDeserializationRequestArgs args);
	static void TriggerRequestObjectDeserialize(ObjectDeserializationRequestArgs args);
};
