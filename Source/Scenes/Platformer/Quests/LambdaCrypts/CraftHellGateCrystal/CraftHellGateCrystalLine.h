#pragma once

#include "Engine/Quests/QuestLine.h"

class CraftHellGateCrystalLine : public QuestLine
{
public:
	static CraftHellGateCrystalLine* create();

	QuestLine* clone() override;

	static const std::string MapKeyQuestLine;

protected:
	CraftHellGateCrystalLine();
	virtual ~CraftHellGateCrystalLine();

private:
	typedef QuestLine super;
};
