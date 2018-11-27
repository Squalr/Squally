#pragma once
#include "cocos2d.h"

#include "Engine/Maps/IObjectDeserializer.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Isometric/IsometricObjects.h"

using namespace cocos2d;

class IsometricObjectDeserializer : public IObjectDeserializer
{
public:
	static void registerGlobalNode();

private:
	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args) override;

	static IsometricObjectDeserializer* instance;
	static const std::string KeyTypeIsometricObject;
};
