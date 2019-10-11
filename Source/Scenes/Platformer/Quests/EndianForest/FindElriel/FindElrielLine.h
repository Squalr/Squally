#pragma once

#include "Engine/Quests/QuestLine.h"

class FindElrielLine : public QuestLine
{
public:
	static FindElrielLine* create();

	static const std::string MapKeyQuestLine;

protected:
	FindElrielLine();
	~FindElrielLine();

private:
	typedef QuestLine super;
};
