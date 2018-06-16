#pragma once
#include "cocos2d.h"

#include "Engine/Maps/ILayerDeserializer.h"
#include "Scenes/Level/Environments/Backgrounds/JungleBackground.h"
#include "Scenes/Level/Environments/Backgrounds/MountainBackground.h"
#include "Scenes/Level/Environments/Backgrounds/OceanBackground.h"
#include "Scenes/Level/Environments/Backgrounds/SnowBackground.h"

using namespace cocos2d;

class BackgroundDeserializer : public ILayerDeserializer
{
public:
	void onDeserializationRequest(LayerDeserializationRequestArgs* args) override;

	static const std::string KeyBackground;
};
