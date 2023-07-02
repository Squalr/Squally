#pragma once

#include "Engine/Quests/QuestTask.h"

class Asmodeus;
class Guano;
class QuestLine;
class Scrappy;
class Squally;

class LavaFlood : public QuestTask
{
public:
	static LavaFlood* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;
	static const std::string MapEventLavaFlooded;
	
protected:
	LavaFlood(GameObject* owner, QuestLine* questLine);
	virtual ~LavaFlood();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void applyLavaFlood(bool isFlooded, bool animate);

	Guano* guano = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
	Asmodeus* asmodeus = nullptr;
};
