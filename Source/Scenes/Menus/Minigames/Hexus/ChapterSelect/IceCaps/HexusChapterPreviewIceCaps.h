#pragma once
#include "cocos2d.h"
#include "Resources.h"

#include "Engine/UI/Controls/MenuSprite.h"
#include "Scenes/Menus/Minigames/Hexus/ChapterSelect/HexusChapterPreview.h"

using namespace cocos2d;

class HexusChapterPreviewIceCaps : public HexusChapterPreview
{
public:
	static HexusChapterPreviewIceCaps * create();

	static const std::string stringKeyChapterName;

protected:
	HexusChapterPreviewIceCaps();
	~HexusChapterPreviewIceCaps();

private:
	void initializePositions() override;
};
