#pragma once

#include "Engine/Quests/QuestLine.h"

class ElricsDemiseLine : public QuestLine
{
public:
	static ElricsDemiseLine* create();

	QuestLine* clone() override;

	static const std::string MapKeyQuestLine;

protected:
	ElricsDemiseLine();
	virtual ~ElricsDemiseLine();

private:
	typedef QuestLine super;
};
