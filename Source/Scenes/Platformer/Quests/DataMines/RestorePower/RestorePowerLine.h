#pragma once

#include "Engine/Quests/QuestLine.h"

class RestorePowerLine : public QuestLine
{
public:
	static RestorePowerLine* create();

	QuestLine* clone() override;

	static const std::string MapKeyQuestLine;

protected:
	RestorePowerLine();
	virtual ~RestorePowerLine();

private:
	typedef QuestLine super;
};
