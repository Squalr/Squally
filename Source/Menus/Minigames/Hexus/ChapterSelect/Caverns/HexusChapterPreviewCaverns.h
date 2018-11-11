#pragma once
#include "cocos2d.h"

#include "Engine/UI/Controls/MenuSprite.h"
#include "Menus/Minigames/Hexus/ChapterSelect/HexusChapterPreview.h"
#include "Resources.h"

using namespace cocos2d;

class HexusChapterPreviewCaverns : public HexusChapterPreview
{
public:
	static HexusChapterPreviewCaverns * create();

	static const std::string stringKeyChapterName;

protected:
	HexusChapterPreviewCaverns();
	~HexusChapterPreviewCaverns();

private:
	void initializePositions() override;
};
