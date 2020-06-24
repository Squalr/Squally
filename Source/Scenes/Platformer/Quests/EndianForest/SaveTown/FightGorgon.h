#pragma once

#include "Engine/Quests/QuestTask.h"

class Gorgon;
class Ram;
class QuestLine;
class Sarude;
class Sound;
class Squally;
class SmartAnimationSequenceNode;
class WorldSound;

class FightGorgon : public QuestTask
{
public:
	static FightGorgon* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	FightGorgon(GameObject* owner, QuestLine* questLine);
	virtual ~FightGorgon();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runMageAnims();
	void positionImpactFx();
	void runCinematicSequencePart1();
	void runCinematicSequencePart1Alt();
	void runCinematicSequencePart2();
	void runCinematicSequencePart3();
	void killRammedEnemies();
	void flickerOutForceField();
	void runGorgonLoop();

	Sarude* sarude;
	Gorgon* gorgon;
	Ram* ram;
	Squally* squally;
	GameObject* forceField;
	SmartAnimationSequenceNode* shieldImpact;
	SmartAnimationSequenceNode* swordImpact;
	SmartAnimationSequenceNode* knifeImpact;
	WorldSound* backPeddleSound;
	WorldSound* runSound;
	WorldSound* reboundSoundShield;
	WorldSound* reboundSoundShieldLite;
	WorldSound* reboundSoundSword;
	Sound* impactSound;

	static const std::string ForceFieldTag;
	static const std::string MarkerTagBack;
	static const std::string MarkerTagFront;
};
