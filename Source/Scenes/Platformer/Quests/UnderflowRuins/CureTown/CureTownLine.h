#pragma once

#include "Engine/Quests/QuestLine.h"

class CureTownLine : public QuestLine
{
public:
	static CureTownLine* create();

	QuestLine* clone() override;

	static const std::string MapKeyQuestLine;

protected:
	CureTownLine();
	virtual ~CureTownLine();

private:
	typedef QuestLine super;
};
