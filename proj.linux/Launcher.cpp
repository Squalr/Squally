#include <stdlib.h>
#include <unistd.h>

#include <fstream>
#include <future>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include <sys/utsname.h>

#include <gtkmm.h>

#include "client/linux/crash_generation/crash_generation_server.h"
#include "common/linux/http_upload.h"

#include "Config.h"
#include "Launcher.hpp"

namespace
{
    std::string crashDumpPath;

    // crash dump callback sets dump path and notifies glib event loop
    void onClientDumpRequestCallback(void* context, const google_breakpad::ClientInfo* clientInfo,
            const std::string* filePath)
    {
        crashDumpPath = *filePath;
        reinterpret_cast<Glib::Dispatcher*>(context)->emit();
    }

    std::string replaceAll(const std::string& str, const std::string& search, const std::string& replace)
    {
        std::string working = str;
        std::size_t pos = 0;
        while ((pos = working.find(search, pos)) != std::string::npos)
        {
            working.replace(pos, search.size(), replace);
        }
        return working;
    }

    // lsb_release parser
    std::string getPlatformVersionString()
    {
        std::string distribution;
        std::string version;

        // find relevant entries
        std::ifstream releaseFile("/etc/lsb-release");
        if (!releaseFile.is_open()) {
            return "unknown";
        }
        while (releaseFile)
        {
            std::string line;
            std::getline(releaseFile, line);
            
            // distribution id entry
            if (!line.compare(0, 10, "DISTRIB_ID"))
            {
                distribution = replaceAll(line.substr(11), "\"", "");
            }
            else if (!line.compare(0, 15, "DISTRIB_RELEASE"))
            {
                version = replaceAll(line.substr(16), "\"", "");
            }
        }

        // start building version string
        std::string versionString = distribution + (version.size() ? ("_" + version) : "");

        // get kernel version
        struct utsname kver{};
        if (!uname(&kver))
        {
            versionString += "_" + std::string(kver.release);
        }

        return versionString;
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
        std::cerr << "[Squally Launcher] failed to create crash dump directory (" << dumpPath << ")" << std::endl;
        return EXIT_FAILURE;
    }

    // create channel for client and server to communicate
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

    // ------------------ Crash Monitor ---------------------
    // create gtk app
    bool gameCrashed = false;
    auto app = Gtk::Application::create(argc, argv, "com.squalr.squally.launcher");

    // use builder to crash upload dialog
    auto builder = Gtk::Builder::create_from_string(launcherDialogXML);

    // get text view handle
    Gtk::TextView* reportTextView = nullptr;
    builder->get_widget<Gtk::TextView>("reportText", reportTextView);

    // set the icon
    Gtk::Image* reportImage = nullptr;
    builder->get_widget<Gtk::Image>("reportImage", reportImage);
    reportImage->set(basePath + "/Resources/Public/AppIcon.ico");

    // get dialog handle
    Gtk::Dialog* dialog = nullptr;
    builder->get_widget<Gtk::Dialog>("reportDialog", dialog);
    dialog->set_title("Squally Crash Reporter");
    dialog->add_button("Yes", Gtk::RESPONSE_YES);
    dialog->add_button("No", Gtk::RESPONSE_NO);
    dialog->set_default_size(400, 100);

    // if child exits and the game hasn't crashed, exit monitor
    Glib::signal_child_watch().connect([app, &gameCrashed] (int, int) {
        if (!gameCrashed) {
            app->quit();
        }
    }, childId);

    // dispatcher that kicks off crash upload question
    Glib::Dispatcher crashDumpNotifier;
    crashDumpNotifier.connect([app, &gameCrashed, dialog] () {
        gameCrashed = true;
        dialog->show_all();
    });

    // dispatcher that quits launcher when upload is done
    Glib::Dispatcher postUploadNotifier;
    postUploadNotifier.connect([app] () {
        app->quit();
    });
    
    // on crash upload reponse, 
    dialog->signal_response().connect([app, dialog, reportTextView, &postUploadNotifier] (int response)
    {
        // hide crash upload dialog box
        dialog->hide();

        // if user does not want to upload a crash dump, exit now
        if (response == Gtk::RESPONSE_NO) {
            app->quit();
            return;
        }

        // upload crash dump (on background thread)
        std::string reportText = reportTextView->get_buffer()->get_text();
        std::thread([reportText, &postUploadNotifier] () {
            std::cerr << "[Squally Launcher] starting crash dump upload." << std::endl;

            std::map<std::string, std::string> parameters = {
                { "app-version", std::to_string(VERSION_MAJOR) + "." + std::to_string(VERSION_MINOR) + "."
                    + std::to_string(VERSION_PATCH) },
                { "platform-version", getPlatformVersionString() },
                { "platform", "linux" },
                { "report", reportText }
            };

            std::map<std::string, std::string> files = {
                { "minidump", crashDumpPath }
            };

            // send crash dump
            std::string response, error;
            google_breakpad::HTTPUpload::SendRequest("https://squallygame.com/api/v1/crashreport", parameters, files,
                    "", "", "", &response, nullptr, &error);
            std::cerr << "[Squally Launcher] crash dump upload complete." << std::endl;
            postUploadNotifier.emit();
        }).detach();
    });

    // start crashdump server (pass dispatcher)
    google_breakpad::CrashGenerationServer server(serverDescriptor, &onClientDumpRequestCallback, &crashDumpNotifier,
            nullptr, nullptr, true, &dumpPath);
    server.Start();

    // run gtk application to provide crash dialog
    app->hold();
    return app->run();
}