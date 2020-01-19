#pragma once

#include "Engine/Quests/QuestLine.h"

class FindElrielLine : public QuestLine
{
public:
	static FindElrielLine* create();

	QuestLine* clone() override;

	static const std::string MapKeyQuestLine;

protected:
	FindElrielLine();
	virtual ~FindElrielLine();

private:
	typedef QuestLine super;
};
