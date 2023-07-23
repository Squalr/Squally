#pragma once

#include "Engine/Quests/QuestLine.h"

class CraftDemonHeartLine : public QuestLine
{
public:
	static CraftDemonHeartLine* create();

	QuestLine* clone() override;

	static const std::string MapKeyQuestLine;

protected:
	CraftDemonHeartLine();
	virtual ~CraftDemonHeartLine();

private:
	typedef QuestLine super;
};
