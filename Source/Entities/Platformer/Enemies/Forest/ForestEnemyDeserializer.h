#pragma once
#include "cocos2d.h"

#include "Engine/Maps/IObjectDeserializer.h"
#include "Entities/Platformer/Enemies/Castle/CastleEntities.h"

using namespace cocos2d;

class ForestEnemyDeserializer : public IObjectDeserializer
{
public:
	ForestEnemyDeserializer();
	~ForestEnemyDeserializer();

	void onDeserializationRequest(ObjectDeserializationRequestArgs* args) override;
};
