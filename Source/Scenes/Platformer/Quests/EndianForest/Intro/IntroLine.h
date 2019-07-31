#pragma once

#include "Engine/Quests/QuestLine.h"

class GameObject;
class Quest;

class IntroLine : public QuestLine
{
public:
	static IntroLine* create(std::string quest, std::string questTag, GameObject* owner);

	static const std::string MapKeyQuestLine;

protected:
	IntroLine(std::string quest, std::string questTag, GameObject* owner);
	~IntroLine();

private:
	typedef QuestLine super;
	void initializePositions() override;
	void initializeListeners() override;
};

