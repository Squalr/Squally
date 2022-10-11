#pragma once

#include "Engine/Quests/QuestLine.h"

class RestoreWarpGatesLine : public QuestLine
{
public:
	static RestoreWarpGatesLine* create();

	QuestLine* clone() override;

	static const std::string MapKeyQuestLine;

protected:
	RestoreWarpGatesLine();
	virtual ~RestoreWarpGatesLine();

private:
	typedef QuestLine super;
};
