#pragma once

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

struct ScopeTimer {
  inline static int depth = 0;
  std::string name;
  std::chrono::time_point<std::chrono::system_clock> start, end;

  ScopeTimer(const std::string &name) : name(name) {
    start = std::chrono::system_clock::now();
    std::cout << std::string(depth * 4, ' ')
              << "------------------------------------\n";
    print_message("Started", start);
    depth++;
  }

  ~ScopeTimer() {
    depth--;
    end = std::chrono::system_clock::now();
    print_message("Ended", end);

    std::chrono::duration<double> duration = end - start;
    std::cout << std::string(depth * 4, ' ') << "Duration: " << duration.count()
              << " seconds\n";
    std::cout << std::string(depth * 4, ' ')
              << "------------------------------------\n";
  }

  void print_message(
      const std::string &prefix,
      const std::chrono::time_point<std::chrono::system_clock> &timePoint) {
    std::time_t time = std::chrono::system_clock::to_time_t(timePoint);
    struct tm *time_info = std::localtime(&time);
    char buffer[80];
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", time_info);

    std::cout << std::string(depth * 4, ' ') << prefix << " " << name << ": "
              << buffer << " CET\n";
  }
};
