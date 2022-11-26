#pragma once

#include "Engine/Quests/QuestTask.h"

class CameraStop;
class CollisionObject;
class EvilEye;
class Gecky;
class Guano;
class KingRedsong;
class QuestLine;
class Scrappy;
class Squally;

class TalkToKing : public QuestTask
{
public:
	static TalkToKing* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	TalkToKing(GameObject* owner, QuestLine* questLine);
	virtual ~TalkToKing();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequencePt1();
	void runCinematicSequencePt2();
	void runCinematicSequencePt3();
	void runCinematicSequencePt4();
	void runCinematicSequencePt5();
	void runCinematicSequencePt6();
	void runCinematicSequencePt7();

	EvilEye* evilEye = nullptr;
	Gecky* gecky = nullptr;
	Guano* guano = nullptr;
	KingRedsong* kingRedsong = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
};
