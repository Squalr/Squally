#pragma once

#include "Engine/UI/HUD/Hud.h"

class LocalizedLabel;
class LocalizedString;

class MusicOverlay : public Hud
{
public:
	static MusicOverlay* create();

private:
	typedef Hud super;
	MusicOverlay();
	virtual ~MusicOverlay();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	LocalizedString* trackString;
	LocalizedLabel* trackLabel;
	LocalizedString* artistString;
	LocalizedLabel* artistLabel;
};
