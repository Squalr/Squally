#pragma once

#include "Engine/Quests/QuestLine.h"

class GameObject;

class IntroLine : public QuestLine
{
public:
	static IntroLine* create();

	static const std::string MapKeyQuestLine;
	static const std::map<std::string, std::tuple<bool, std::function<QuestTask*(GameObject*, QuestLine*, std::string)>>> Quests;

protected:
	IntroLine();
	~IntroLine();

private:
	typedef QuestLine super;
};
