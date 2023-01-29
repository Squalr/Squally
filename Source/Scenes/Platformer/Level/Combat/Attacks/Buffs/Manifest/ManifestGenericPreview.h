#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class ManifestGenericPreview : public HackablePreview
{
public:
	static ManifestGenericPreview* create();

	HackablePreview* clone() override;

protected:
	ManifestGenericPreview();
	virtual ~ManifestGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
