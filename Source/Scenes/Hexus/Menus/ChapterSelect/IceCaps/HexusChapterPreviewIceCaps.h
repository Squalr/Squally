#pragma once

#include "Scenes/Hexus/Menus/ChapterSelect/HexusChapterPreview.h"

class HexusChapterPreviewIceCaps : public HexusChapterPreview
{
public:
	static HexusChapterPreviewIceCaps* create();

	static const std::string SaveKeyChapterName;

protected:
	HexusChapterPreviewIceCaps();
	~HexusChapterPreviewIceCaps();

private:
	typedef HexusChapterPreview super;
	void initializePositions() override;
};
