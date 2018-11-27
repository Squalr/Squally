#pragma once
#include "cocos2d.h"

#include "Engine/Maps/IObjectDeserializer.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/PlatformerDecorObject.h"
#include "Objects/Platformer/PlatformerObjectDeserializer.h"

using namespace cocos2d;

class PlatformerDecorDeserializer : public IObjectDeserializer
{
public:
	static void registerGlobalNode();

private:
	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args) override;

	static PlatformerDecorDeserializer* instance;
	static const std::string KeyTypeDecor;
};
