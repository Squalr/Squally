#pragma once

#include "Engine/Quests/QuestTask.h"

class GatlingGun;
class KillingMachine1;
class KillingMachine2;
class KillingMachine3;
class KillingMachine4;
class KillingMachine5;
class KillingMachine6;
class QuestLine;
class Squally;
class WorldSound;

class WinGauntlet : public QuestTask
{
public:
	static WinGauntlet* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	WinGauntlet(GameObject* owner, QuestLine* questLine);
	virtual ~WinGauntlet();

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

	KillingMachine1* killingMachine1 = nullptr;
	KillingMachine2* killingMachine2 = nullptr;
	KillingMachine3* killingMachine3 = nullptr;
	KillingMachine4* killingMachine4 = nullptr;
	KillingMachine5* killingMachine5 = nullptr;
	KillingMachine6* killingMachine6 = nullptr;
	Squally* squally = nullptr;
	GatlingGun* gatlingGun = nullptr;

	static const std::string MapEventBeginGauntlet;
};
