#pragma once
#include "cocos2d.h"

#include "Engine/Maps/IObjectDeserializer.h"
#include "Entities/Platformer/Npcs/Obelisk/ObeliskNpcs.h"
#include "Entities/Platformer/PlatformerEntityDeserializer.h"

using namespace cocos2d;

class ObeliskNpcDeserializer : public PlatformerEntityDeserializer
{
public:
	static void registerGlobalNode();

private:
	ObeliskNpcDeserializer();
	~ObeliskNpcDeserializer();

	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args) override;

	static ObeliskNpcDeserializer* instance;
};
