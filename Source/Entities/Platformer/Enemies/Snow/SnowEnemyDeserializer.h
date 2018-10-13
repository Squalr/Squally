#pragma once
#include "cocos2d.h"

#include "Engine/Maps/IObjectDeserializer.h"
#include "Entities/Platformer/Enemies/Snow/SnowEnemies.h"
#include "Entities/Platformer/PlatformerEntityDeserializer.h"

using namespace cocos2d;

class SnowEnemyDeserializer : public PlatformerEntityDeserializer
{
public:
	SnowEnemyDeserializer();
	~SnowEnemyDeserializer();

	void onDeserializationRequest(ObjectDeserializationRequestArgs* args) override;
};
