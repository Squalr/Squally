#pragma once
#include "cocos2d.h"

#include "Engine/GlobalNode.h"
#include "Engine/Events/DeserializationEvents.h"
#include "Entities/Isometric/IsometricEntities.h"

using namespace cocos2d;

class IsometricEntityDeserializer : public GlobalNode
{
public:
	static void registerGlobalNode();

private:
	IsometricEntityDeserializer();
	~IsometricEntityDeserializer();

	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args);

	static IsometricEntityDeserializer* instance;
	static const std::string KeyTypeIsometricEntity;
};
