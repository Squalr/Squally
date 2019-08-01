#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Value;
	typedef std::map<std::string, Value> ValueMap;
}

class LocalizedString;
class QuestTask;

class QuestLine
{
public:
	static cocos2d::ValueMap getQuestData();
	static std::set<std::string> getQuestLines();
	static std::set<std::string> getActiveQuestLines();
	static std::string getActiveQuestTaskForLine(std::string questLine);
	static bool isQuestTaskComplete(std::string questLine, std::string questTask);
	static LocalizedString* getQuestLineName(std::string questLine);
	static LocalizedString* getQuestLineObjective(std::string questLine, std::string questTask);
	static void advanceNextQuest(QuestTask* currentQuest);
	static void markQuestLineComplete(std::string questLine);

private:
	static const std::string QuestsSaveKey;
	static const std::string QuestLineSaveKeyComplete;
};

