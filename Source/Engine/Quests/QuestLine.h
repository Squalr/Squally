#pragma once

#include "cocos/base/ccTypes.h"

#include "Engine/SmartNode.h"

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
	bool isCompleteUpTo(std::string questTask);
	virtual QuestLine* clone() = 0;

protected:
	QuestLine(std::string questLine, const std::vector<QuestData> quests, QuestLine* prereq = nullptr, std::string prereqTask = "");
	virtual ~QuestLine();

private:
	typedef SmartNode super;

	std::string questLine;
	std::vector<QuestData> quests;
	QuestLine* prereq;
	std::string prereqTask = "";

	static const std::string QuestLineSaveKeyComplete;
};
