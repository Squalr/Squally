#pragma once

#include "Engine/Deserializers/QuestDeserializer.h"

class PlatformerQuestDeserializer : public QuestDeserializer
{
public:
	static PlatformerQuestDeserializer* create();

	static const std::string MapKeyTypeObject;

private:
	typedef QuestDeserializer super;

	PlatformerQuestDeserializer();
	~PlatformerQuestDeserializer();
};
