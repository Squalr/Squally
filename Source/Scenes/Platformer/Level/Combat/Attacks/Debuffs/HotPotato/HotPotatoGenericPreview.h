#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class HotPotatoGenericPreview : public HackablePreview
{
public:
	static HotPotatoGenericPreview* create();

	HackablePreview* clone() override;

protected:
	HotPotatoGenericPreview();
	virtual ~HotPotatoGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* healEffect = nullptr;
};
