#pragma once

#include "Engine/Deserializers/LayerDeserializer.h"
#include "Engine/GlobalNode.h"

class WeatherDeserializer : public LayerDeserializer
{
public:
	static WeatherDeserializer* create();

private:
	typedef LayerDeserializer super;
	WeatherDeserializer();
	~WeatherDeserializer();

	void deserialize(LayerDeserializer::LayerDeserializationRequestArgs* args);

	static const std::string MapKeyWeatherLayer;
	static const std::string MapKeyWeather;
};
