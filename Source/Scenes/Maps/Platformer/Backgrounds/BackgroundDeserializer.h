#pragma once
#include "cocos2d.h"

#include "Engine/Maps/ILayerDeserializer.h"
#include "Scenes/Maps/Platformer/Backgrounds/JungleBackground.h"
#include "Scenes/Maps/Platformer/Backgrounds/MountainBackground.h"
#include "Scenes/Maps/Platformer/Backgrounds/OceanBackground.h"
#include "Scenes/Maps/Platformer/Backgrounds/SnowBackground.h"

using namespace cocos2d;

class BackgroundDeserializer : public ILayerDeserializer
{
public:
	void onDeserializationRequest(LayerDeserializationRequestArgs* args) override;

	static const std::string KeyBackground;
};
