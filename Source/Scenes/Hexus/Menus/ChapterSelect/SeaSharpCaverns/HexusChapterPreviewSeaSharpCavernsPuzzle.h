#pragma once

#include "Scenes/Hexus/Menus/ChapterSelect/HexusChapterPreview.h"

class HexusChapterPreviewSeaSharpCavernsPuzzle : public HexusChapterPreview
{
public:
	static HexusChapterPreviewSeaSharpCavernsPuzzle* create();

	static const std::string SaveKeyChapterName;

protected:
	HexusChapterPreviewSeaSharpCavernsPuzzle();
	~HexusChapterPreviewSeaSharpCavernsPuzzle();

private:
	typedef HexusChapterPreview super;
	void initializePositions() override;
};
