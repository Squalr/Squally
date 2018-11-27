#pragma once
#include "cocos2d.h"

#include "Engine/Events/DeserializationEvents.h"
#include "Engine/GlobalNode.h"
#include "Objects/Platformer/PlatformerDecorObject.h"
#include "Objects/Platformer/PlatformerObjectDeserializer.h"

using namespace cocos2d;

class PlatformerDecorDeserializer : public GlobalNode
{
public:
	static void registerGlobalNode();

private:
	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args);

	static PlatformerDecorDeserializer* instance;
	static const std::string KeyTypeDecor;
};
