#pragma once

#include "Engine/Events/DeserializationEvents.h"
#include "Engine/GlobalNode.h"

class BackgroundDeserializer : public GlobalNode
{
public:
	static void registerGlobalNode();

private:
	typedef GlobalNode super;
	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::LayerDeserializationRequestArgs* args);

	static const std::string MapKeyBackgroundLayer;
	static BackgroundDeserializer* instance;
};
