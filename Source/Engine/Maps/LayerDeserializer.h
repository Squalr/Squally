#pragma once
#include "cocos2d.h"

#include "Engine/Events/DeserializationEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Maps/ILayerDeserializer.h"
#include "Engine/Maps/SerializableObject.h"
#include "Engine/Utils/StrUtils.h"

using namespace cocos2d;

class LayerDeserializer : public ILayerDeserializer
{
public:
	static void registerGlobalNode();

	void onDeserializationRequest(DeserializationEvents::LayerDeserializationRequestArgs* args) override;

private:
	LayerDeserializer();
	~LayerDeserializer();

	void initializeListeners() override;

	static LayerDeserializer* instance;
};
