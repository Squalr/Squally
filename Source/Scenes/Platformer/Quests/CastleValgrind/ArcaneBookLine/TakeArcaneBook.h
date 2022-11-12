#pragma once

#include "Engine/Quests/QuestTask.h"

class ArcaneBook;
class EvilEye;
class Gecky;
class Guano;
class Mabel;
class QuestLine;
class Scrappy;
class Squally;

class TakeArcaneBook : public QuestTask
{
public:
	static TakeArcaneBook* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	TakeArcaneBook(GameObject* owner, QuestLine* questLine);
	virtual ~TakeArcaneBook();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void moveBookshelf(bool animate);
	void runCinematicSequencePt1();

	Gecky* gecky = nullptr;
	Guano* guano = nullptr;
	Mabel* mabel = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
	ArcaneBook* arcaneBook = nullptr;
	GameObject* bookshelf = nullptr;
};
