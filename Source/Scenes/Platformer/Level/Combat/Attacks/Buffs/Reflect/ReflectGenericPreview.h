#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class ReflectGenericPreview : public HackablePreview
{
public:
	static ReflectGenericPreview* create();

	HackablePreview* clone() override;

protected:
	ReflectGenericPreview();
	virtual ~ReflectGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* healEffect;
};
