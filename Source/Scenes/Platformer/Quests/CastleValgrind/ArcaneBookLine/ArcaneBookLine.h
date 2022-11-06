#pragma once

#include "Engine/Quests/QuestLine.h"

class ArcaneBookLine : public QuestLine
{
public:
	static ArcaneBookLine* create();

	QuestLine* clone() override;

	static const std::string MapKeyQuestLine;

protected:
	ArcaneBookLine();
	virtual ~ArcaneBookLine();

private:
	typedef QuestLine super;
};
