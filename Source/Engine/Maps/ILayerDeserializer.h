#pragma once
#include "cocos2d.h"

#include "Engine/Events/DeserializationEvents.h"
#include "Engine/GlobalNode.h"
#include "Engine/Maps/SerializableLayer.h"
#include "Engine/Utils/StrUtils.h"

using namespace cocos2d;

class ILayerDeserializer : public GlobalNode
{
public:
	virtual void onDeserializationRequest(DeserializationEvents::LayerDeserializationRequestArgs* args) = 0;
};
