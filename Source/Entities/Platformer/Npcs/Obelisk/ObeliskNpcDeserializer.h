#pragma once
#include "cocos2d.h"

#include "Engine/Maps/IObjectDeserializer.h"
#include "Entities/Platformer/Npcs/Obelisk/ObeliskNpcs.h"
#include "Entities/Platformer/PlatformerEntityDeserializer.h"

using namespace cocos2d;

class ObeliskNpcDeserializer : public PlatformerEntityDeserializer
{
public:
	ObeliskNpcDeserializer();
	~ObeliskNpcDeserializer();

	void onDeserializationRequest(ObjectDeserializationRequestArgs* args) override;
};
