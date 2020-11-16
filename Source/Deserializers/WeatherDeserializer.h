#pragma once

#include "Engine/Deserializers/LayerDeserializer.h"

class WeatherDeserializer : public LayerDeserializer
{
public:
	static WeatherDeserializer* create();

protected:
	WeatherDeserializer();
	virtual ~WeatherDeserializer();

private:
	typedef LayerDeserializer super;

	void deserialize(LayerDeserializer::LayerDeserializationRequestArgs* args);

	static const std::string MapKeyWeatherLayer;
	static const std::string MapKeyWeather;
};
