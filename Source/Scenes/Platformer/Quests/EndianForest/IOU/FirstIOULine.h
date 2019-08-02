#pragma once

#include "Engine/Quests/QuestLine.h"

class GameObject;

class FirstIOULine : public QuestLine
{
public:
	static FirstIOULine* create();

	static const std::string MapKeyQuestLine;

protected:
	FirstIOULine();
	~FirstIOULine();

private:
	typedef QuestLine super;
};
