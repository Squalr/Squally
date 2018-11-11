#pragma once
#include "cocos2d.h"

#include "Engine/UI/Controls/MenuSprite.h"
#include "Menus/Minigames/Hexus/ChapterSelect/HexusChapterPreview.h"
#include "Resources.h"

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
