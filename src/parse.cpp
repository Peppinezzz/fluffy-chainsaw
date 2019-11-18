#include <getopt.h>
#include <iostream>
#include <stdlib.h>
#include <string>

struct options_set_t {
    bool help{0};
    bool version{0};
    bool numbers{0};
    std::string numbers_list;
};

int main(int argc, char **argv) {
    options_set_t opts;

    while (true) {
        int option_index = 0;
        static option long_options[] = {
            {"help", no_argument, 0, 'h'},
            {"version", no_argument, 0, 'v'},
            {"numbers", required_argument, 0, 'n'},
            {0, 0, 0, 0}
        };

        int option = getopt_long(argc, argv, "hvn:", long_options, nullptr);
        if (option == -1) {
            break;
        }
        switch (option) {
        case 'h':
            opts.help = true;
            break;
        case 'v':
            opts.version = true;
            break;
        case 'n':
            opts.numbers = true;
            opts.numbers_list = optarg;
            break;
        default:
            break;
        }
    }

    if (opts.help) {
        std::cout << "Usage:\t\t" << argv[0] << " [-h] [--help] [-v] [--version] [-n] [--numbers]" << std::endl;
    }
    if (opts.version) {
        std::cout << "Version:\t0.1" << std::endl;
    }
    if (opts.numbers) {
        std::cout << "List arguments:\t";
        if (opts.numbers_list.find(",") == std::string::npos) {
            std::cout << opts.numbers_list << std::endl;
        } else {
            std::string arguments = opts.numbers_list;
            int last_pos = 0;
            size_t pos = 0;
            std::string token = "";
            while ((pos = arguments.find(",")) != std::string::npos) {
                token = arguments.substr(0, pos);
                std::cout << token << " ";
                arguments.erase(0, pos + 1);
            }
            std::cout << arguments << std::endl;
        }
    }

    return 0;
}
