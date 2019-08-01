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
		bool isActive;
		bool isSkippable;
		bool isComplete;

		QuestData(std::string questTask, bool isActive, bool isSkippable, bool isComplete) : questTask(questTask), isActive(isActive), isSkippable(isSkippable), isComplete(isComplete) { }
	};

	QuestTask* deserialize(GameObject* owner, std::string questTask, std::string questTag);
	const std::vector<QuestData> getQuests();
	std::string getQuestLine();
	std::string getActiveQuestTaskName();
	bool isQuestTaskComplete(std::string questTaskName);
	void advanceNextQuest(QuestTask* currentQuest);
	void markQuestLineComplete();
	LocalizedString* getQuestLineName();
	LocalizedString* getQuestLineObjective(std::string questTask);

protected:
	QuestLine(std::string questLine, const std::map<std::string, std::tuple<bool, std::function<QuestTask*(GameObject*, QuestLine*, std::string)>>> quests);
	~QuestLine();

private:
	typedef SmartNode super;

	std::string questLine;
	std::map<std::string, std::tuple<bool, std::function<QuestTask*(GameObject*, QuestLine*, std::string)>>> quests;

	static const std::string QuestLineSaveKeyComplete;
};

