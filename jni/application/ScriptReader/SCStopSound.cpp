#include "SCStopSound.h"


ScriptReader::SCStopSound::SCStopSound(ScriptReader *reader)
{
	this->reader = reader;
	this->type = StopSd;
}


ScriptReader::SCStopSound::~SCStopSound()
{
}

void ScriptReader::SCStopSound::execute(cocos2d::CCNode* stage)
{
	(reader->stopSoundObj->*reader->stopSound)();

	reader->nextScript();
}
