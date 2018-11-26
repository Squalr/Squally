#pragma once
#include "cocos2d.h"

#include "Engine/Maps/IObjectDeserializer.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Isometric/IsometricEntities.h"

using namespace cocos2d;

class IsometricEntityDeserializer : public IObjectDeserializer
{
public:
	IsometricEntityDeserializer();
	~IsometricEntityDeserializer();

	void onDeserializationRequest(ObjectDeserializationRequestArgs* args) override;

	static const std::string KeyTypeIsometricEntity;

};
