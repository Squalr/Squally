#pragma once

#include "Engine/Maps/SerializableLayer.h"

class PhysicsLayer : public SerializableLayer
{
public:
	static PhysicsLayer* create(cocos2d::ValueMap& properties, std::string name);

	static const std::string MapKeyWeatherLayerPhysicsLayer;

protected:
	void onEnter() override;

private:
	typedef SerializableLayer super;
	PhysicsLayer(cocos2d::ValueMap& properties, std::string name);
	~PhysicsLayer();

	float gravity;

	static const std::string MapKeyGravity;
	static const float DefaultGravity;
	static const float MinimumGravity;
	static const float MaximumGravity;
};
