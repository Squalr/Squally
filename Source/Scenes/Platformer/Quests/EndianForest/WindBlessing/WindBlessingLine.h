#pragma once

#include "Engine/Quests/QuestLine.h"

class WindBlessingLine : public QuestLine
{
public:
	static WindBlessingLine* create();

	QuestLine* clone() override;

	static const std::string MapKeyQuestLine;

protected:
	WindBlessingLine();
	virtual ~WindBlessingLine();

private:
	typedef QuestLine super;
};
