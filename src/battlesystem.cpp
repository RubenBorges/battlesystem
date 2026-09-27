#include <cstdlib>
#include <print>
#include <string>

#include <actor.hpp>
#include <battlecalculator.hpp>
#include <datamanager.hpp>
#include <log.hpp>
#include <statistics.hpp>
#include <graph.hpp>

int main(int argc, char* argv[]) {
    // Establish basic command-line instructions
    if (argc < 3) {
        std::println("Usage:   {} [option 1] \"[option 2]\" [option 3] ...", argv[0]);
        return EXIT_FAILURE;
    }

    // STEP 0: PARSE COMMAND LINE
    const std::string model_path = argv[1];
    std::string inputQuery{argv[2]};
   
    return EXIT_SUCCESS;
}