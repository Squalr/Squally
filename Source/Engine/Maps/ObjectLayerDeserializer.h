#pragma once
#include "cocos2d.h"

#include "Engine/Events/DeserializationEvents.h"
#include "Engine/GlobalNode.h"
#include "Engine/Maps/SerializableObject.h"

using namespace cocos2d;

class ObjectLayerDeserializer : public GlobalNode
{
public:
	static void registerGlobalNode();

	void onDeserializationRequest(DeserializationEvents::LayerDeserializationRequestArgs* args);

private:
	ObjectLayerDeserializer();
	~ObjectLayerDeserializer();

	void initializeListeners() override;

	static ObjectLayerDeserializer* instance;
	static const std::string MapKeyObjectLayer;
};
