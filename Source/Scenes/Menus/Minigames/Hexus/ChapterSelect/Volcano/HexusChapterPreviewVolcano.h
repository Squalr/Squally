#pragma once
#include "cocos2d.h"
#include "Resources.h"

#include "Engine/UI/Controls/MenuSprite.h"
#include "Scenes/Menus/Minigames/Hexus/ChapterSelect/HexusChapterPreview.h"

using namespace cocos2d;

class HexusChapterPreviewVolcano : public HexusChapterPreview
{
public:
	static HexusChapterPreviewVolcano * create();

	static const std::string stringKeyChapterName;

protected:
	HexusChapterPreviewVolcano();
	~HexusChapterPreviewVolcano();

private:
	void initializePositions() override;
};
