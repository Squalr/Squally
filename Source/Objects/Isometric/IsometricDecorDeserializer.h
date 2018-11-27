#pragma once
#include "cocos2d.h"

#include "Engine/Maps/IObjectDeserializer.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Isometric/IsometricDecorObject.h"
#include "Objects/Isometric/IsometricObjectDeserializer.h"

using namespace cocos2d;

class IsometricDecorDeserializer : public IObjectDeserializer
{
public:
	static void registerGlobalNode();

private:
	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args) override;

	static IsometricDecorDeserializer* instance;
	static const std::string KeyTypeDecor;
};
