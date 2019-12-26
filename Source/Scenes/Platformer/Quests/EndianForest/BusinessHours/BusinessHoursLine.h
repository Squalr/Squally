#pragma once

#include "Engine/Quests/QuestLine.h"

class BusinessHoursLine : public QuestLine
{
public:
	static BusinessHoursLine* create();

	QuestLine* clone() override;

	static const std::string MapKeyQuestLine;

protected:
	BusinessHoursLine();
	~BusinessHoursLine();

private:
	typedef QuestLine super;
};
