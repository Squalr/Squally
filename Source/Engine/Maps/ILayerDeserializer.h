#pragma once
#include "cocos2d.h"

#include "Engine/Maps/SerializableLayer.h"
#include "Engine/Utils/StrUtils.h"

using namespace cocos2d;

class ILayerDeserializer 
{
public:
	// Additional info used to help layer deserialization
	struct DeserializationMapMeta {
		Size mapSize;
		bool isIsometric;

		DeserializationMapMeta(Size mapSize, bool isIsometric) : mapSize(mapSize), isIsometric(isIsometric)
		{
		}
	};

	struct LayerDeserializationRequestArgs
	{
		TMXObjectGroup* objectGroup;
		std::function<void(SerializableLayer*, int layerIndex)> callback;
		std::vector<IObjectDeserializer*>* objectDeserializers;
		DeserializationMapMeta mapMeta;
		bool handled = false;

		LayerDeserializationRequestArgs(
			TMXObjectGroup* objectGroup, 
			std::vector<IObjectDeserializer*>* objectDeserializers,
			DeserializationMapMeta mapMeta,
			std::function<void(SerializableLayer*, int)> callback):
			objectGroup(objectGroup), objectDeserializers(objectDeserializers), mapMeta(mapMeta), callback(callback)
		{
		}
	};

	virtual void onDeserializationRequest(LayerDeserializationRequestArgs* args) = 0;
};
