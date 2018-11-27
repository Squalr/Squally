#pragma once
#include "cocos2d.h"

#include "Engine/Maps/SerializableLayer.h"
#include "Engine/Maps/SerializableObject.h"

using namespace cocos2d;

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
	static void TriggerLayerDeserialize(LayerDeserializationArgs args);
	static void TriggerObjectDeserialize(ObjectDeserializationArgs args);

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
		Size mapSize;
		bool isIsometric;

		DeserializationMapMeta(Size mapSize, bool isIsometric) : mapSize(mapSize), isIsometric(isIsometric)
		{
		}
	};

	struct LayerDeserializationRequestArgs
	{
		TMXObjectGroup* objectGroup;
		DeserializationMapMeta mapMeta;
		bool handled = false;

		LayerDeserializationRequestArgs(
			TMXObjectGroup* objectGroup,
			DeserializationMapMeta mapMeta) :
			objectGroup(objectGroup), mapMeta(mapMeta)
		{
		}
	};

	struct ObjectDeserializationRequestArgs
	{
		std::string typeName;
		ValueMap properties;
		bool handled = false;

		ObjectDeserializationRequestArgs(std::string typeName, ValueMap properties) : typeName(typeName), properties(properties)
		{
		}
	};

	static const std::string RequestLayerDeserializeEvent;
	static const std::string RequestObjectDeserializeEvent;
	static const std::string LayerDeserializeEvent;
	static const std::string ObjectDeserializeEvent;
};
