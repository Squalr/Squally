#pragma once

#include "Engine/Quests/QuestTask.h"

class PrincessNebea;
class Gecky;
class Grim;
class Guano;
class QuestLine;
class Scrappy;
class Squally;

class TalkToNebea : public QuestTask
{
public:
	static TalkToNebea* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	TalkToNebea(GameObject* owner, QuestLine* questLine);
	virtual ~TalkToNebea();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();

	PrincessNebea* princessNebea = nullptr;
	Gecky* gecky = nullptr;
	Guano* guano = nullptr;
	Grim* grim = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
};
