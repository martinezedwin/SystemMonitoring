#include <cstddef>
#include <set>
#include <string>
#include <unistd.h>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU (Done probably?)
// Defining the System::Cpu() function
Processor &System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes (Done probably?)
// Defining the System::Processes() funtion
vector<Process> &System::Processes() {
  // while (true) {
  // 	processes_.clear();
  // 	for (int pid : LinuxParser::Pids()) {
  // 		Process process(pid);
  // 		processes_.push_back(process);
  // 	}
  // 	return processes_;
  // }
  processes_.clear();
  for (int pid : LinuxParser::Pids()) {
    Process process(pid);
    processes_.push_back(process);
  }

  sort(processes_.begin(), processes_.end());
  return processes_;
}

// TODO: Return the system's kernel identifier (string)
// Returning the kernel_ variable I defined as a private member of System class
// in system.h
std::string System::Kernel() { return kernel_; }

// TODO: Return the system's memory utilization
// Returning the memory_utilization_ variable I defined as a private member of
// System class in system.h
float System::MemoryUtilization() { return memory_utilization_; }

// TODO: Return the operating system name
// Returning the operating_sytem_ variable I defined as a private member of
// System class in system.h
std::string System::OperatingSystem() { return operating_sytem_; }

// TODO: Return the number of processes actively running on the system
// Returning the running_processes_ variable I defined as a private member of
// System class in system.h
int System::RunningProcesses() { return running_processes_; }

// TODO: Return the total number of processes on the system
// Returning the total_processes_ variable I defined as a private member of
// System class in system.h
int System::TotalProcesses() { return total_processes_; }

// TODO: Return the number of seconds since the system started running
// Returning the up_time_ variable I defined as a private member of System class
// in system.h
long int System::UpTime() { return up_time_; }

// void System::UpdateProcesses() {
//   processes_.clear();
//   for (int pid : LinuxParser::Pids()) {
//     UpdateProcess(pid);
//   }
//   sort(processes_.begin(), processes_.end());
// }

// void System::UpdateProcess(int pid) {
//   Process process(pid);
//   processes_.emplace_back(process);
// }