#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
// Define the ElapsedTime() function from format.h
string Format::ElapsedTime(long seconds[[maybe_unused]]) { 
  int seconds_in_hour = 60 * 60;
  int seconds_in_minute = 60;

  int hours = seconds/seconds_in_hour;
  seconds -= hours * seconds_in_hour;

  int minutes = seconds/seconds_in_minute;
  seconds -= minutes * seconds_in_minute;

  std::string hours_in_string = std::to_string(hours);
  std::string minutes_in_string = std::to_string(minutes);
  std::string seconds_in_string = std::to_string(seconds);

  if(hours_in_string.length() < 2) {
    hours_in_string = "0" + hours_in_string;
  }
  if(minutes_in_string.length() < 2) {
    minutes_in_string = "0" + minutes_in_string;
  }
  if(seconds_in_string.length() < 2) {
    seconds_in_string = "0" + seconds_in_string;
  }

  std::string formatted_time = hours_in_string + ":" + minutes_in_string + ":" + seconds_in_string;

  return formatted_time; 
}