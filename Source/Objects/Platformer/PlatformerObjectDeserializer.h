#pragma once
#include "cocos2d.h"

#include "Engine/Events/DeserializationEvents.h"
#include "Engine/GlobalNode.h"
#include "Objects/Platformer/PlatformerObjects.h"

using namespace cocos2d;

class PlatformerObjectDeserializer : public GlobalNode
{
public:
	static void registerGlobalNode();

private:
	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args);

	static PlatformerObjectDeserializer* instance;
	static const std::string KeyTypeObject;
};
