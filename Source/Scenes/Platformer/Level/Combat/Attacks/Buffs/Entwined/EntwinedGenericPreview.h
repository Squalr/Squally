#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class EntwinedGenericPreview : public HackablePreview
{
public:
	static EntwinedGenericPreview* create();

	HackablePreview* clone() override;

protected:
	EntwinedGenericPreview();
	virtual ~EntwinedGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
