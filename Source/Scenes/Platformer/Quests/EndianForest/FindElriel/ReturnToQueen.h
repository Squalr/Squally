#pragma once

#include "Engine/Quests/QuestTask.h"

class Elriel;
class Guano;
class QueenLiana;
class QuestLine;
class RewardPoolLiana;
class Scrappy;
class Squally;

class ReturnToQueen : public QuestTask
{
public:
	static ReturnToQueen* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	ReturnToQueen(GameObject* owner, QuestLine* questLine);
	virtual ~ReturnToQueen();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();
	void setPostText();

	RewardPoolLiana* rewardPool = nullptr;
	Elriel* elriel = nullptr;
	Guano* guano = nullptr;
	QueenLiana* queenLiana = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
};
