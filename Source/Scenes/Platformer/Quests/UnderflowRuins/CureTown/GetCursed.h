#pragma once

#include "Engine/Quests/QuestTask.h"

class Guano;
class QuestLine;
class Scrappy;
class Squally;
class Medusa;

class GetCursed : public QuestTask
{
public:
	static GetCursed* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	GetCursed(GameObject* owner, QuestLine* questLine);
	virtual ~GetCursed();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequencePt1();
	void runCinematicSequencePt2();
	void petrifyGuano();

	Guano* guano;
	Scrappy* scrappy;
	Squally* squally;
	Medusa* medusa;

	static const std::string TagCinematicExit;
	static const std::string SaveKeyDespawned;
};
