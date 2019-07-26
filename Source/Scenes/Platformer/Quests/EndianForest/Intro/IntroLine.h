#pragma once

#include "Engine/Quests/QuestLine.h"

class Quest;

class IntroLine : public QuestLine
{
public:
	static IntroLine* create();

	static const std::string MapKeyQuestLineIntro;

protected:
	IntroLine();
	~IntroLine();

private:
	typedef QuestLine super;
	void initializePositions() override;
	void initializeListeners() override;
};

