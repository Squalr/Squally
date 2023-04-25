#pragma once

#include "Engine/Quests/QuestTask.h"

class CartLift;
class Computer;
class Guano;
class QuestLine;
class Scrappy;
class Squally;

class RestorePower : public QuestTask
{
public:
	static RestorePower* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;
protected:
	RestorePower(GameObject* owner, QuestLine* questLine);
	virtual ~RestorePower();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void powerOnComputers();

	Computer* computer = nullptr;
	Guano* guano = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
	CartLift* cartLift = nullptr;

	static const std::string MapEventPowerRestored;
	static const std::string TagCartLiftPowered;
};
