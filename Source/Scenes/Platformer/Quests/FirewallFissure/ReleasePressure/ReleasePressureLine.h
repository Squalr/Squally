#pragma once

#include "Engine/Quests/QuestLine.h"

class ReleasePressureLine : public QuestLine
{
public:
	static ReleasePressureLine* create();

	QuestLine* clone() override;

	static const std::string MapKeyQuestLine;

protected:
	ReleasePressureLine();
	virtual ~ReleasePressureLine();

private:
	typedef QuestLine super;
};
