#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class FuryGenericPreview : public HackablePreview
{
public:
	static FuryGenericPreview* create();

	HackablePreview* clone() override;

protected:
	FuryGenericPreview();
	virtual ~FuryGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
