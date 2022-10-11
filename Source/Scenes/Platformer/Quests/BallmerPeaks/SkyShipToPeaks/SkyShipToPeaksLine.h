#pragma once

#include "Engine/Quests/QuestLine.h"

class SkyShipToPeaksLine : public QuestLine
{
public:
	static SkyShipToPeaksLine* create();

	QuestLine* clone() override;

	static const std::string MapKeyQuestLine;

protected:
	SkyShipToPeaksLine();
	virtual ~SkyShipToPeaksLine();

private:
	typedef QuestLine super;
};
