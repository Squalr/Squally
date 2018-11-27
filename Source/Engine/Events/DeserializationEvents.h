#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class DeserializationEvents
{
public:
	// Forward declarations
	struct ObjectDeserializationRequestArgs;
	struct DeserializationMapMeta;
	struct LayerDeserializationRequestArgs;

	static void TriggerLayerDeserialize(LayerDeserializationRequestArgs args);
	static void TriggerObjectDeserialize(ObjectDeserializationRequestArgs args);

	struct ObjectDeserializationRequestArgs
	{
		std::string typeName;
		ValueMap properties;
		bool handled = false;

		ObjectDeserializationRequestArgs(std::string typeName, ValueMap properties) : typeName(typeName), properties(properties)
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

	static const std::string LayerDeserializeEvent;
	static const std::string ObjectDeserializeEvent;
};
