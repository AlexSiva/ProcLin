#include <unistd.h>
#include <wait.h>

#include <iostream>

int main(int argc, char *argv[]) {
  std::string proc = "PROC_TO_KILL";
  std::string env = "Telegram";
  setenv(env.c_str(), proc.c_str(), 0);
  pid_t pid = fork();
  switch (pid) {
    case 0:
      execv("./../../killer/cmake-build-debug/killer", argv);
      exit(0);
    case -1:
      std::cout << "Error\n";
      return -1;
    default:
      wait(NULL);
      exit(0);
  }
  unsetenv("PROC_TO_KILL");
  return 0;
}  // user