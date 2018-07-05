#pragma once
#include "cocos2d.h"

#include "Engine/Maps/IObjectDeserializer.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Objects.h"
#include "Resources.h"

using namespace cocos2d;

class ObjectDeserializer : public IObjectDeserializer
{
public:
	void onDeserializationRequest(ObjectDeserializationRequestArgs* args) override;

	static const std::string KeyTypeObject;
};
