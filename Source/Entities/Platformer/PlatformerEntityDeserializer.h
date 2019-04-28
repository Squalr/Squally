#pragma once
#include "Engine/GlobalNode.h"
#include "Engine/Events/DeserializationEvents.h"

class PlatformerEntityDeserializer : public GlobalNode
{
public:
	static void registerGlobalNode();
	static PlatformerEntityDeserializer* getInstance();

	void onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args);

	static const std::string KeyTypeEntity;

protected:
	PlatformerEntityDeserializer();
	virtual ~PlatformerEntityDeserializer();

	void initializeListeners() override;

	static PlatformerEntityDeserializer* instance;

private:
	typedef GlobalNode super;
};
