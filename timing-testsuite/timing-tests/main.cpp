#include <botan/pubkey.h>
#include <botan/rsa.h>
#include <botan/system_rng.h>
#include <botan/hex.h>
#include <botan/rng.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <botan/numthry.h>


#include "TimingTest.h"

/**
 * Reads directory and outputs a vector of files. 
 * 
 * @param dir_path
 * @return 
 */
std::vector<std::string> read_dir(const std::string& dir_path) {
    DIR *dir;
    struct dirent *ent;
    std::vector<std::string> out;
    if ((dir = opendir(dir_path.c_str())) != NULL) {

        while ((ent = readdir(dir)) != NULL) {
            const std::string filename = ent->d_name;
            if (filename == "." || filename == "..")
                continue;
            const std::string full_path = dir_path + "/" + filename;
            out.push_back(full_path);
        }
        closedir(dir);
    }
    return out;
}

/*
 * Reads vectors from a given file 
 * 
 */
std::vector<std::string> read_vectors(const std::string& filename) {
    std::string line;
    std::ifstream infile(filename);
    std::vector<std::string> out;
    while (std::getline(infile, line)) {
        if (line.at(0) != '#') {
            out.push_back(line);
        }
    }
    return out;
}

int main() {

    std::vector<std::string> files = read_dir("data");
    for (auto const& file : files) {
        std::vector<std::string> inputs = read_vectors(file);

        if (file.find("bleichenbacher") != std::string::npos) {
            //            const std::vector<uint8_t> valid = Botan::hex_decode(inputs.at(0));
            //            std::string result_folder = "results/bleichenbacher";
            //            std::unique_ptr<BleichenbacherTest> test(new BleichenbacherTest(inputs, result_folder, 2048));
            //            test->execute_evaluation();
        } else if (file.find("manger") != std::string::npos) {
            //            const std::vector<uint8_t> valid = Botan::hex_decode(inputs.at(0));
            //            std::string result_folder = "results/manger";
            //            std::unique_ptr<MangerTest> test(new MangerTest(inputs, result_folder, 2048));
            //            test->execute_evaluation();
        } else if (file.find("lucky13") != std::string::npos) {
            const std::vector<uint8_t> valid = Botan::hex_decode(inputs.at(0));
            std::string result_folder = "results/lucky13";
            std::unique_ptr<Lucky13Test> test(new Lucky13Test(inputs, result_folder));
            test->execute_evaluation();

        } else {
            std::cout << "invalid file name";
        }
    }

    return 1;
}

