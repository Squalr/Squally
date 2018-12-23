#pragma once
#include <string>

#include "Menus/Minigames/Hexus/ChapterSelect/HexusChapterPreview.h"

class HexusChapterPreviewRuins : public HexusChapterPreview
{
public:
	static HexusChapterPreviewRuins* create();

	static const std::string SaveKeyChapterName;

protected:
	HexusChapterPreviewRuins();
	~HexusChapterPreviewRuins();

private:
	void initializePositions() override;
};
