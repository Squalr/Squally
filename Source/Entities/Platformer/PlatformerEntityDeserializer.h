#pragma once
#include "Engine/GlobalNode.h"
#include "Engine/Events/DeserializationEvents.h"

class PlatformerEntityDeserializer : public GlobalNode
{
public:
	static void registerGlobalNode();

protected:
	PlatformerEntityDeserializer();
	virtual ~PlatformerEntityDeserializer();

	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args);

	static PlatformerEntityDeserializer* instance;

	static const std::string KeyTypeEntity;
};
