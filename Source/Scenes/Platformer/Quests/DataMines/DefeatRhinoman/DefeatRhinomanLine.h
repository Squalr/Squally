#pragma once

#include "Engine/Quests/QuestLine.h"

class DefeatRhinomanLine : public QuestLine
{
public:
	static DefeatRhinomanLine* create();

	QuestLine* clone() override;

	static const std::string MapKeyQuestLine;

protected:
	DefeatRhinomanLine();
	virtual ~DefeatRhinomanLine();

private:
	typedef QuestLine super;
};
