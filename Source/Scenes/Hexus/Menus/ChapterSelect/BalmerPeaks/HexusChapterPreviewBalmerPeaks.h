#pragma once

#include "Scenes/Hexus/Menus/ChapterSelect/HexusChapterPreview.h"

class HexusChapterPreviewBalmerPeaks : public HexusChapterPreview
{
public:
	static HexusChapterPreviewBalmerPeaks* create();

	static const std::string SaveKeyChapterName;

protected:
	HexusChapterPreviewBalmerPeaks();
	~HexusChapterPreviewBalmerPeaks();

private:
	typedef HexusChapterPreview super;
	void initializePositions() override;
};
