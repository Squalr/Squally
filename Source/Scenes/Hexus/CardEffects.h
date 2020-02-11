#pragma once
#include "Engine/SmartNode.h"

class SmartParticles;

class CardEffects : public SmartNode
{
public:
	static CardEffects* create();

	enum class CardEffect
	{
		Bite,
		DustPoof,
		DustStorm,
		FireBlast,
		Flow,
		FocusRing,
		FrostCirlce,
		Gush,
		Lightning,
		MagicBurst,
		MeteorAlt,
		MeteorBlue,
		MeteorPurple,
		Nether,
		Poison,
		RadialAura,
		RadialFire,
		RadialGalaxy,
		RadialStorm,
		SelectionPulse,
		SpinningMagic,
		Splash,
		StarBurst,
		StarHit,
		TargetPulse,
	};

	void runEffect(CardEffect effect);
	void clearEffects();

protected:
	CardEffects();
	virtual ~CardEffects();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;
	
	SmartParticles* getBite();
	SmartParticles* getDustPoof();
	SmartParticles* getDustStorm();
	SmartParticles* getFireBlast();
	SmartParticles* getFlow();
	SmartParticles* getFocusRing();
	SmartParticles* getFrostCircle();
	SmartParticles* getGush();
	SmartParticles* getLightning();
	SmartParticles* getMagicBurst();
	SmartParticles* getMeteorAlt();
	SmartParticles* getMeteorBlue();
	SmartParticles* getMeteorPurple();
	SmartParticles* getNether();
	SmartParticles* getPoison();
	SmartParticles* getRadialAura();
	SmartParticles* getRadialFire();
	SmartParticles* getRadialGalaxy();
	SmartParticles* getRadialStorm();
	SmartParticles* getSelectionPulse();
	SmartParticles* getSpinningMagic();
	SmartParticles* getSplash();
	SmartParticles* getStarBurst();
	SmartParticles* getStarHit();
	SmartParticles* getTargetPulse();

	SmartParticles* bite;
	SmartParticles* dustPoof;
	SmartParticles* dustStorm;
	SmartParticles* fireBlast;
	SmartParticles* flow;
	SmartParticles* frostCircle;
	SmartParticles* focusRing;
	SmartParticles* gush;
	SmartParticles* lightning;
	SmartParticles* magicBurst;
	SmartParticles* meteorAlt;
	SmartParticles* meteorBlue;
	SmartParticles* meteorPurple;
	SmartParticles* nether;
	SmartParticles* poison;
	SmartParticles* radialAura;
	SmartParticles* radialFire;
	SmartParticles* radialGalaxy;
	SmartParticles* radialStorm;
	SmartParticles* selectionPulse;
	SmartParticles* spinningMagic;
	SmartParticles* splash;
	SmartParticles* starBurst;
	SmartParticles* starHit;
	SmartParticles* targetPulse;
};
