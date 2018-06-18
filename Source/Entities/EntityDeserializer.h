#pragma once
#include "cocos2d.h"

#include "Engine/Maps/IObjectDeserializer.h"
#include "Entities/Entities.h"
#include "Resources.h"
#include "Utils/GameUtils.h"

using namespace cocos2d;

class EntityDeserializer : public IObjectDeserializer
{
public:
	EntityDeserializer();
	~EntityDeserializer();

	void onDeserializationRequest(ObjectDeserializationRequestArgs* args) override;

	static const std::string KeyTypeEntity;


};
