#pragma once

#include "Engine/SmartNode.h"

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
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;
};
