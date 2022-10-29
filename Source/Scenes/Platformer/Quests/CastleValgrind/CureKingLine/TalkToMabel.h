#pragma once

#include "Engine/Quests/QuestTask.h"

class EvilEye;
class Gecky;
class Guano;
class Mabel;
class QuestLine;
class Scrappy;
class Squally;

class TalkToMabel : public QuestTask
{
public:
	static TalkToMabel* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	TalkToMabel(GameObject* owner, QuestLine* questLine);
	virtual ~TalkToMabel();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();

	EvilEye* evilEye = nullptr;
	Gecky* gecky = nullptr;
	Guano* guano = nullptr;
	Mabel* mabel = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;

	static const std::string MapEventMabelRevealed;
};
