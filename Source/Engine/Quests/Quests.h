#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Value;
	typedef std::map<std::string, Value> ValueMap;
}

class LocalizedString;
class QuestTask;

class Quests
{
public:
	static cocos2d::ValueMap getQuestData();
	static std::set<std::string> getStartedQuestLines();
	static std::set<std::string> getActiveQuestLines();
	static std::set<std::string> getCompletedQuestLines();

protected:
	Quests();
	~Quests();

private:
	typedef SmartNode super;

	static const std::string QuestsSaveKey;
};
