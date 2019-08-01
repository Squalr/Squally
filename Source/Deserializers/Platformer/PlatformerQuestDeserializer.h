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

	void deserialize(QuestDeserializer::QuestDeserializationRequestArgs args);

	std::map<std::string, std::function<GameObject*(GameObject*, std::string, std::string, std::string)>> deserializers;
};
