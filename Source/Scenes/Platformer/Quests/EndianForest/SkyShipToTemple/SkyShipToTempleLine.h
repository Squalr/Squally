#pragma once

#include "Engine/Quests/QuestLine.h"

class SkyShipToTempleLine : public QuestLine
{
public:
	static SkyShipToTempleLine* create();

	QuestLine* clone() override;

	static const std::string MapKeyQuestLine;

protected:
	SkyShipToTempleLine();
	virtual ~SkyShipToTempleLine();

private:
	typedef QuestLine super;
};
