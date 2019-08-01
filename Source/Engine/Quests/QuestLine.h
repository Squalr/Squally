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
	QuestTask* deserialize(GameObject* owner, std::string questTask, std::string questTag);
	const std::map<std::string, bool> getQuests();
	std::string getActiveQuestTaskName();
	bool isQuestTaskComplete(std::string questTaskName);
	LocalizedString* getQuestLineName();
	LocalizedString* getQuestLineObjective(std::string questTask);
	void advanceNextQuest(QuestTask* currentQuest);
	void markQuestLineComplete();

protected:
	QuestLine(std::string questLine, const std::map<std::string, std::tuple<bool, std::function<QuestTask*(GameObject*, QuestLine*, std::string)>>> quests);
	~QuestLine();

private:
	typedef SmartNode super;

	std::string questLine;
	std::map<std::string, std::tuple<bool, std::function<QuestTask*(GameObject*, QuestLine*, std::string)>>> quests;

	static const std::string QuestsSaveKey;
	static const std::string QuestLineSaveKeyComplete;
};

