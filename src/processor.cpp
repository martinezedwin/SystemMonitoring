#include "processor.h"
#include "linux_parser.h"
#include <unistd.h>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  long prevIdle, Idle, prevNonIdle, NonIdle, prevTotal, Total;
  float T, I, CPU_Percentage;

  std::vector<long> prev_cpu_stats = LinuxParser::CpuUtilization();
  ;
  // wait half a second to collect stats again
  usleep(500000);
  std::vector<long> cpu_stats = LinuxParser::CpuUtilization();
  ;

  prevIdle = prev_cpu_stats[3] + prev_cpu_stats[4];
  Idle = cpu_stats[3] + cpu_stats[4];

  prevNonIdle = prev_cpu_stats[0] + prev_cpu_stats[1] + prev_cpu_stats[2] +
                prev_cpu_stats[5] + prev_cpu_stats[6] + prev_cpu_stats[7];
  NonIdle = cpu_stats[0] + cpu_stats[1] + cpu_stats[2] + cpu_stats[5] +
            cpu_stats[6] + cpu_stats[7];

  prevTotal = prevIdle + prevNonIdle;
  Total = Idle + NonIdle;

  T = Total - prevTotal;
  I = Idle - prevIdle;

  CPU_Percentage = (T - I) / T;

  return CPU_Percentage;
}