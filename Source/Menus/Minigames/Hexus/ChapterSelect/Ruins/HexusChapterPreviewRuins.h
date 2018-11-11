#pragma once
#include "cocos2d.h"

#include "Engine/UI/Controls/MenuSprite.h"
#include "Menus/Minigames/Hexus/ChapterSelect/HexusChapterPreview.h"
#include "Resources.h"

using namespace cocos2d;

class HexusChapterPreviewRuins : public HexusChapterPreview
{
public:
	static HexusChapterPreviewRuins * create();

	static const std::string stringKeyChapterName;

protected:
	HexusChapterPreviewRuins();
	~HexusChapterPreviewRuins();

private:
	void initializePositions() override;
};
