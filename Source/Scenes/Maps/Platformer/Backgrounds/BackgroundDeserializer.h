#pragma once
#include "cocos2d.h"

#include "Engine/Events/DeserializationEvents.h"
#include "Engine/GlobalNode.h"
#include "Scenes/Maps/Platformer/Backgrounds/Background.h"

using namespace cocos2d;

class BackgroundDeserializer : public GlobalNode
{
public:
	static void registerGlobalNode();

private:
	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::LayerDeserializationRequestArgs* args);

	static const std::string MapKeyBackgroundLayer;
	static BackgroundDeserializer* instance;
};
