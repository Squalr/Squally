#pragma once

#include "Engine/Events/DeserializationEvents.h"
#include "Engine/GlobalNode.h"

class MusicDeserializer : public GlobalNode
{
public:
	static void registerGlobalNode();

private:
	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::LayerDeserializationRequestArgs* args);

	static const std::string KeyMusicProperty;
	static MusicDeserializer* instance;
};
