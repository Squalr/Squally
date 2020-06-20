#pragma once

#include "Engine/Quests/QuestLine.h"

class CleansePyramidLine : public QuestLine
{
public:
	static CleansePyramidLine* create();

	QuestLine* clone() override;

	static const std::string MapKeyQuestLine;

protected:
	CleansePyramidLine();
	virtual ~CleansePyramidLine();

private:
	typedef QuestLine super;
};
