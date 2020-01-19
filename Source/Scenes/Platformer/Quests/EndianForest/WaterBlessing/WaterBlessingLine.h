#pragma once

#include "Engine/Quests/QuestLine.h"

class WaterBlessingLine : public QuestLine
{
public:
	static WaterBlessingLine* create();

	QuestLine* clone() override;

	static const std::string MapKeyQuestLine;

protected:
	WaterBlessingLine();
	virtual ~WaterBlessingLine();

private:
	typedef QuestLine super;
};
