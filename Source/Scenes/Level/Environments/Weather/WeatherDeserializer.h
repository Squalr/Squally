#pragma once
#include "cocos2d.h"

#include "Engine/Maps/ILayerDeserializer.h"
#include "Scenes/Level/Environments/Weather/Fireflies.h"
#include "Scenes/Level/Environments/Weather/Rain.h"
#include "Scenes/Level/Environments/Weather/Snow.h"

using namespace cocos2d;

class WeatherDeserializer : public ILayerDeserializer
{
public:
	void onDeserializationRequest(LayerDeserializationRequestArgs* args) override;

	static const std::string KeyWeather;
};
