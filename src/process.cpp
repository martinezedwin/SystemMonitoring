#include <cctype>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>

#include "linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return _pid; }

float Process::CpuUtilization() { return LinuxParser::ProcessCpuUtilization(_pid);}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(_pid);}

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(_pid);}

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(_pid);}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(_pid);}
//-----------------------------------------------------------------------------------

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const &a) const {
  if (_cpuUtilization > a._cpuUtilization)
    return true;
  else
    return false;
}

Process::Process(int pid) {
  _pid = pid;
  _cpuUtilization = LinuxParser::ProcessCpuUtilization(_pid);
}
