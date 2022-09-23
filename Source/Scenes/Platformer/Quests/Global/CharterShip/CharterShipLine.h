#pragma once

#include "Engine/Quests/QuestLine.h"

class CharterShipLine : public QuestLine
{
public:
	static CharterShipLine* create();

	QuestLine* clone() override;

	static const std::string MapKeyQuestLine;

protected:
	CharterShipLine();
	virtual ~CharterShipLine();

private:
	typedef QuestLine super;
};
