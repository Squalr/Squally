#pragma once

#include "Engine/Quests/QuestTask.h"

class CameraStop;
class CollisionObject;
class EvilEye;
class Gecky;
class Guano;
class KingRedsong;
class KingRedsongSlime;
class Leroy;
class PrincessOpal;
class QuestLine;
class Scrappy;
class Squally;

class TalkToKingRedsong : public QuestTask
{
public:
	static TalkToKingRedsong* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	TalkToKingRedsong(GameObject* owner, QuestLine* questLine);
	virtual ~TalkToKingRedsong();

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

	EvilEye* evilEye = nullptr;
	Gecky* gecky = nullptr;
	Guano* guano = nullptr;
	KingRedsong* kingRedsong = nullptr;
	KingRedsongSlime* kingRedsongSlime = nullptr;
	Leroy* leroy = nullptr;
	PrincessOpal* princessOpal = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
};
