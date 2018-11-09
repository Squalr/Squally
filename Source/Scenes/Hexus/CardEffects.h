#pragma once
#include "cocos2d.h"

#include "Engine/SmartNode.h"
#include "Resources.h"
#include "Scenes/Hexus/Config.h"

using namespace cocos2d;

class CardEffects : public SmartNode
{
public:
	static CardEffects* create();

	enum CardEffect
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
	~CardEffects();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	ParticleSystemQuad* getBite();
	ParticleSystemQuad* getDustPoof();
	ParticleSystemQuad* getDustStorm();
	ParticleSystemQuad* getFireBlast();
	ParticleSystemQuad* getFlow();
	ParticleSystemQuad* getFocusRing();
	ParticleSystemQuad* getFrostCircle();
	ParticleSystemQuad* getGush();
	ParticleSystemQuad* getLightning();
	ParticleSystemQuad* getMagicBurst();
	ParticleSystemQuad* getMeteorAlt();
	ParticleSystemQuad* getMeteorBlue();
	ParticleSystemQuad* getMeteorPurple();
	ParticleSystemQuad* getRadialAura();
	ParticleSystemQuad* getRadialFire();
	ParticleSystemQuad* getRadialGalaxy();
	ParticleSystemQuad* getRadialStorm();
	ParticleSystemQuad* getSelectionPulse();
	ParticleSystemQuad* getSpinningMagic();
	ParticleSystemQuad* getSplash();
	ParticleSystemQuad* getStarBurst();
	ParticleSystemQuad* getStarHit();
	ParticleSystemQuad* getTargetPulse();

	ParticleSystemQuad* bite;
	ParticleSystemQuad* dustPoof;
	ParticleSystemQuad* dustStorm;
	ParticleSystemQuad* fireBlast;
	ParticleSystemQuad* flow;
	ParticleSystemQuad* frostCircle;
	ParticleSystemQuad* focusRing;
	ParticleSystemQuad* gush;
	ParticleSystemQuad* lightning;
	ParticleSystemQuad* magicBurst;
	ParticleSystemQuad* meteorAlt;
	ParticleSystemQuad* meteorBlue;
	ParticleSystemQuad* meteorPurple;
	ParticleSystemQuad* radialAura;
	ParticleSystemQuad* radialFire;
	ParticleSystemQuad* radialGalaxy;
	ParticleSystemQuad* radialStorm;
	ParticleSystemQuad* selectionPulse;
	ParticleSystemQuad* spinningMagic;
	ParticleSystemQuad* splash;
	ParticleSystemQuad* starBurst;
	ParticleSystemQuad* starHit;
	ParticleSystemQuad* targetPulse;
};
