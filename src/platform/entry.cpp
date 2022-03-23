#include "entry.hpp"

int geodeEntry(void* platformData) {
    // setup internals

    if (!Geode::get()) {
        Geode::platformMessageBox(
            "Unable to Load Geode!",
            "There was an unknown fatal error setting up "
            "internal tools and Geode can not be loaded. "
            "(Geode::get returned nullptr)"
        );
    }

    // if (!geode::core::initialize()) {
    //     Geode::platformMessageBox(
    //         "Unable to load Geode!",
    //         "There was an unknown fatal error setting up "
    //         "internal tools and Geode can not be loaded. "
    //         "(Unable to set up hook manager)"
    //     );
    // }

    Interface::get()->init(InternalMod::get());

    if (!Geode::get()->setup()) {
        // if we've made it here, Geode will 
        // be gettable (otherwise the call to 
        // setup would've immediately crashed)

        Geode::platformMessageBox(
            "Unable to Load Geode!",
            "There was an unknown fatal error setting up "
            "internal tools and Geode can not be loaded. "
            "(Geode::setup) returned false"
        );
        return 1;
    }

    InternalMod::get()->log()
        << Severity::Debug
        << "Loaded internal Geode class";

    // set up loader, load mods, etc.
    if (!Loader::get()->setup()) {
        Geode::get()->platformMessageBox(
            "Unable to Load Geode!",
            "There was an unknown fatal error setting up "
            "the loader and Geode can not be loaded."
        );
        delete Geode::get();
        return 1;
    }

    InternalMod::get()->log()
        << Severity::Debug
        << "Set up loader";

    // debugging console
    #ifdef GEODE_PLATFORM_CONSOLE
    InternalMod::get()->log()
        << Severity::Debug
        << "Loading Console...";

    Geode::get()->setupPlatformConsole();
    Geode::get()->awaitPlatformConsole();
    Geode::get()->closePlatformConsole();

    InternalMod::get()->log()
        << Severity::Debug
        << "Cleaning up...";

    //delete Geode::get();
    #endif

    InternalMod::get()->log()
        << Severity::Debug
        << "Entry done.";
    return 0;
}
