#pragma once

#include "Engine/Quests/QuestLine.h"

class GameObject;

class FerryRepairsLine : public QuestLine
{
public:
	static FerryRepairsLine* create();

	static const std::string MapKeyQuestLine;

protected:
	FerryRepairsLine();
	~FerryRepairsLine();

private:
	typedef QuestLine super;
};
