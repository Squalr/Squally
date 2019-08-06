#pragma once

#include "Engine/Deserializers/QuestDeserializer.h"

class PlatformerQuestDeserializer : public QuestDeserializer
{
public:
	static PlatformerQuestDeserializer* create();

	void deserializeProperties(GameObject* owner, cocos2d::ValueMap properties) override;
	std::string getPropertyDeserializerKey() override;

private:
	typedef QuestDeserializer super;

	PlatformerQuestDeserializer();
	~PlatformerQuestDeserializer();
};
