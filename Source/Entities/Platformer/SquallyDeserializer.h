#pragma once
#include "cocos2d.h"

#include "Engine/Events/DeserializationEvents.h"
#include "Entities/Platformer/PlatformerEntityDeserializer.h"
#include "Entities/Platformer/Squally/Squally.h"

using namespace cocos2d;

class SquallyDeserializer : public PlatformerEntityDeserializer
{
public:
	static void registerGlobalNode();

private:
	SquallyDeserializer();
	~SquallyDeserializer();

	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args);

	static SquallyDeserializer* instance;
};
