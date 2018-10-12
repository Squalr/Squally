#pragma once
#include "cocos2d.h"

#include "Engine/Maps/IObjectDeserializer.h"
#include "Entities/Platformer/Npcs/Volcano/VolcanoNpcs.h"
#include "Entities/Platformer/PlatformerEntityDeserializer.h"

using namespace cocos2d;

class VolcanoNpcDeserializer : public PlatformerEntityDeserializer
{
public:
	VolcanoNpcDeserializer();
	~VolcanoNpcDeserializer();

	void onDeserializationRequest(ObjectDeserializationRequestArgs* args) override;
};
