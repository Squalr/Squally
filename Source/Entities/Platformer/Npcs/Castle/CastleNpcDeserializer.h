#pragma once
#include "cocos2d.h"

#include "Engine/Maps/IObjectDeserializer.h"
#include "Entities/Platformer/Npcs/Castle/CastleNpcs.h"
#include "Entities/Platformer/PlatformerEntityDeserializer.h"

using namespace cocos2d;

class CastleNpcDeserializer : public PlatformerEntityDeserializer
{
public:
	CastleNpcDeserializer();
	~CastleNpcDeserializer();

	void onDeserializationRequest(ObjectDeserializationRequestArgs* args) override;
};
