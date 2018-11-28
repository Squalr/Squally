#pragma once
#include "cocos2d.h"

#include "Engine/Events/DeserializationEvents.h"
#include "Engine/GlobalNode.h"
#include "Scenes/Maps/Platformer/Weather/Fireflies.h"
#include "Scenes/Maps/Platformer/Weather/Rain.h"
#include "Scenes/Maps/Platformer/Weather/Snow.h"

using namespace cocos2d;

class WeatherDeserializer : public GlobalNode
{
public:
	static void registerGlobalNode();

private:
	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::LayerDeserializationRequestArgs* args);

	static const std::string MapKeyWeatherLayer;
	static WeatherDeserializer* instance;
};
