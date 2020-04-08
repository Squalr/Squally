#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Value;
	typedef std::map<std::string, Value> ValueMap;
}

class GameObject;
class LocalizedString;
class QuestTask;

class QuestLine : public SmartNode
{
public:
	struct QuestData
	{
		std::string questTask;
		bool isSkippable;
		std::function<QuestTask*(GameObject*, QuestLine*)> deserializer;

		QuestData(std::string questTask, bool isSkippable, std::function<QuestTask*(GameObject*, QuestLine*)> deserializer)
			: questTask(questTask), isSkippable(isSkippable), deserializer(deserializer) { }
	};

	struct QuestMeta
	{
		std::string questTask;
		bool isActive;
		bool isSkippable;
		bool isComplete;

		QuestMeta(std::string questTask, bool isActive, bool isSkippable, bool isComplete) : questTask(questTask), isActive(isActive), isSkippable(isSkippable), isComplete(isComplete) { }
	};

	QuestTask* deserialize(GameObject* owner, std::string questTask);
	const std::vector<QuestMeta> getQuests();
	std::string getQuestLine();
	void advanceNextQuest(QuestTask* currentQuest);
	void waiveQuestPrereq();
	LocalizedString* getQuestLineName();
	LocalizedString* getQuestLineObjective(std::string questTask);
	bool isComplete();
	virtual QuestLine* clone() = 0;

protected:
	QuestLine(std::string questLine, const std::vector<QuestData> quests, QuestLine* prereq = nullptr);
	virtual ~QuestLine();

private:
	typedef SmartNode super;

	std::string questLine;
	std::vector<QuestData> quests;
	QuestLine* prereq;

	static const std::string QuestLineSaveKeyComplete;
};
