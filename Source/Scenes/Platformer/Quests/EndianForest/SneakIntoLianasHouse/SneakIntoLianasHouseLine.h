#pragma once

#include "Engine/Quests/QuestLine.h"

class SneakIntoLianasHouseLine : public QuestLine
{
public:
	static SneakIntoLianasHouseLine* create();

	QuestLine* clone() override;

	static const std::string MapKeyQuestLine;

protected:
	SneakIntoLianasHouseLine();
	virtual ~SneakIntoLianasHouseLine();

private:
	typedef QuestLine super;
};
