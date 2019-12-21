#pragma once

#include "Engine/Hackables/HackablePreview.h"

class SmartAnimationSequenceNode;

class RestoreHealthGenericPreview : public HackablePreview
{
public:
	static RestoreHealthGenericPreview* create();

	HackablePreview* clone() override;

protected:
	RestoreHealthGenericPreview();
	virtual ~RestoreHealthGenericPreview();
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* healEffect;
};
