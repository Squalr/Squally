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
	virtual QuestTask* deserialize(GameObject* owner, std::string questTask, std::string questTag) = 0;
	static std::string getActiveQuestTaskForLine(std::string questLine);
	static bool isQuestTaskComplete(std::string questLine, std::string questTask);
	static LocalizedString* getQuestLineName(std::string questLine);
	static LocalizedString* getQuestLineObjective(std::string questLine, std::string questTask);
	static void advanceNextQuest(QuestTask* currentQuest);
	static void markQuestLineComplete(std::string questLine);

protected:
	QuestLine();
	~QuestLine();

private:
	typedef SmartNode super;

	static const std::string QuestsSaveKey;
	static const std::string QuestLineSaveKeyComplete;
};

