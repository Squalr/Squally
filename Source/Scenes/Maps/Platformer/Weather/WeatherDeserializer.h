#pragma once
#include "cocos2d.h"

#include "Engine/Maps/ILayerDeserializer.h"
#include "Scenes/Maps/Platformer/Weather/Fireflies.h"
#include "Scenes/Maps/Platformer/Weather/Rain.h"
#include "Scenes/Maps/Platformer/Weather/Snow.h"

using namespace cocos2d;

class WeatherDeserializer : public ILayerDeserializer
{
public:
	static void registerGlobalNode();

private:
	void initializeListeners() override;
	void onDeserializationRequest(LayerDeserializationRequestArgs* args) override;

	static const std::string KeyWeather;
};
