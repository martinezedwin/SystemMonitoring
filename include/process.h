#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  // Declaring the Pid() getter function 
  int Pid();                               // TODO: See src/process.cpp
  // Declaring the User() getter fucntion
  std::string User();                      // TODO: See src/process.cpp
  // Declaring the Command() getter function
  std::string Command();                   // TODO: See src/process.cpp
  // Declaring the CpuUtilization() getter function
  float CpuUtilization();                  // TODO: See src/process.cpp
  // Declaring the Ram() getter function
  std::string Ram();                       // TODO: See src/process.cpp
  // Declaring the UpTime() getter function
  long int UpTime();                       // TODO: See src/process.cpp
  // Declaring the operator overloader of <
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  // TODO: Declare any necessary private members
 private:
  int pid_ = {};
  float cpu_utilization_ = {};
  std::string command_ = {};
  std::string ram_ = {};
  std::string user_ = {};
  long int up_time_ = {};
};

#endif