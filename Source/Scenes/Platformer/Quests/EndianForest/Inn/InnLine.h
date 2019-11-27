#pragma once

#include "Engine/Quests/QuestLine.h"

class InnLine : public QuestLine
{
public:
	static InnLine* create();

	static const std::string MapKeyQuestLine;

protected:
	InnLine();
	~InnLine();

private:
	typedef QuestLine super;
};
