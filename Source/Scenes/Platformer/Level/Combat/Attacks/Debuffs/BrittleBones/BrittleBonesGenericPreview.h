#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class BrittleBonesGenericPreview : public HackablePreview
{
public:
	static BrittleBonesGenericPreview* create();

	HackablePreview* clone() override;

protected:
	BrittleBonesGenericPreview();
	virtual ~BrittleBonesGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
