#pragma once

#include "Engine/Quests/QuestLine.h"

class MagesWarpLockLine : public QuestLine
{
public:
	static MagesWarpLockLine* create();

	QuestLine* clone() override;

	static const std::string MapKeyQuestLine;

protected:
	MagesWarpLockLine();
	virtual ~MagesWarpLockLine();

private:
	typedef QuestLine super;
};
