#include "Voices.h"

#include "Resources/SoundResources.h"

std::string Voices::GetNextVoiceShort(VoiceType voiceType)
{
	switch(voiceType)
	{
		default:
		case VoiceType::Human:
		{
			return Voices::GetNextVoiceHumanShort();
		}
		case VoiceType::Droid:
		{
			return Voices::GetNextVoiceDroidShort();
		}
		case VoiceType::Orc:
		{
			return Voices::GetNextVoiceOrcShort();
		}
		case VoiceType::Demon:
		{
			return Voices::GetNextVoiceDemonShort();
		}
		case VoiceType::Ghost:
		{
			return Voices::GetNextVoiceGhostShort();
		}
	}
}

std::string Voices::GetNextVoiceMedium(VoiceType voiceType)
{
	switch(voiceType)
	{
		default:
		case VoiceType::Human:
		{
			return Voices::GetNextVoiceHumanMedium();
		}
		case VoiceType::Droid:
		{
			return Voices::GetNextVoiceDroidMedium();
		}
		case VoiceType::Orc:
		{
			return Voices::GetNextVoiceOrcMedium();
		}
		case VoiceType::Demon:
		{
			return Voices::GetNextVoiceDemonMedium();
		}
		case VoiceType::Ghost:
		{
			return Voices::GetNextVoiceGhostMedium();
		}
	}
}

std::string Voices::GetNextVoiceLong(VoiceType voiceType)
{
	switch(voiceType)
	{
		default:
		case VoiceType::Human:
		{
			return Voices::GetNextVoiceHumanLong();
		}
		case VoiceType::Droid:
		{
			return Voices::GetNextVoiceDroidLong();
		}
		case VoiceType::Orc:
		{
			return Voices::GetNextVoiceOrcLong();
		}
		case VoiceType::Demon:
		{
			return Voices::GetNextVoiceDemonLong();
		}
		case VoiceType::Ghost:
		{
			return Voices::GetNextVoiceGhostLong();
		}
	}
}

std::string Voices::GetNextVoiceQuestion(VoiceType voiceType)
{
	switch(voiceType)
	{
		default:
		case VoiceType::Human:
		{
			return Voices::GetNextVoiceHumanQuestion();
		}
		case VoiceType::Droid:
		{
			return Voices::GetNextVoiceDroidQuestion();
		}
		case VoiceType::Orc:
		{
			return Voices::GetNextVoiceOrcQuestion();
		}
		case VoiceType::Demon:
		{
			return Voices::GetNextVoiceDemonQuestion();
		}
		case VoiceType::Ghost:
		{
			return Voices::GetNextVoiceGhostQuestion();
		}
	}
}

std::string Voices::GetNextVoiceLaugh(VoiceType voiceType)
{
	switch(voiceType)
	{
		default:
		case VoiceType::Human:
		{
			return SoundResources::Platformer_Entities_Orc_OrcLaugh1;
		}
		case VoiceType::Droid:
		{
			return SoundResources::Platformer_Entities_Droid_DroidLaugh1;
		}
		case VoiceType::Orc:
		{
			return SoundResources::Platformer_Entities_Orc_OrcLaugh1;
		}
		case VoiceType::Demon:
		{
			return SoundResources::Platformer_Entities_Demon_Laugh1;
		}
		case VoiceType::Ghost:
		{
			return SoundResources::Platformer_Entities_Orc_OrcLaugh1;
		}
	}
}

std::string Voices::GetNextVoiceHumanShort()
{
	static unsigned int VoiceIncrement = 0;

	VoiceIncrement++;

	switch(VoiceIncrement % 2)
	{
		default:
		case 1:
		{
			return SoundResources::Platformer_Entities_Generic_ChatterShort1;
		}
		case 0:
		{
			return SoundResources::Platformer_Entities_Generic_ChatterShort2;
		}
	}
}

