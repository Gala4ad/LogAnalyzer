#include "LogAnalyzer.h"
#include "log_line_parser.h"

#include <cassert>
#include "argparse.hpp"


int main(int argc, char* argv[]) {
    argparse::ArgumentParser program("LogAnalyzer", "Log Analyzer 1.0");

    program.add_argument("input_file")
        .help("Path to log file");

    program.add_argument("-st", "--statistics")
        .help("Detailed statistics")
        .default_value(false)
        .implicit_value(true);

    program.add_argument("--top")
        .help("Top N function")
        .default_value(10)
        .scan<'i', int>();

    try {
        program.parse_args(argc, argv);
    }
    catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        return 1;
    }

    auto input_file = program.get<std::string>("input_file");
    auto statistic = program.get<bool>("--statistics");
    auto top_count = program.get<int>("--top");

    try {
        LogAnalyzer Logs;

        if (!Logs.loadData(input_file)) {
            Logs.sortFunctions();

            if (statistic) {
                Logs.getStatistic();
                Logs.getTopFunctions(top_count);
            }
            else
                Logs.getTopFunctions(top_count);
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Îøèáêà: " << e.what() << std::endl;
        return 1;
    }


	return 0;
}