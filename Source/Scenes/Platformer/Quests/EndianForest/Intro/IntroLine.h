#pragma once

#include "Engine/Quests/QuestLine.h"

class IntroLine : public QuestLine
{
public:
	static IntroLine* create();

	QuestLine* clone() override;

	static const std::string MapKeyQuestLine;

protected:
	IntroLine();
	virtual ~IntroLine();

private:
	typedef QuestLine super;
};
