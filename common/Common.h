#ifndef __Common_H__
#define __Common_H__

#include <string>

using uint32 = unsigned int;

enum class CameraType : unsigned char {
	Unknown,
	DaHua,
	HiK
};

enum class LatestMsgResult :unsigned char {
	DownLoadFailed,
	DownLoadOnly,
	Processed,
};

struct AlarmMsg {
	uint32 msgId;
	CameraType cameraType;
	std::string devIp;
	uint32 devPort;
	uint32 playDuration;
	std::string userName;
	std::string userPassword;
	std::string downloadUrl;
	std::string fileName;
	std::string md5Value;
};

#endif
