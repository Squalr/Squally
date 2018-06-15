#pragma once
#include "cocos2d.h"

#include "Engine/Maps/IDeserializer.h"
#include "Objects/DecorObject.h"
#include "Resources.h"
#include "Utils/GameUtils.h"

#include "ObjectDeserializer.h"

using namespace cocos2d;

class DecorDeserializer : public IDeserializer
{
public:
	void onDeserializationRequest(DeserializationRequestArgs* args) override;

	static const std::string KeyTypeDecor;
};
