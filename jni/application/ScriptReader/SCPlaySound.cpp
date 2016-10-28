#include "SCPlaySound.h"
#include "SoundManager.h"

ScriptReader::SCPlaySound::SCPlaySound(ScriptReader *reader, std::string key)
	:key(key)
{
	this->reader = reader;
	this->type = PlaySd;
}


ScriptReader::SCPlaySound::~SCPlaySound()
{
}

void ScriptReader::SCPlaySound::execute(cocos2d::CCNode* stage)
{
	std::string sound = SM->getSound(key);
	if (sound.compare("") == 0)
	{
		CCLOG("SC> unfine bgm %s", key.c_str());
	}
	else
	{
		(reader->playSoundObj->*reader->playSound)(sound);
	}

	reader->nextScript();
}
