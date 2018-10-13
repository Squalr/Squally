#pragma once
#include "cocos2d.h"

#include "Engine/Maps/IObjectDeserializer.h"
#include "Entities/Platformer/Enemies/Obelisk/ObeliskEnemies.h"
#include "Entities/Platformer/PlatformerEntityDeserializer.h"

using namespace cocos2d;

class ObeliskEnemyDeserializer : public PlatformerEntityDeserializer
{
public:
	ObeliskEnemyDeserializer();
	~ObeliskEnemyDeserializer();

	void onDeserializationRequest(ObjectDeserializationRequestArgs* args) override;
};
