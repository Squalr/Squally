#pragma once
#include "cocos2d.h"

#include "Engine/Maps/IObjectDeserializer.h"
#include "Entities/Platformer/Npcs/Forest/ForestNpcs.h"
#include "Entities/Platformer/PlatformerEntityDeserializer.h"

using namespace cocos2d;

class ForestNpcDeserializer : public PlatformerEntityDeserializer
{
public:
	ForestNpcDeserializer();
	~ForestNpcDeserializer();

	void onDeserializationRequest(ObjectDeserializationRequestArgs* args) override;
};
