#pragma once
#include "cocos2d.h"

#include "Engine/Events/DeserializationEvents.h"
#include "Engine/GlobalNode.h"
#include "Engine/Maps/SerializableObject.h"
#include "Engine/Utils/StrUtils.h"

using namespace cocos2d;

class IObjectDeserializer : public GlobalNode
{
public:
	virtual void onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args) = 0;
};
