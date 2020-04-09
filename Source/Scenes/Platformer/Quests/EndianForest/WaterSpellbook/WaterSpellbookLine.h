#pragma once

#include "Engine/Quests/QuestLine.h"

class WaterSpellbookLine : public QuestLine
{
public:
	static WaterSpellbookLine* create();

	QuestLine* clone() override;

	static const std::string MapKeyQuestLine;

protected:
	WaterSpellbookLine();
	virtual ~WaterSpellbookLine();

private:
	typedef QuestLine super;
};
