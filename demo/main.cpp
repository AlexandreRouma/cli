#include <stdio.h>
#include "cli.h"

int main(int argc, char** argv) {
    // Define command line interface
    cli::Interface iface;
    iface.arg("addr", 'a', "0.0.0.0", "Server mode address");
    iface.arg("autostart", 0, false, "Automatically start the SDR after loading");
    iface.arg("con", 'c', false, "Show console on Windows");
    iface.arg("port", 'p', 5459, "Server mode port");

    // Add a subcommand everyone in europe would enjoy running
    iface.subcmd("nukefrance", cli::Interface(), "Nuke france I guess");

    // Other useless bullshit
    cli::Interface someshit;
    someshit.arg("shit", 's', "bull", "Some description");
    iface.subcmd("someshit", someshit, "Print some shit idfk");

    // Parse command line
    cli::Command cmd;
    try {
        cmd = cli::parse(iface, argc, argv);
    }
    catch (const std::exception& e) {
        fprintf(stderr, "ERROR: %s\n", e.what());
        return -1;
    }
    
    // Dump the result
    while (true) {
        printf("=== %s ===\n", cmd.command.c_str());
        printf("Values: ");
        for (const auto& val : cmd.values) {
            printf("'%s' ", val.c_str());
        }
        printf("\n");
        
        // If there's no subcommand, stop
        if (!cmd.subcommand) { break; }

        cli::Command cmd;
        // Works
        auto test = *cmd.subcommand;
        cmd = test;
        // Crashes
        cmd = *cmd.subcommand;

        printf("%s\n", test.command.c_str());
        //cmd = *cmd.subcommand;
    }

    return 0;
}