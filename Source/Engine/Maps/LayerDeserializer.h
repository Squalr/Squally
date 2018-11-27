#pragma once
#include "cocos2d.h"

#include "Engine/Events/DeserializationEvents.h"
#include "Engine/GlobalNode.h"
#include "Engine/Maps/SerializableObject.h"

using namespace cocos2d;

class LayerDeserializer : public GlobalNode
{
public:
	static void registerGlobalNode();

	void onDeserializationRequest(DeserializationEvents::LayerDeserializationRequestArgs* args);

private:
	LayerDeserializer();
	~LayerDeserializer();

	void initializeListeners() override;

	static LayerDeserializer* instance;
};
