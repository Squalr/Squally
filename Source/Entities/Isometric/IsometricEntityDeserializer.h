#pragma once
#include "cocos2d.h"

#include "Engine/Events/DeserializationEvents.h"
#include "Engine/Maps/IObjectDeserializer.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Isometric/IsometricEntities.h"

using namespace cocos2d;

class IsometricEntityDeserializer : public IObjectDeserializer
{
public:
	static void registerGlobalNode();

private:
	IsometricEntityDeserializer();
	~IsometricEntityDeserializer();

	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args) override;

	static IsometricEntityDeserializer* instance;
	static const std::string KeyTypeIsometricEntity;
};
