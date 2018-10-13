#pragma once
#include "cocos2d.h"

#include "Engine/Maps/IObjectDeserializer.h"
#include "Entities/Platformer/Enemies/Volcano/VolcanoEnemies.h"
#include "Entities/Platformer/PlatformerEntityDeserializer.h"

using namespace cocos2d;

class VolcanoEnemyDeserializer : public PlatformerEntityDeserializer
{
public:
	VolcanoEnemyDeserializer();
	~VolcanoEnemyDeserializer();

	void onDeserializationRequest(ObjectDeserializationRequestArgs* args) override;
};
