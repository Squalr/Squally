#pragma once

#include "Engine/Quests/QuestLine.h"

class RescueGuanoLine : public QuestLine
{
public:
	static RescueGuanoLine* create();

	static const std::string MapKeyQuestLine;

protected:
	RescueGuanoLine();
	~RescueGuanoLine();

private:
	typedef QuestLine super;
};
