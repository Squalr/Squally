#pragma once
#include "cocos2d.h"

#include "Engine/Maps/IObjectDeserializer.h"
#include "Entities/Platformer/Enemies/Castle/CastleEntities.h"

using namespace cocos2d;

class CastleEnemyDeserializer : public IObjectDeserializer
{
public:
	CastleEnemyDeserializer();
	~CastleEnemyDeserializer();

	void onDeserializationRequest(ObjectDeserializationRequestArgs* args) override;
};
