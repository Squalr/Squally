#pragma once
#include "cocos2d.h"

#include "Engine/Physics/CollisionObject.h"
#include "Engine/Maps/ILayerDeserializer.h"
#include "Engine/Maps/SerializableObject.h"
#include "Engine/Utils/StrUtils.h"

using namespace cocos2d;

class DefaultLayerDeserializer : public ILayerDeserializer
{
public:
	void onDeserializationRequest(LayerDeserializationRequestArgs* args) override;

};
