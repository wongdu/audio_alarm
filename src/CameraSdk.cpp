#include "CameraSdk.h"

CameraSdk::CameraSdk():devIp(""), devPort(0), userName(""), usrPassword(""), strAudioFileName(""){
	playTimeType = PlayTimeType::UnSupported;
	playTime = 0;
	playedTime = 0;
}

CameraSdk::~CameraSdk() {

}
