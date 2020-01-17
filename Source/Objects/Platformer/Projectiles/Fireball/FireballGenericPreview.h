#pragma once

#include "Engine/Hackables/HackablePreview.h"

class SmartAnimationSequenceNode;

class FireballGenericPreview : public HackablePreview
{
public:
	static FireballGenericPreview* create();

	HackablePreview* clone() override;

protected:
	FireballGenericPreview();
	virtual ~FireballGenericPreview();
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* fireball;
};
