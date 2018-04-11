#include "../include/foodUtils.h"

bool fileToString(const std::string& filename, std::string& result){
   std::ifstream file(filename.c_str());
   if(file){
       std::stringstream ss;
       std::string line;
       while(!file.eof()){
           getline(file, line);
           if(line!=""){
               ss << line << std::endl;
           }
       }
       file.close();
       result = ss.str();
       return true;
   }
   return false;
}
