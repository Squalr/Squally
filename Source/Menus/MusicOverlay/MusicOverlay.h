#pragma once

#include "Engine/UI/HUD/Hud.h"

namespace cocos2d
{
	class Sprite;
};

class LocalizedLabel;
class LocalizedString;
class Track;

class MusicOverlay : public Hud
{
public:
	static MusicOverlay* create();

protected:
	MusicOverlay();
	virtual ~MusicOverlay();
	
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef Hud super;

	void showOverlayForTrack(Track* track);

	cocos2d::Node* contentNode;
	LocalizedLabel* trackLabel;
	LocalizedLabel* artistLabel;
	cocos2d::Sprite* note;
	LocalizedString* trackString;
	LocalizedString* artistString;

	static std::string CachedLastPlayedTrack;

	static const cocos2d::Vec2 ScrollOutDelta;
};
