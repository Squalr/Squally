#pragma once
#include "cocos2d.h"

#include "Engine/Maps/IDeserializer.h"
#include "Objects/Objects.h"
#include "Resources.h"
#include "Utils/GameUtils.h"

using namespace cocos2d;

class ObjectDeserializer : public IDeserializer
{
public:
	void onDeserializationRequest(DeserializationRequestArgs* args) override;

	static const std::string KeyTypeObject;
};
