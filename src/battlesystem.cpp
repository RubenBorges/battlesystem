#include <cstdlib>
#include <print>
#include <string>

#include <actor.hpp>
#include <battlecalculator.hpp>
#include <datamanager.hpp>
#include <log.hpp>
#include <statistics.hpp>

int main(int argc, char* argv[]) {
    // Establish basic command-line instructions
    if (argc < 3) {
        std::println("Usage:   {} [path_to_gguf_model] \"[query]\" [file1.txt] [file2.txt] ...", argv[0]);
        std::println("Example: {} ./dist/ibm-granite30m/ibm-granite \"Linda dog\" dist/docs/linda_the_dog.txt\n", argv[0]);
        return EXIT_FAILURE;
    }

    // STEP 0: PARSE COMMAND LINE
    const std::string model_path = argv[1];
    std::string inputQuery{argv[2]};
   
    return EXIT_SUCCESS;
}