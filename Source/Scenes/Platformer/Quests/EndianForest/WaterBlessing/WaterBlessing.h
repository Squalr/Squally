#pragma once

#include "Engine/Quests/QuestTask.h"

class PlatformerEntity;
class QuestLine;
class Squally;

class WaterBlessing : public QuestTask
{
public:
	static WaterBlessing* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	WaterBlessing(GameObject* owner, QuestLine* questLine);
	virtual ~WaterBlessing();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();
	void setPostText();

	PlatformerEntity* entity;
	Squally* squally;
};
