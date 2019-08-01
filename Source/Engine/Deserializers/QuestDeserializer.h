#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Value;
	typedef std::map<std::string, Value> ValueMap;
}

class GameObject;
class QuestLine;
class QuestTask;

class QuestDeserializer : public SmartNode
{
public:
	struct QuestLineDeserializationRequestArgs
	{
		std::string questLine;

		QuestLineDeserializationRequestArgs(std::string questLine) : questLine(questLine)
		{
		}
	};
	
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

	QuestLine* deserialize(QuestDeserializer::QuestLineDeserializationRequestArgs args);
	QuestTask* deserialize(QuestDeserializer::QuestDeserializationRequestArgs args);

protected:
	QuestDeserializer();
	~QuestDeserializer();

	std::map<std::string, std::function<QuestLine*()>> lineDeserializers;

private:
	typedef SmartNode super;
};
