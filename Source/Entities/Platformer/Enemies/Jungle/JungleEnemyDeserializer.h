#pragma once
#include "cocos2d.h"

#include "Engine/Maps/IObjectDeserializer.h"
#include "Entities/Platformer/Enemies/Jungle/JungleEnemies.h"
#include "Entities/Platformer/PlatformerEntityDeserializer.h"

using namespace cocos2d;

class JungleEnemyDeserializer : public PlatformerEntityDeserializer
{
public:
	static void registerGlobalNode();

private:
	JungleEnemyDeserializer();
	~JungleEnemyDeserializer();

	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args) override;

	static JungleEnemyDeserializer* instance;
};
