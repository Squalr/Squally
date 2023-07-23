#pragma once

#include "Engine/Quests/QuestLine.h"

class DefeatAsmodeusLine : public QuestLine
{
public:
	static DefeatAsmodeusLine* create();

	QuestLine* clone() override;

	static const std::string MapKeyQuestLine;

protected:
	DefeatAsmodeusLine();
	virtual ~DefeatAsmodeusLine();

private:
	typedef QuestLine super;
};
