#pragma once

#include "Engine/Quests/QuestLine.h"

class PerceptronEncounterLine : public QuestLine
{
public:
	static PerceptronEncounterLine* create();

	QuestLine* clone() override;

	static const std::string MapKeyQuestLine;

protected:
	PerceptronEncounterLine();
	virtual ~PerceptronEncounterLine();

private:
	typedef QuestLine super;
};
