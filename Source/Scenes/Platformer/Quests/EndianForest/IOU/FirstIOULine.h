#pragma once

#include "Engine/Quests/QuestLine.h"

class GameObject;
class Quest;

class FirstIOULine : public QuestLine
{
public:
	static FirstIOULine* create(std::string quest, std::string questTag, GameObject* owner);

	static const std::string MapKeyQuestLine;

protected:
	FirstIOULine(std::string quest, std::string questTag, GameObject* owner);
	~FirstIOULine();

private:
	typedef QuestLine super;
	void initializePositions() override;
	void initializeListeners() override;
};

