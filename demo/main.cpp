#include <stdio.h>
#include "cli.h"
#include <inttypes.h>

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
        printf("Values:");
        for (const auto& val : cmd.values) {
            printf(" '%s'", val.c_str());
        }
        printf("\n\nArguments:\n");
        for (const auto& [name, val] : cmd.arguments) {
            switch (val.type) {
            case cli::VAL_TYPE_STRING:
                printf("'%s': %s\n", name.c_str(), ((std::string)val).c_str()); break;
            case cli::VAL_TYPE_UNSIGNED_INTEGER:
                printf("'%s': %" PRIu64 "\n", name.c_str(), (uint64_t)val); break;
            case cli::VAL_TYPE_SIGNED_INTEGER:
                printf("'%s': %" PRId64 "\n", name.c_str(), (int64_t)val); break;
            case cli::VAL_TYPE_FLOATING:
                printf("'%s': %lf\n", name.c_str(), (double)val); break;
            case cli::VAL_TYPE_BOOLEAN:
                printf("'%s': %s\n", name.c_str(), val ? "True" : "False"); break;
            default:
                printf("Uknown type: %d\n", val.type); break;
            }
        }
        printf("\n");
        
        // If there's no subcommand, stop
        if (!cmd.subcommand) { break; }

        cmd = *cmd.subcommand;
    }

    return 0;
}