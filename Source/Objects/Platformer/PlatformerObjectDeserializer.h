#pragma once
#include "cocos2d.h"

#include "Engine/Maps/IObjectDeserializer.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/PlatformerObjects.h"

using namespace cocos2d;

class PlatformerObjectDeserializer : public IObjectDeserializer
{
public:
	static void registerGlobalNode();

private:
	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args) override;

	static PlatformerObjectDeserializer* instance;
	static const std::string KeyTypeObject;
};
