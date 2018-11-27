#pragma once
#include "cocos2d.h"

#include "Engine/Events/DeserializationEvents.h"
#include "Engine/GlobalNode.h"
#include "Scenes/Maps/Platformer/Backgrounds/JungleBackground.h"
#include "Scenes/Maps/Platformer/Backgrounds/MountainBackground.h"
#include "Scenes/Maps/Platformer/Backgrounds/ObeliskBackground.h"
#include "Scenes/Maps/Platformer/Backgrounds/OceanBackground.h"
#include "Scenes/Maps/Platformer/Backgrounds/SnowBackground.h"

using namespace cocos2d;

class BackgroundDeserializer : public GlobalNode
{
public:
	static void registerGlobalNode();

private:
	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::LayerDeserializationRequestArgs* args);

	static const std::string KeyBackground;
	static BackgroundDeserializer* instance;
};
