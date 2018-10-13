#pragma once
#include "cocos2d.h"

#include "Engine/Maps/IObjectDeserializer.h"
#include "Entities/Platformer/Enemies/Mech/MechEnemies.h"
#include "Entities/Platformer/PlatformerEntityDeserializer.h"

using namespace cocos2d;

class MechEnemyDeserializer : public PlatformerEntityDeserializer
{
public:
	MechEnemyDeserializer();
	~MechEnemyDeserializer();

	void onDeserializationRequest(ObjectDeserializationRequestArgs* args) override;
};
