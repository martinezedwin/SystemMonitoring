#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
// Returning the pid_ variable created in process.h
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
// Returning the cpu_utilization_ variable created in process.h
float Process::CpuUtilization() { return cpu_utilization_; }

// TODO: Return the command that generated this process
// Returning the command_ variable created in process.h
string Process::Command() { return command_; }

// TODO: Return this process's memory utilization
// Returning the ram_ variable created in process.h
string Process::Ram() { return ram_; }

// TODO: Return the user (name) that generated this process
// Returning the user_ variable created in process.h
string Process::User() { return user_; }

// TODO: Return the age of this process (in seconds)
// Returning the up_time_ variable created in process.h
long int Process::UpTime() { return up_time_; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }