#pragma once
#include "Engine/Events/DeserializationEvents.h"
#include "Engine/GlobalNode.h"

class ObjectLayerDeserializer : public GlobalNode
{
public:
	static void registerGlobalNode();

	void onDeserializationRequest(DeserializationEvents::LayerDeserializationRequestArgs* args);

private:
	ObjectLayerDeserializer();
	virtual ~ObjectLayerDeserializer();

	void initializeListeners() override;

	static ObjectLayerDeserializer* instance;
	static const std::string MapKeyObjectLayer;
};
