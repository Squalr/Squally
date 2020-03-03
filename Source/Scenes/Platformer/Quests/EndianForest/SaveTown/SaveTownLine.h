#pragma once

#include "Engine/Quests/QuestLine.h"

class SaveTownLine : public QuestLine
{
public:
	static SaveTownLine* create();

	QuestLine* clone() override;

	static const std::string MapKeyQuestLine;

protected:
	SaveTownLine();
	virtual ~SaveTownLine();

private:
	typedef QuestLine super;
};
