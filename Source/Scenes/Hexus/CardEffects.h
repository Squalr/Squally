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
		SelectionPulse,
		Fire,
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

	ParticleSystemQuad* selectionPulse;
};

