#pragma once

#include "Engine/Quests/QuestLine.h"

class MinesPerceptronEncounterLine : public QuestLine
{
public:
	static MinesPerceptronEncounterLine* create();

	QuestLine* clone() override;

	static const std::string MapKeyQuestLine;

protected:
	MinesPerceptronEncounterLine();
	virtual ~MinesPerceptronEncounterLine();

private:
	typedef QuestLine super;
};
