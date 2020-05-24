#pragma once

#include <string>

class Voices
{
public:
	enum class VoiceType
	{
		Human,
		Droid,
		Orc,
		Demon,
		Ghost,
	};

	static std::string GetNextVoiceShort(VoiceType voiceType = VoiceType::Human);
	static std::string GetNextVoiceMedium(VoiceType voiceType = VoiceType::Human);
	static std::string GetNextVoiceLong(VoiceType voiceType = VoiceType::Human);
	static std::string GetNextVoiceQuestion(VoiceType voiceType = VoiceType::Human);
	static std::string GetNextVoiceLaugh(VoiceType voiceType = VoiceType::Human);

protected:

private:
	static std::string GetNextVoiceHumanShort();
	static std::string GetNextVoiceHumanMedium();
	static std::string GetNextVoiceHumanLong();
	static std::string GetNextVoiceHumanQuestion();
	
	static std::string GetNextVoiceDroidShort();
	static std::string GetNextVoiceDroidMedium();
	static std::string GetNextVoiceDroidLong();
	static std::string GetNextVoiceDroidQuestion();
	
	static std::string GetNextVoiceOrcShort();
	static std::string GetNextVoiceOrcMedium();
	static std::string GetNextVoiceOrcLong();
	static std::string GetNextVoiceOrcQuestion();
	
	static std::string GetNextVoiceDemonShort();
	static std::string GetNextVoiceDemonMedium();
	static std::string GetNextVoiceDemonLong();
	static std::string GetNextVoiceDemonQuestion();

	static std::string GetNextVoiceGhostShort();
	static std::string GetNextVoiceGhostMedium();
	static std::string GetNextVoiceGhostLong();
	static std::string GetNextVoiceGhostQuestion();
};
