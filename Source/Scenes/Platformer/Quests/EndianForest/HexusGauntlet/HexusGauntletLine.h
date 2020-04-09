#pragma once

#include "Engine/Quests/QuestLine.h"

class HexusGauntletLine : public QuestLine
{
public:
	static HexusGauntletLine* create();

	QuestLine* clone() override;

	static const std::string MapKeyQuestLine;

protected:
	HexusGauntletLine();
	virtual ~HexusGauntletLine();

private:
	typedef QuestLine super;
};
