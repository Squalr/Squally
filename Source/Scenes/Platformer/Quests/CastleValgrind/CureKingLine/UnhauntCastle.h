#pragma once

#include "Engine/Quests/QuestTask.h"

class Guano;
class Hera;
class QuestLine;
class Scrappy;
class Squally;

class UnhauntCastle : public QuestTask
{
public:
	static UnhauntCastle* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;
	static const std::string SaveKeyUnhauntedCount;
	static const std::string SaveKeyElricCured;
	static const std::string SaveKeyLeopoldCured;
	static const int MaxCuredCount;

protected:
	UnhauntCastle(GameObject* owner, QuestLine* questLine);
	virtual ~UnhauntCastle();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();
	void setPreText();

	Guano* guano = nullptr;
	Hera* hera = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
};
