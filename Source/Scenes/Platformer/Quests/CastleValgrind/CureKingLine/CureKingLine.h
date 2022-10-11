#pragma once

#include "Engine/Quests/QuestLine.h"

class CureKingLine : public QuestLine
{
public:
	static CureKingLine* create();

	QuestLine* clone() override;

	static const std::string MapKeyQuestLine;

protected:
	CureKingLine();
	virtual ~CureKingLine();

private:
	typedef QuestLine super;
};
