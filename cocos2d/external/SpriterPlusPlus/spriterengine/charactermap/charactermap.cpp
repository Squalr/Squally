#include "charactermap.h"

namespace SpriterEngine
{

	CharacterMap::CharacterMap()
	{
	}


	void CharacterMap::applyCharacterMap(FileReferenceVector *mappedFiles)
	{
		for (auto& it : mapInstructions)
		{
			it.applyMapInstruction(mappedFiles);
		}
	}

	void CharacterMap::appendMapInstruction(int initialFileToReplaceIndex, File *replacementFile)
	{
			mapInstructions.push_back(CharacterMapInstruction(initialFileToReplaceIndex, replacementFile));
	}

}