std::string Voices::GetNextVoiceHumanMedium()
{
	static unsigned int VoiceIncrement = 0;
	
	VoiceIncrement++;

	switch(VoiceIncrement % 4)
	{
		default:
		case 1:
		{
			return SoundResources::Platformer_Entities_Generic_ChatterMedium1;
		}
		case 2:
		{
			return SoundResources::Platformer_Entities_Generic_ChatterMedium2;
		}
		case 3:
		{
			return SoundResources::Platformer_Entities_Generic_ChatterMedium3;
		}
		case 0:
		{
			return SoundResources::Platformer_Entities_Generic_ChatterMedium4;
		}
	}
}

std::string Voices::GetNextVoiceHumanLong()
{
	static unsigned int VoiceIncrement = 0;
	
	VoiceIncrement++;

	switch(VoiceIncrement % 1)
	{
		default:
		case 0:
		{
			return SoundResources::Platformer_Entities_Generic_ChatterLong1;
		}
	}
}

std::string Voices::GetNextVoiceHumanQuestion()
{
	static unsigned int VoiceIncrement = 0;
	
	VoiceIncrement++;

	switch(VoiceIncrement % 1)
	{
		default:
		case 0:
		{
			return SoundResources::Platformer_Entities_Generic_ChatterQuestion1;
		}
	}
}

std::string Voices::GetNextVoiceDroidShort()
{
	static unsigned int VoiceIncrement = 0;
	
	VoiceIncrement++;

	switch(VoiceIncrement % 4)
	{
		default:
		case 1:
		{
			return SoundResources::Platformer_Entities_Droid_DroidShort1;
		}
		case 2:
		{
			return SoundResources::Platformer_Entities_Droid_DroidShort2;
		}
		case 3:
		{
			return SoundResources::Platformer_Entities_Droid_DroidShort3;
		}
		case 0:
		{
			return SoundResources::Platformer_Entities_Droid_DroidShort4;
		}
	}
}

std::string Voices::GetNextVoiceDroidMedium()
{
	static unsigned int VoiceIncrement = 0;
	
	VoiceIncrement++;

	switch(VoiceIncrement % 3)
	{
		default:
		case 1:
		{
			return SoundResources::Platformer_Entities_Droid_DroidMedium1;
		}
		case 2:
		{
			return SoundResources::Platformer_Entities_Droid_DroidMedium2;
		}
		case 0:
		{
			return SoundResources::Platformer_Entities_Droid_DroidMedium3;
		}
	}
}

std::string Voices::GetNextVoiceDroidLong()
{
	static unsigned int VoiceIncrement = 0;
	
	VoiceIncrement++;

	switch(VoiceIncrement % 2)
	{
		default:
		case 1:
		{
			return SoundResources::Platformer_Entities_Droid_DroidLong1;
		}
		case 0:
		{
			return SoundResources::Platformer_Entities_Droid_DroidLong2;
		}
	}
}

std::string Voices::GetNextVoiceDroidQuestion()
{
	static unsigned int VoiceIncrement = 0;
	
	VoiceIncrement++;

	switch(VoiceIncrement % 4)
	{
		default:
		case 1:
		{
			return SoundResources::Platformer_Entities_Droid_DroidQuestion1;
		}
		case 2:
		{
			return SoundResources::Platformer_Entities_Droid_DroidQuestion2;
		}
		case 3:
		{
			return SoundResources::Platformer_Entities_Droid_DroidQuestion3;
		}
		case 0:
		{
			return SoundResources::Platformer_Entities_Droid_DroidQuestion4;
		}
	}
}

std::string Voices::GetNextVoiceOrcShort()
{
	static unsigned int VoiceIncrement = 0;

	VoiceIncrement++;

	switch(VoiceIncrement % 1)
	{
		default:
		case 0:
		{
			return SoundResources::Platformer_Entities_Orc_OrcShort1;
		}
	}
}

