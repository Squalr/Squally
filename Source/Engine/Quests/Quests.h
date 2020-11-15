#pragma once

#include "cocos/base/ccTypes.h"

#include "Engine/SmartNode.h"

class Quests
{
public:
	static cocos2d::ValueMap getQuestData();
	static void saveQuestLineProgress(std::string questLine, std::string currentQuest);
	static std::string getCurrentQuestTaskForLine(std::string questLine);
	static std::set<std::string> getStartedQuestLines();
	static std::set<std::string> getActiveQuestLines();
	static std::set<std::string> getCompletedQuestLines();

protected:
	Quests();
	virtual ~Quests();

private:
	typedef SmartNode super;

	static const std::string QuestsSaveKey;
};
