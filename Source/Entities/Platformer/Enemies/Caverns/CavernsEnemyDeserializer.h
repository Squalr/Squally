#pragma once
#include "cocos2d.h"

#include "Engine/Maps/IObjectDeserializer.h"
#include "Entities/Platformer/Enemies/Caverns/CavernsEnemies.h"
#include "Entities/Platformer/PlatformerEntityDeserializer.h"

using namespace cocos2d;

class CavernsEnemyDeserializer : public PlatformerEntityDeserializer
{
public:
	static void registerGlobalNode();

private:
	CavernsEnemyDeserializer();
	~CavernsEnemyDeserializer();

	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args) override;

	static CavernsEnemyDeserializer* instance;
};
