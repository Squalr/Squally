#pragma once

#include "Engine/Quests/QuestLine.h"

class SkyShipToCastleLine : public QuestLine
{
public:
	static SkyShipToCastleLine* create();

	QuestLine* clone() override;

	static const std::string MapKeyQuestLine;

protected:
	SkyShipToCastleLine();
	virtual ~SkyShipToCastleLine();

private:
	typedef QuestLine super;
};
