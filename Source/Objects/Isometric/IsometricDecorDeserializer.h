#pragma once
#include "cocos2d.h"

#include "Engine/Events/DeserializationEvents.h"
#include "Engine/GlobalNode.h"
#include "Objects/Isometric/IsometricDecorObject.h"
#include "Objects/Isometric/IsometricObjectDeserializer.h"

using namespace cocos2d;

class IsometricDecorDeserializer : public GlobalNode
{
public:
	static void registerGlobalNode();

private:
	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args);

	static IsometricDecorDeserializer* instance;
	static const std::string KeyTypeDecor;
};
