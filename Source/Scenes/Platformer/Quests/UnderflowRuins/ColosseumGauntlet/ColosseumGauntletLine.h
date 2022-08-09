#pragma once

#include "Engine/Quests/QuestLine.h"

class ColosseumGauntletLine : public QuestLine
{
public:
	static ColosseumGauntletLine* create();

	QuestLine* clone() override;

	static const std::string MapKeyQuestLine;

protected:
	ColosseumGauntletLine();
	virtual ~ColosseumGauntletLine();

private:
	typedef QuestLine super;
};
