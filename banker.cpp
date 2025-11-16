// Banker's Algorithm by Aidan Marias
#include <iostream>
#include <fstream>
#include <vector>





int main(int argc, char const *argv[])
{
    if (argc < 2){
        std::cerr << "Error: No input file\n";
        return 1;
    }
    for (size_t i = 1; i < argc; i++){
        std::cout << "File: " << argv[i] << std::endl;
        std::fstream file(argv[i]);
        if (!file) {std::cerr << "Error: Unable to open file" << std::endl; return 1;}
        int current_value = 0;
        std::cout << "Total Resources: ";
        std::vector<int> total_resources;
        while (file >> current_value){
            total_resources.push_back(current_value);
            std::cout << current_value << ' ';
            if (file.peek() == '\n') { // Checks if next char is newline. If true, pops newline and exits while loop
                file.get(); 
                while (file.peek() == '\n'){file.get();}
                break;
            }
        }
        bool outerbreak = false; // Used to indicate if an outer loop need to be broken from an inner loop
        std::cout << "\nAllocated Resources:\n";
        std::vector<int> allocated_resources;
        while (file >> current_value){
            allocated_resources.push_back(current_value);
            std::cout << current_value << ' ';
            while (file.peek() == '\n') { 
                file.get(); 
                if (file.peek() == '\n'){
                    file.get();
                    outerbreak = true;
                    break;
                } else {
                    std::cout << std::endl;
                }
            }
            if (outerbreak) {outerbreak = false; break;}
        }
        std::cout << "\nMax Resources:\n";
        std::vector<int> max_resources;
        while (file >> current_value){
            max_resources.push_back(current_value);
            std::cout << current_value << ' ';
            while (file.peek() == '\n') { 
                file.get(); 
                if (file.peek() == '\n'){
                    file.get();
                    outerbreak = true;
                    break;
                } else {
                    std::cout << std::endl;
                }
            }
            if (outerbreak) {outerbreak = false; break;}
        }
        std::cout << "\nNeeded Resources:\n";
        std::vector<int> needed_resources;
        for (size_t i = 0; i < allocated_resources.size(); i++){
            needed_resources.push_back(max_resources[i]-allocated_resources[i]);
            if ((i+1)%total_resources.size()){
                std::cout << needed_resources[i] << ' ';
            } else {
                std::cout << needed_resources[i] << '\n';
            }
        }
        

        // Banker's Algorithm starts here

        std::vector<int>avalible_resources = total_resources; // Create copy of total_resources
        std::cout << "Avalible Resources: ";
        for (size_t i = 0; i < (allocated_resources.size()/total_resources.size()); i++){
            for (size_t j = 0; j < total_resources.size(); j++){
                    avalible_resources[j] -= allocated_resources[j+total_resources.size()*i];
            }
        }
        for (size_t i = 0; i < total_resources.size(); i++){
            std::cout << avalible_resources[i] << ' ';
        }
        std::vector<bool> finished_programs(allocated_resources.size()/total_resources.size(), false);
        std::vector<int> safe_sequence;
        while(!outerbreak) {
            outerbreak = true;
            for (size_t i = 0; i < allocated_resources.size()/total_resources.size(); i++){
                if (!finished_programs[i]) {
                    bool runnable = true;
                    for (size_t j = 0; j < total_resources.size(); j++){
                        if (needed_resources[j+total_resources.size()*i] > avalible_resources[j]) runnable = false;
                    }
                    if (runnable) {
                        for (size_t j = 0; j < total_resources.size(); j++){
                            avalible_resources[j] += allocated_resources[j+total_resources.size()*i];
                        }
                        finished_programs[i] = true;
                        safe_sequence.push_back(i);
                        outerbreak = false;
                    }
                }
            }
        }
        std::cout << "\nSequence: ";
        if (safe_sequence.size() == allocated_resources.size()/total_resources.size()) {
            for (size_t i = 0; i < safe_sequence.size(); i++)
            {
                std::cout << 'p' << safe_sequence[i] << ' ';
            }
            std::cout << "\nThis sequence is safe\n";
        } else {
            std::cout << "Not Safe\n";
        }
        
    }
    return 0;
}