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
		GameObject* owner;
		std::string questLine;
		std::string questTask;
		std::string questTag;

		QuestDeserializationRequestArgs(GameObject* owner,
			std::string questLine,
			std::string questTask,
			std::string questTag):
			owner(owner), questLine(questLine), questTask(questTask), questTag(questTag)
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
