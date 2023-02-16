#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class ParryGenericPreview : public HackablePreview
{
public:
	static ParryGenericPreview* create();

	HackablePreview* clone() override;

protected:
	ParryGenericPreview();
	virtual ~ParryGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
