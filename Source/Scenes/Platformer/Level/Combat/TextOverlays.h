#pragma once

#include "Engine/UI/HUD/Hud.h"

class LocalizedLabel;
class LocalizedString;
class PlatformerEntity;

class TextOverlays : public Hud
{
public:
	static TextOverlays* create();

private:
	typedef Hud super;
	TextOverlays();
	virtual ~TextOverlays() = default;

	void onEnter() override;
	void onExit() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;
	void runLabelOverEntity(PlatformerEntity* target, LocalizedLabel* label);
};
