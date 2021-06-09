//#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <string>
#include <thread>
#include <fstream>
#include <memory>

#include <glog/logging.h>

#include "AudioAlarmServer.h"

using namespace std;
using namespace audio_alarm;

static void SignalHandle(const char* data, int size);
static bool CheckLogPath(const std::string& strLogPath);

static constexpr size_t kMsgQueueSize = 1000;

int main(int argc, char* argv[]) {
	FLAGS_colorlogtostderr = false;
	FLAGS_alsologtostderr = true;
	FLAGS_timestamp_in_logfile_name = true;
	FLAGS_logbufsecs = 0;
	FLAGS_max_log_size = 10;  //MB

	// Make sure stderr is not buffered as stderr seems to be buffered on recent windows.
	setbuf(stderr, NULL);

	google::InitGoogleLogging(argv[0]);

	std::string strLogPath = get_current_dir_name();
	strLogPath = strLogPath.substr(0, strLogPath.find_last_of("/")+1);
	if (!CheckLogPath(strLogPath+"log")) {
		LOG(ERROR) << "check log directory failed";
		return -1;	
	}
	strLogPath = strLogPath + "log/auido_alarm_";
	google::SetLogDestination(google::GLOG_INFO, strLogPath.c_str());

	google::InstallFailureSignalHandler();
	google::InstallFailureWriter(&SignalHandle);

	LOG(INFO) << "start run audio alarm server";

	std::shared_ptr<AudioAlarmServer> ptrAudioAlarmServer;
	try
	{
		ptrAudioAlarmServer = std::make_shared<AudioAlarmServer>();
		ptrAudioAlarmServer->Initialize(kMsgQueueSize, std::thread::hardware_concurrency());
		ptrAudioAlarmServer->RegisterService();;
		ptrAudioAlarmServer->Start();

	}
	catch (const std::exception& e)
	{
		LOG(ERROR) << "caught exception:"<<e.what();
	}

	ptrAudioAlarmServer->Stop();
	google::ShutdownGoogleLogging();
	return 0;
}

static void SignalHandle(const char* data, int size)
{
	std::ofstream fs_("core_dump.log", std::ios::app);
	std::string str_ = std::string(data, size);
	fs_ << str_;
	LOG(ERROR) << str_;
	fs_.close();
}

static bool CheckLogPath(const std::string& strLogPath) {
	if (!access(strLogPath.c_str(),0)) {
		return true;
	}

	if (mkdir(strLogPath.c_str(), 0777) == -1) {	
		return false;
	}

	return true;
}