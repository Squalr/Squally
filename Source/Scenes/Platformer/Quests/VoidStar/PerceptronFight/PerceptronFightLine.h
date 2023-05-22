#pragma once

#include "Engine/Quests/QuestLine.h"

class PerceptronFightLine : public QuestLine
{
public:
	static PerceptronFightLine* create();

	QuestLine* clone() override;

	static const std::string MapKeyQuestLine;

protected:
	PerceptronFightLine();
	virtual ~PerceptronFightLine();

private:
	typedef QuestLine super;
};
