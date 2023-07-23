#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;
class Scrappy;
class Squally;

class ArcaneHintBehavior : public GameComponent
{
public:
	static ArcaneHintBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	ArcaneHintBehavior(GameObject* owner);
	virtual ~ArcaneHintBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	void runCinematicSequencePt1();
	void runCinematicSequencePt2();
	void runCinematicSequencePt3();

	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
};
