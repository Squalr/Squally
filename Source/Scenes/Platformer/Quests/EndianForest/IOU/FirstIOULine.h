#pragma once

#include "Engine/Quests/QuestLine.h"

class GameObject;

class FirstIOULine : public QuestLine
{
public:
	static FirstIOULine* create();

	static const std::string MapKeyQuestLine;
	static const std::map<std::string, std::tuple<bool, std::function<QuestTask*(GameObject*, QuestLine*, std::string)>>> Quests;

protected:
	FirstIOULine();
	~FirstIOULine();

private:
	typedef QuestLine super;
};
