#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "linux_parser.h"

class System {
 public:
  // Declaring Cpu() getter function?
  Processor& Cpu();                   // TODO: See src/system.cpp
  // Delcaring Processes() getter function
  std::vector<Process>& Processes();  // TODO: See src/system.cpp
  // Declaring the MemoryUtilization() function
  float MemoryUtilization();          // TODO: See src/system.cpp
  // Declaring the UpTime() getter function
  long UpTime();                      // TODO: See src/system.cpp
  // Declaring the TotalProcesses() getter function
  int TotalProcesses();               // TODO: See src/system.cpp
  // Declaring the RunningProcesses() getter function
  int RunningProcesses();             // TODO: See src/system.cpp
  // Declaring the Kernel() getter function
  std::string Kernel();               // TODO: See src/system.cpp
  // Declaring the OperatingSystem() getter function
  std::string OperatingSystem();      // TODO: See src/system.cpp

  // TODO: Define any necessary private members
 private:
  // variable cpu_ of type Processor
  Processor cpu_;
  // variable processes_ of type vector of Process
  std::vector<Process> processes_ = {};
  // Created - variable kernel_ of type string
  std::string kernel_ = LinuxParser::Kernel();
  // Created - variable memory_utilization_ of type float
  float memory_utilization_ = LinuxParser::MemoryUtilization();
  // Created - variable operating_system_ of type string
  std::string operating_sytem_ = LinuxParser::OperatingSystem();
  // Created - variable running_processes_ of type int
  int running_processes_ = LinuxParser::RunningProcesses();
  // Created - variable total_processes_ of type int
  int total_processes_ = LinuxParser::TotalProcesses();
  // Created - variable up_time_ of type long
  long up_time_ = LinuxParser::UpTime();

  // void UpdateProcess(int pid);

  // void UpdateProcesses();
};

#endif