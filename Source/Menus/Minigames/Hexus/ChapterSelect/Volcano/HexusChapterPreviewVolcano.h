#pragma once
#include <string>

#include "Menus/Minigames/Hexus/ChapterSelect/HexusChapterPreview.h"

class HexusChapterPreviewVolcano : public HexusChapterPreview
{
public:
	static HexusChapterPreviewVolcano * create();

	static const std::string SaveKeyChapterName;

protected:
	HexusChapterPreviewVolcano();
	~HexusChapterPreviewVolcano();

private:
	void initializePositions() override;
};
