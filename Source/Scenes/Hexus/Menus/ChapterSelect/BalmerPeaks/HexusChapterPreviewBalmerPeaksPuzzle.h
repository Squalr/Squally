#pragma once

#include "Scenes/Hexus/Menus/ChapterSelect/HexusChapterPreview.h"

class HexusChapterPreviewBalmerPeaksPuzzle : public HexusChapterPreview
{
public:
	static HexusChapterPreviewBalmerPeaksPuzzle* create();

	static const std::string SaveKeyChapterName;

protected:
	HexusChapterPreviewBalmerPeaksPuzzle();
	~HexusChapterPreviewBalmerPeaksPuzzle();

private:
	typedef HexusChapterPreview super;
	void initializePositions() override;
};
