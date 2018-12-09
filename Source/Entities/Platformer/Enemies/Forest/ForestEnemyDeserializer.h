#pragma once

#include "Engine/Events/DeserializationEvents.h"
#include "Entities/Platformer/PlatformerEntityDeserializer.h"

class ForestEnemyDeserializer : public PlatformerEntityDeserializer
{
public:
	static void registerGlobalNode();

private:
	ForestEnemyDeserializer();
	virtual ~ForestEnemyDeserializer();

	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args);

	static ForestEnemyDeserializer* instance;
};
