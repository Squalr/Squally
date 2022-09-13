#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class RejuvinationGenericPreview : public HackablePreview
{
public:
	static RejuvinationGenericPreview* create();

	HackablePreview* clone() override;

protected:
	RejuvinationGenericPreview();
	virtual ~RejuvinationGenericPreview();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* healEffect = nullptr;
};
