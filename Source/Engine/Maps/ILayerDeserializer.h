#pragma once
#include "cocos2d.h"

#include "Engine/Maps/SerializableLayer.h"
#include "Engine/Utils/StrUtils.h"

using namespace cocos2d;

class ILayerDeserializer 
{
public:
	struct LayerDeserializationRequestArgs
	{
		TMXObjectGroup* objectGroup;
		std::function<void(SerializableLayer*, int layerIndex)> callback;
		std::vector<IObjectDeserializer*>* objectDeserializers;
		bool handled = false;

		LayerDeserializationRequestArgs(TMXObjectGroup* objectGroup, std::vector<IObjectDeserializer*>* objectDeserializers, std::function<void(SerializableLayer*, int)> callback):
			objectGroup(objectGroup), objectDeserializers(objectDeserializers), callback(callback)
		{
		}
	};

	virtual void onDeserializationRequest(LayerDeserializationRequestArgs* args) = 0;
};
