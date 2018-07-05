#pragma once
#include "cocos2d.h"

#include "Engine/Maps/IObjectDeserializer.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/PlatformerDecorObject.h"
#include "Objects/Platformer/PlatformerObjectDeserializer.h"
#include "Resources.h"

using namespace cocos2d;

class PlatformerDecorDeserializer : public IObjectDeserializer
{
public:
	void onDeserializationRequest(ObjectDeserializationRequestArgs* args) override;

	static const std::string KeyTypeDecor;
};
