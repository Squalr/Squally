#pragma once

#include "Engine/Quests/QuestLine.h"

class GameObject;

class IntroLine : QuestLine
{
public:
	static GameObject* deserialize(GameObject* owner, std::string questLine, std::string questTask, std::string questTag);

	static const std::string MapKeyQuestLine;

private:
	typedef QuestLine super;
};
