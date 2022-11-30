#include <signal.h>
#include <string.h>

#include <iostream>

void killById(int id) {
  pid_t pid = id;
  kill(pid, SIGTERM);
}

void killByName(char* name) {
  char buffer[512];
  std::string str(name);
  FILE* cmdPipe = popen(("pidof " + str).c_str(), "r");
  fgets(buffer, 512, cmdPipe);
  pclose(cmdPipe);
  pid_t pid = strtoul(buffer, NULL, 10);
  pclose(cmdPipe);
  killById(pid);
}

int main(int argc, char* argv[]) {
  char* env = getenv("PROC_TO_KILL");
  killByName(env);
  for (int i = 0; i < argc; i++) {
    std::string str = argv[i];
    if (strcmp(argv[i], "--name") == 0) {
      killByName(argv[i + 1]);
    } else if (strcmp(argv[i], "--id") == 0) {
      killByID(std::atoi(argv[i + 1]));
    }
  }
}