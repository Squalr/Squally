#pragma once
#include "cocos2d.h"
#include "Resources.h"

#include "Engine/UI/Controls/MenuSprite.h"
#include "Scenes/Menus/Minigames/Hexus/ChapterSelect/HexusChapterPreview.h"

using namespace cocos2d;

class HexusChapterPreviewRuins : public HexusChapterPreview
{
public:
	static HexusChapterPreviewRuins * create();

protected:
	HexusChapterPreviewRuins();
	~HexusChapterPreviewRuins();

private:
	void initializePositions() override;
};
