#pragma once
#include "cocos2d.h"

#include "Engine/Maps/IObjectDeserializer.h"
#include "Entities/Platformer/Npcs/Forest/ForestNpcs.h"
#include "Entities/Platformer/PlatformerEntityDeserializer.h"

using namespace cocos2d;

class ForestNpcDeserializer : public PlatformerEntityDeserializer
{
public:
	static void registerGlobalNode();

private:
	ForestNpcDeserializer();
	~ForestNpcDeserializer();

	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args) override;

	static ForestNpcDeserializer* instance;
};
