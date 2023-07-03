#pragma once

#include "Engine/Quests/QuestTask.h"

class Gecky;
class Guano;
class Bancroft;
class Mildred;
class QuestLine;
class Scrappy;
class Squally;
class Warp;

class BancroftTrainAccess : public QuestTask
{
public:
	static BancroftTrainAccess* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	BancroftTrainAccess(GameObject* owner, QuestLine* questLine);
	virtual ~BancroftTrainAccess();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void setMildredText();

	void runCinematicSequenceAccessBlockedPt1();
	void runCinematicSequenceAccessBlockedPt2();
	void runCinematicSequenceAccessBlockedPt3();
	void runCinematicSequenceAccessBlockedPt4();
	void runCinematicSequenceAccessBlockedPt5();
	void runCinematicSequencePt1();

	Gecky* gecky = nullptr;
	Guano* guano = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
	Bancroft* bancroft = nullptr;
	Mildred* mildred = nullptr;
	Warp* warp = nullptr;

	static const std::string TagTrainWarp;
};
