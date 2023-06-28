#pragma once

#include "Engine/Quests/QuestTask.h"

class CinematicMarker;
class Guano;
class Marcel;
class QuestLine;
class Squally;

class WindSpellbook : public QuestTask
{
public:
	static WindSpellbook* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	WindSpellbook(GameObject* owner, QuestLine* questLine);
	virtual ~WindSpellbook();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;
	
	void runCinematicSequencePart1();
	void runCinematicSequencePart2();
	void runCinematicSequencePart3();
	void runCinematicSequencePart4();
	void runCinematicSequencePart5();
	void runCinematicSequencePart6();

	Marcel* marcel = nullptr;
	Squally* squally = nullptr;
	CinematicMarker* marcelArrive = nullptr;
	CinematicMarker* marcelLeave = nullptr;
	QueenLiana* queenLiana = nullptr;
	Guano* guano = nullptr;
	Scrappy* scrappy = nullptr;
};
