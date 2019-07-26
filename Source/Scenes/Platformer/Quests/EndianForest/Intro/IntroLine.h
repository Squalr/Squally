#pragma once

#include "Engine/Quests/QuestLine.h"

class GameObject;
class Quest;

class IntroLine : public QuestLine
{
public:
	static IntroLine* create(GameObject* owner);

	static const std::string MapKeyQuestLineIntro;

protected:
	IntroLine(GameObject* owner);
	~IntroLine();

private:
	typedef QuestLine super;
	void initializePositions() override;
	void initializeListeners() override;
};

