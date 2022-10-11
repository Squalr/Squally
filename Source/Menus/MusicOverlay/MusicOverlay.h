#pragma once

#include "Engine/UI/HUD/Hud.h"

namespace cocos2d
{
	class Sprite;
};

class LocalizedLabel;
class LocalizedString;
class Music;

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

	void showOverlayForMusic(Music* music);

	cocos2d::Node* contentNode = nullptr;
	LocalizedLabel* musicLabel = nullptr;
	LocalizedLabel* artistLabel = nullptr;
	cocos2d::Sprite* note = nullptr;
	LocalizedString* musicString = nullptr;
	LocalizedString* artistString = nullptr;

	static std::string CachedLastPlayedMusic;

	static const cocos2d::Vec2 ScrollOutDelta;
};
