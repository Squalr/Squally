#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#include <future>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "client/linux/crash_generation/crash_generation_server.h"

namespace
{
    std::promise<void> gClientDone;

    void onClientDumpRequestCallback(void* context, const google_breakpad::ClientInfo* clientInfo,
            const std::string* filePath)
    {
        std::cout << "dumped: " << *filePath << std::endl;
    }

    void onClientExitingCallback(void* context, const google_breakpad::ClientInfo* clientInfo)
    {
        std::cout << "client exiting." << std::endl;
    }
}

int main(int argc, char **argv)
{
    // find game executable
    const std::string& launcher = argv[0];
    const std::string& basePath = launcher.substr(0, launcher.find_last_of('/'));
    const std::string& game = basePath + "/Squally";

    // come up with a unique session name
    const std::string& dumpPath = "/tmp/com.squalr.squally";
    int ret = mkdir(dumpPath.c_str(), 0700);
    if (ret && errno != EEXIST)
    {
        std::cerr << "[Squally Launcher] failed to create crash dump directory (" << dumpPath << ", " << ret << ")" << std::endl;
        return EXIT_FAILURE;
    }

    // create channel for client and server to communicate
    std::cerr << "[Squally Launcher] launching game: " << game << std::endl;
    int serverDescriptor, clientDescriptor;
    if (!google_breakpad::CrashGenerationServer::CreateReportChannel(&serverDescriptor, &clientDescriptor))
    {
        std::cerr << "[Squally Launcher] failed to create communication channel." << std::endl;
        return EXIT_FAILURE;
    }

    // run game
    pid_t childId = fork();
    if (!childId)
    {
        return execl(game.c_str(), game.c_str(), "-d", std::to_string(clientDescriptor).c_str(), nullptr);
    }
    else if (childId < 0)
    {
        std::cerr << "[Squally Launcher] failed to fork game process." << std::endl;
        return EXIT_FAILURE;
    }

    // wait for dumps
    google_breakpad::CrashGenerationServer server(serverDescriptor, &onClientDumpRequestCallback, nullptr,
            &onClientExitingCallback, nullptr, true, &dumpPath);
    server.Start();
    gClientDone.get_future().wait();
    return EXIT_SUCCESS;
}