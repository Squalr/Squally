#pragma once

#include "Engine/Quests/QuestLine.h"

class SailForRuinsLine : public QuestLine
{
public:
	static SailForRuinsLine* create();

	QuestLine* clone() override;

	static const std::string MapKeyQuestLine;

protected:
	SailForRuinsLine();
	~SailForRuinsLine();

private:
	typedef QuestLine super;
};
