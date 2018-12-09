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
	// Forward declarations
	struct LayerDeserializationArgs;
	struct ObjectDeserializationArgs;
	struct DeserializationMapMeta;
	struct LayerDeserializationRequestArgs;
	struct ObjectDeserializationRequestArgs;

	static void TriggerRequestLayerDeserialize(LayerDeserializationRequestArgs args);
	static void TriggerRequestObjectDeserialize(ObjectDeserializationRequestArgs args);

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
		cocos2d::Size mapSize;
		bool isIsometric;

		DeserializationMapMeta(cocos2d::Size mapSize, bool isIsometric) : mapSize(mapSize), isIsometric(isIsometric)
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

	static const std::string RequestLayerDeserializeEvent;
	static const std::string RequestObjectDeserializeEvent;
};
