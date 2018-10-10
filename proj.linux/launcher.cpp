#include <stdlib.h>
#include <unistd.h>

#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include <gtkmm.h>

#include "client/linux/crash_generation/crash_generation_server.h"

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

    // ------------------ Crash Monitor ---------------------
    // create gtk app
    auto app = Gtk::Application::create(argc, argv, "com.squalr.squally.launcher");
    bool gameCrashed = false;

    // if child exits and the game hasn't crashed, exit monitor
    Glib::signal_child_watch().connect([&app, &gameCrashed] (int, int) {
        if (!gameCrashed) {
            app->quit();
        }
    }, childId);

    // create upload crash dump dialog
    Gtk::Label mainText, secondaryText;
    mainText.set_markup("<b>Squally crashed out of the Vapor Web and his head exploded</b>");
    mainText.set_line_wrap();
    mainText.set_line_wrap_mode(Pango::WRAP_WORD);

    secondaryText.set_markup("Mr Muskrat will be cleaning the walls for weeks, can you send us a bug report so we can "
            "keep this from happening again?");
    secondaryText.set_line_wrap();
    secondaryText.set_line_wrap_mode(Pango::WRAP_WORD);

    Gtk::VBox labelBox;
    labelBox.add(mainText);
    labelBox.add(secondaryText);
    //labelBox.set_size_request(-1, 64);

    Gtk::HBox contentBox;
    Gtk::Image imageIcon(basePath + "/Resources/icon.ico");
    contentBox.add(imageIcon);
    contentBox.add(labelBox);

    Gtk::TextView reportTextView;
    //reportTextView.set_size_request(-1, 64);

    Gtk::Dialog dialog("Squally Crash Monitor", Gtk::DIALOG_MODAL);
    dialog.add_button("Yes", Gtk::RESPONSE_YES);
    dialog.add_button("No", Gtk::RESPONSE_NO);
    dialog.get_content_area()->add(contentBox);
    dialog.get_content_area()->add(reportTextView);

    dialog.signal_response().connect([&app, &dialog] (int response)
    {
        switch (response)
        {
            case Gtk::RESPONSE_YES:
                std::cout << "uploading crash dump: " << crashDumpPath << std::endl;
                break;

            case Gtk::RESPONSE_NO:
                break;
        }

        // hide crash upload dialog box
        dialog.hide();
        app->quit();
    });

    // dispatcher that kicks off crash upload question
    Glib::Dispatcher crashDumpNotifier;
    crashDumpNotifier.connect([&app, &gameCrashed, &dialog] () {
        gameCrashed = true;
        dialog.show_all();
    });

    // start crashdump server (pass dispatcher)
    google_breakpad::CrashGenerationServer server(serverDescriptor, &onClientDumpRequestCallback, &crashDumpNotifier,
            nullptr, nullptr, true, &dumpPath);
    server.Start();

    // run gtk application to provide crash dialog
    app->hold();
    return app->run();
}