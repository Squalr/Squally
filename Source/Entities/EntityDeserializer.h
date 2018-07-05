#pragma once
#include "cocos2d.h"

#include "Engine/Maps/IObjectDeserializer.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Entities.h"
#include "Resources.h"

using namespace cocos2d;

class EntityDeserializer : public IObjectDeserializer
{
public:
	EntityDeserializer();
	~EntityDeserializer();

	void onDeserializationRequest(ObjectDeserializationRequestArgs* args) override;

	static const std::string KeyTypeEntity;


};
