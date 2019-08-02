#pragma once

#include "Engine/Quests/QuestLine.h"

class GameObject;

class IntroLine : public QuestLine
{
public:
	static IntroLine* create();

	static const std::string MapKeyQuestLine;

protected:
	IntroLine();
	~IntroLine();

private:
	typedef QuestLine super;
};
