#pragma once
#include "cocos2d.h"

#include "Engine/Maps/IObjectDeserializer.h"
#include "Entities/Platformer/Enemies/Mech/MechEnemies.h"
#include "Entities/Platformer/PlatformerEntityDeserializer.h"

using namespace cocos2d;

class MechEnemyDeserializer : public PlatformerEntityDeserializer
{
public:
	static void registerGlobalNode();

private:
	MechEnemyDeserializer();
	~MechEnemyDeserializer();

	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args) override;

	static MechEnemyDeserializer* instance;
};
