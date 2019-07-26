#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Value;
	typedef std::map<std::string, Value> ValueMap;
}

class GameObject;

class QuestDeserializer : public SmartNode
{
public:
	struct QuestDeserializationRequestArgs
	{
		GameObject* targetObject;
		std::string quest;
		std::string questLine;
		std::string questTag;

		QuestDeserializationRequestArgs(GameObject* targetObject,
			std::string questLine,
			std::string quest,
			std::string questTag):
			targetObject(targetObject), questLine(questLine), quest(quest), questTag(questTag)
		{
		}
	};

	virtual void deserialize(QuestDeserializer::QuestDeserializationRequestArgs args) = 0;

protected:
	QuestDeserializer();
	~QuestDeserializer();

private:
	typedef SmartNode super;
};
