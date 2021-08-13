#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <assert.h>
#include <exception>
#include <sstream>  //string stream


//why does file_path need to be a pointer? 
std::vector<int> check_for_file_integrity (const char *file_path,std::vector<int> data_range) {
    try { 
        auto data_read = std::fstream(file_path);
        if(!data_read.is_open()){
            throw(std::exception());
        }

        std::stringstream string_stream;

        for (std::string line; !data_read.eof();line.clear()){
            std::getline(data_read, line);
            if(line.empty()){
                assert(false);
                throw(std::runtime_error("Empty line encountered"));
                
            }

            // assert(!line.empty());
            // std::cout << line << "\n";
            string_stream << line;
            int line_value{0};
            string_stream >> line_value;
            if(string_stream.fail()){
                throw(std::runtime_error("String stream failed to convert"));
            }
            string_stream.clear();
            string_stream.str("");
            data_range.push_back(line_value);
        }

        data_read.close();

        


    } catch(std::exception& exception) {
        std::cerr << "Exception: " << exception.what() << "\n";
        //return error does not work here, can not convert int to vector int
    }
    return(data_range);
}

void check_for_answer (std::vector<int> data_range, int check_variable, bool problem_success) {
    for (const auto& left_variable : data_range){
        //auto left_variable = data_range.front();
        
        
        for(auto range_index{data_range.cbegin()}; range_index != data_range.cend();++range_index){
            //auto test = range_index;
            
            const auto& right_variable = *range_index; 

             for(auto range_index{data_range.cbegin()}; range_index != data_range.cend();++range_index){
            const auto& third_variable = *range_index;
            //     if(nullptr == &right_variable){
            //     throw(std::runtime_error("No value"));
            // }

            if(check_variable == left_variable + right_variable + third_variable){
                std::cout << left_variable << " + " << right_variable << " + " <<
                third_variable << " = " << check_variable << "\n";
                auto mult_value{(left_variable*right_variable*third_variable)};
                std::cout << "The three variables multiplied = " << mult_value << "\n";

                
                problem_success = true;
                    break;
                

            } //else{
               // left_variable = data_range.front() + 1;}
             }
          if (problem_success == true) {
              break;
          } 
        }
}}


int main () {
    constexpr auto file_path = "C:\\src\\code\\advent2020\\day1\\range.txt";
    std::vector<int> data_range;


    //need to catch data_range output? 
    //also, order of arguments important? 
    data_range= {check_for_file_integrity(file_path, data_range)};

    constexpr auto check_variable = 2020;
    bool problem_success{false};

    //void because we don't need anything returned, once printed to console can be destroyed.
    check_for_answer(data_range, check_variable, problem_success);


return(EXIT_SUCCESS);

}
