#include "SCPlayBGM.h"
#include "BackgroundMusicManager.h"

ScriptReader::SCPlayBGM::SCPlayBGM(ScriptReader *reader, std::string key)
	:key(key)
{
	this->reader = reader;
	this->type = PlayBGM;
}


ScriptReader::SCPlayBGM::~SCPlayBGM()
{
}

void ScriptReader::SCPlayBGM::execute(cocos2d::CCNode* stage)
{
	reader->playBackgroundMusic(key);

	reader->nextScript();
}
