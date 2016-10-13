#include "SCStopBGM.h"


ScriptReader::SCStopBGM::SCStopBGM(ScriptReader *reader)
{
	this->reader = reader;
	this->type = StopBGM;
}


ScriptReader::SCStopBGM::~SCStopBGM()
{
}

void ScriptReader::SCStopBGM::execute(cocos2d::CCNode* stage)
{
	reader->stopBackgroundMusic();

	reader->nextScript();
}
