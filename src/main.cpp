//#include <iostream>
#include <unistd.h>
#include <string>
#include <thread>
#include <fstream>
#include <memory>

#include <glog/logging.h>

#include "AudioAlarmServer.h"

using namespace std;
using namespace audio_alarm;

static void SignalHandle(const char* data, int size);

static constexpr size_t kMsgQueueSize = 1000;

int main(int argc, char* argv[]) {
	FLAGS_colorlogtostderr = false;
	FLAGS_alsologtostderr = true;
	FLAGS_timestamp_in_logfile_name = true;
	FLAGS_max_log_size = 100; //MB

	// Make sure stderr is not buffered as stderr seems to be buffered on recent windows.
	setbuf(stderr, NULL);

	google::InitGoogleLogging(argv[0]);

	//google::SetLogDestination(google::GLOG_INFO, local_conf_.log_path.c_str());
	google::SetLogDestination(google::GLOG_INFO, get_current_dir_name());
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
