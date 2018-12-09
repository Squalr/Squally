#pragma once
#include "Engine/Events/DeserializationEvents.h"
#include "Engine/GlobalNode.h"

class CollisionDeserializer : public GlobalNode
{
public:
	static void registerGlobalNode();

private:
	CollisionDeserializer();
	virtual ~CollisionDeserializer();

	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args);

	static CollisionDeserializer* instance;
};
