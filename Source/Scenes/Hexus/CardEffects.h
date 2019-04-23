#pragma once
#include "Engine/SmartNode.h"

namespace cocos2d
{
	class ParticleSystemQuad;
}

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
	~CardEffects();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;
	
	cocos2d::ParticleSystemQuad* getBite();
	cocos2d::ParticleSystemQuad* getDustPoof();
	cocos2d::ParticleSystemQuad* getDustStorm();
	cocos2d::ParticleSystemQuad* getFireBlast();
	cocos2d::ParticleSystemQuad* getFlow();
	cocos2d::ParticleSystemQuad* getFocusRing();
	cocos2d::ParticleSystemQuad* getFrostCircle();
	cocos2d::ParticleSystemQuad* getGush();
	cocos2d::ParticleSystemQuad* getLightning();
	cocos2d::ParticleSystemQuad* getMagicBurst();
	cocos2d::ParticleSystemQuad* getMeteorAlt();
	cocos2d::ParticleSystemQuad* getMeteorBlue();
	cocos2d::ParticleSystemQuad* getMeteorPurple();
	cocos2d::ParticleSystemQuad* getNether();
	cocos2d::ParticleSystemQuad* getPoison();
	cocos2d::ParticleSystemQuad* getRadialAura();
	cocos2d::ParticleSystemQuad* getRadialFire();
	cocos2d::ParticleSystemQuad* getRadialGalaxy();
	cocos2d::ParticleSystemQuad* getRadialStorm();
	cocos2d::ParticleSystemQuad* getSelectionPulse();
	cocos2d::ParticleSystemQuad* getSpinningMagic();
	cocos2d::ParticleSystemQuad* getSplash();
	cocos2d::ParticleSystemQuad* getStarBurst();
	cocos2d::ParticleSystemQuad* getStarHit();
	cocos2d::ParticleSystemQuad* getTargetPulse();

	cocos2d::ParticleSystemQuad* bite;
	cocos2d::ParticleSystemQuad* dustPoof;
	cocos2d::ParticleSystemQuad* dustStorm;
	cocos2d::ParticleSystemQuad* fireBlast;
	cocos2d::ParticleSystemQuad* flow;
	cocos2d::ParticleSystemQuad* frostCircle;
	cocos2d::ParticleSystemQuad* focusRing;
	cocos2d::ParticleSystemQuad* gush;
	cocos2d::ParticleSystemQuad* lightning;
	cocos2d::ParticleSystemQuad* magicBurst;
	cocos2d::ParticleSystemQuad* meteorAlt;
	cocos2d::ParticleSystemQuad* meteorBlue;
	cocos2d::ParticleSystemQuad* meteorPurple;
	cocos2d::ParticleSystemQuad* nether;
	cocos2d::ParticleSystemQuad* poison;
	cocos2d::ParticleSystemQuad* radialAura;
	cocos2d::ParticleSystemQuad* radialFire;
	cocos2d::ParticleSystemQuad* radialGalaxy;
	cocos2d::ParticleSystemQuad* radialStorm;
	cocos2d::ParticleSystemQuad* selectionPulse;
	cocos2d::ParticleSystemQuad* spinningMagic;
	cocos2d::ParticleSystemQuad* splash;
	cocos2d::ParticleSystemQuad* starBurst;
	cocos2d::ParticleSystemQuad* starHit;
	cocos2d::ParticleSystemQuad* targetPulse;
};
