#include <dirent.h>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
// Definining OperatingSystem() function
string LinuxParser::OperatingSystem() {
  // Declaring variable line of type string
  string line;
  // Declaring variable key of type string
  string key;
  // Declaring variable value of type string
  string value;
  // Read from a file using ifstream
  // filestream becomes object
  // kOSPath is the path of the file to be read
  std::ifstream filestream(kOSPath);
  // Parse the kOSPatch until you get to the OS Name and return it
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR *directory = opendir(kProcDirectory.c_str());
  struct dirent *file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  // const std::string kProcDirectory{"/proc/"};
  // const std::string kMeminfoFilename{"/meminfo"};
  float mem_total, mem_available, buffers, value;
  float mem_utilization;
  std::string key;
  std::string line;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);

  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "Buffers") {
          buffers = value;
        }
        if (key == "MemTotal") {
          mem_total = value;
        }
        if (key == "MemAvailable") {
          mem_available = value;
        }
      }
    }
    mem_utilization = (1 - (mem_available - buffers) / mem_total);
  }
  return mem_utilization;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  // const std::string kProcDirectory{"/proc/"};
  // const std::string kUptimeFilename{"/uptime"};

  long up_time;
  std::string key;
  std::string line;

  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> up_time;
    return up_time;
  }
  return up_time;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() {
  long one, two, three, four, five, six, seven, eight, nine, ten;
  long total_jiffies;
  std::string key;
  std::string line;

  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    while (linestream >> key >> one >> two >> three >> four >> five >> six >>
           seven >> eight >> nine >> ten) {
      if (key == "cpu") {
        one = one;
        two = two;
        three = three;
        four = four;
        five = five;
        six = six;
        seven = seven;
        eight = eight;
        nine = nine;
        ten = ten;
      }
    }
  }
  total_jiffies =
      one + two + three + four + five + six + seven + eight + nine + ten;

  return total_jiffies;
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) {
  long active_jiffies;
  std::string key;
  std::string line;
  std::vector<std::string> pid_stat;

  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    while (linestream >> key) {
      pid_stat.push_back(key);
    }
  }
  long user_code = std::stol(pid_stat[13]);
  long kernel_code = std::stol(pid_stat[14]);

  active_jiffies = user_code + kernel_code;
  return active_jiffies;
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<long> LinuxParser::CpuUtilization() {
  std::vector<long> cpu_stats;
  long one, two, three, four, five, six, seven, eight, nine, ten;
  std::string key;
  std::string line;

  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    while (linestream >> key >> one >> two >> three >> four >> five >> six >>
           seven >> eight >> nine >> ten) {
      if (key == "cpu") {
        cpu_stats.insert(cpu_stats.end(), {one, two, three, four, five, six,
                                           seven, eight, nine, ten});
        return cpu_stats;
      }
    }
  }
  return cpu_stats;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  int value;
  std::string key;
  std::string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          return value;
        }
      }
    }
  }
  return value;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  int value;
  std::string key;
  std::string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          return value;
        }
      }
    }
  }
  return value;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  std::string command;
  std::string key;
  std::string line;
  command.clear();

  std::ifstream stream("/proc/" + std::to_string(pid) + "/cmdline");
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key) {
        
        command.append(key);
        command.append(" ");
      }
    }
  }
  return command;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
  string mem_utilization;
  mem_utilization.clear();
  std::string key;
  std::string value;
  std::string line;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);

  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "VmSize:") {
          mem_utilization = std::to_string(std::stoi(value) / 1000);
          return mem_utilization;
        }
      }
    }
  }
  return mem_utilization;
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  std::string value;
  std::string key;
  std::string line;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "Uid:") {
          return value;
        }
      }
    }
  }
  return value;
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
  string line;
  string key;
  string value;
  std::ifstream stream(kPasswordPath);

  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::replace(line.begin(), line.end(), 'x', ' ');

      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (value == LinuxParser::Uid(pid)) {
          return key;
        }
      }
    }
  }
  return key;
}

float LinuxParser::ProcessCpuUtilization(int pid) {
  float process_cpu_utilization;
  long uptime = LinuxParser::UpTime(); // Replace using parser uptime (maybe
                                       // not)
  std::string key;
  std::string line;
  std::vector<std::string> proc_pid_stat_items = {};

  long hertz;

  float utime, stime, cutime, cstime, starttime;

  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key) {
        proc_pid_stat_items.push_back(key);
      }
    }
  }

  utime = std::stof(proc_pid_stat_items[13]);
  stime = std::stof(proc_pid_stat_items[14]);
  cutime = std::stof(proc_pid_stat_items[15]);
  cstime = std::stof(proc_pid_stat_items[16]);
  starttime = std::stof(proc_pid_stat_items[21]);

  hertz = sysconf(_SC_CLK_TCK);

  float total_time = utime + stime + cutime + cstime;

  float seconds = uptime - (starttime / hertz);

  process_cpu_utilization =
      ((total_time / hertz) / seconds); // ncurses will times by 100 to get %

  return process_cpu_utilization;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  long system_uptime = LinuxParser::UpTime();
  long uptime;
  std::string key;
  std::string value;
  std::string line;
  std::vector<std::string> proc_pid_stat_items = {};

  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key) {
        proc_pid_stat_items.push_back(key);
      }
    }
  }

  uptime = system_uptime - (std::stof(proc_pid_stat_items[21]) / sysconf(_SC_CLK_TCK));
  return uptime;
}