std::string Voices::GetNextVoiceOrcMedium()
{
	static unsigned int VoiceIncrement = 0;
	
	VoiceIncrement++;

	switch(VoiceIncrement % 1)
	{
		default:
		case 0:
		{
			return SoundResources::Platformer_Entities_Orc_OrcMedium1;
		}
	}
}

std::string Voices::GetNextVoiceOrcLong()
{
	static unsigned int VoiceIncrement = 0;
	
	VoiceIncrement++;

	switch(VoiceIncrement % 1)
	{
		default:
		case 0:
		{
			return SoundResources::Platformer_Entities_Orc_OrcLong1;
		}
	}
}

std::string Voices::GetNextVoiceOrcQuestion()
{
	static unsigned int VoiceIncrement = 0;
	
	VoiceIncrement++;

	switch(VoiceIncrement % 1)
	{
		default:
		case 0:
		{
			return SoundResources::Platformer_Entities_Orc_OrcQuestion1;
		}
	}
}

std::string Voices::GetNextVoiceDemonShort()
{
	static unsigned int VoiceIncrement = 0;

	VoiceIncrement++;

	switch(VoiceIncrement % 2)
	{
		default:
		case 1:
		{
			return SoundResources::Platformer_Entities_Demon_DemonShort1;
		}
		case 0:
		{
			return SoundResources::Platformer_Entities_Demon_DemonShort2;
		}
	}
}

std::string Voices::GetNextVoiceDemonMedium()
{
	static unsigned int VoiceIncrement = 0;
	
	VoiceIncrement++;

	switch(VoiceIncrement % 2)
	{
		default:
		case 1:
		{
			return SoundResources::Platformer_Entities_Demon_DemonMedium1;
		}
		case 0:
		{
			return SoundResources::Platformer_Entities_Demon_DemonMedium2;
		}
	}
}

std::string Voices::GetNextVoiceDemonLong()
{
	static unsigned int VoiceIncrement = 0;
	
	VoiceIncrement++;

	switch(VoiceIncrement % 1)
	{
		default:
		case 0:
		{
			return SoundResources::Platformer_Entities_Demon_DemonLong1;
		}
	}
}

std::string Voices::GetNextVoiceDemonQuestion()
{
	static unsigned int VoiceIncrement = 0;
	
	VoiceIncrement++;

	switch(VoiceIncrement % 2)
	{
		default:
		case 1:
		{
			return SoundResources::Platformer_Entities_Demon_DemonQuestion1;
		}
		case 0:
		{
			return SoundResources::Platformer_Entities_Demon_DemonQuestion2;
		}
	}
}

std::string Voices::GetNextVoiceGhostShort()
{
	static unsigned int VoiceIncrement = 0;

	VoiceIncrement++;

	switch(VoiceIncrement % 1)
	{
		default:
		case 0:
		{
			return SoundResources::Platformer_Entities_Ghost_GhostShort1;
		}
	}
}

std::string Voices::GetNextVoiceGhostMedium()
{
	static unsigned int VoiceIncrement = 0;
	
	VoiceIncrement++;

	switch(VoiceIncrement % 1)
	{
		default:
		case 0:
		{
			return SoundResources::Platformer_Entities_Ghost_GhostMedium1;
		}
	}
}

std::string Voices::GetNextVoiceGhostLong()
{
	static unsigned int VoiceIncrement = 0;
	
	VoiceIncrement++;

	switch(VoiceIncrement % 1)
	{
		default:
		case 0:
		{
			return SoundResources::Platformer_Entities_Ghost_GhostLong1;
		}
	}
}

std::string Voices::GetNextVoiceGhostQuestion()
{
	static unsigned int VoiceIncrement = 0;
	
	VoiceIncrement++;

	switch(VoiceIncrement % 1)
	{
		default:
		case 0:
		{
			return SoundResources::Platformer_Entities_Ghost_GhostMedium1;
		}
	}
}
