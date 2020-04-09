#pragma once

#include "Engine/Quests/QuestLine.h"

class WindSpellbookLine : public QuestLine
{
public:
	static WindSpellbookLine* create();

	QuestLine* clone() override;

	static const std::string MapKeyQuestLine;

protected:
	WindSpellbookLine();
	virtual ~WindSpellbookLine();

private:
	typedef QuestLine super;
};
