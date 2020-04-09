#pragma once

#include "Engine/Quests/QuestLine.h"

class RescueGuanoLine : public QuestLine
{
public:
	static RescueGuanoLine* create();

	QuestLine* clone() override;

	static const std::string MapKeyQuestLine;

protected:
	RescueGuanoLine();
	virtual ~RescueGuanoLine();

private:
	typedef QuestLine super;
};
