#pragma once

#include "Engine/SmartNode.h"

class LocalizedLabel;
class LocalizedString;
class PlatformerEntity;

class TextOverlays : public SmartNode
{
public:
	static TextOverlays* create();

private:
	typedef SmartNode super;
	TextOverlays();
	virtual ~TextOverlays() = default;

	void onEnter() override;
	void onExit() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;
	void runLabelOverEntity(PlatformerEntity* target, LocalizedLabel* label);
};
