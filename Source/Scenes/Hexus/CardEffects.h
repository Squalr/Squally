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

	SmartParticles* bite = nullptr;
	SmartParticles* dustPoof = nullptr;
	SmartParticles* dustStorm = nullptr;
	SmartParticles* fireBlast = nullptr;
	SmartParticles* flow = nullptr;
	SmartParticles* frostCircle = nullptr;
	SmartParticles* focusRing = nullptr;
	SmartParticles* gush = nullptr;
	SmartParticles* lightning = nullptr;
	SmartParticles* magicBurst = nullptr;
	SmartParticles* meteorAlt = nullptr;
	SmartParticles* meteorBlue = nullptr;
	SmartParticles* meteorPurple = nullptr;
	SmartParticles* nether = nullptr;
	SmartParticles* poison = nullptr;
	SmartParticles* radialAura = nullptr;
	SmartParticles* radialFire = nullptr;
	SmartParticles* radialGalaxy = nullptr;
	SmartParticles* radialStorm = nullptr;
	SmartParticles* selectionPulse = nullptr;
	SmartParticles* spinningMagic = nullptr;
	SmartParticles* splash = nullptr;
	SmartParticles* starBurst = nullptr;
	SmartParticles* starHit = nullptr;
	SmartParticles* targetPulse = nullptr;
};
