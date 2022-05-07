#pragma once

#include "Engine/Quests/QuestTask.h"

class QuestLine;
class Rhinoman;
class ScreamingDoor;
class Squally;
class WorldSound;

class ReleasePressure : public QuestTask
{
public:
	static ReleasePressure* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	ReleasePressure(GameObject* owner, QuestLine* questLine);
	virtual ~ReleasePressure();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	static const std::string MapEventPressureReleased;
	static const std::string MapTagPressureRaised;
	static const std::string MapTagPressureLowered;
};
