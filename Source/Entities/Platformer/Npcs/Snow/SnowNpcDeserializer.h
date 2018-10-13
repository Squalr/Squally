#pragma once
#include "cocos2d.h"

#include "Engine/Maps/IObjectDeserializer.h"
#include "Entities/Platformer/Npcs/Snow/SnowNpcs.h"
#include "Entities/Platformer/PlatformerEntityDeserializer.h"

using namespace cocos2d;

class SnowNpcDeserializer : public PlatformerEntityDeserializer
{
public:
	SnowNpcDeserializer();
	~SnowNpcDeserializer();

	void onDeserializationRequest(ObjectDeserializationRequestArgs* args) override;
};
