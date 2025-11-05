#include <iostream>
#include <unistd.h>

namespace {
    pid_t attach(int argc, const char** argv) {
        pid_t pid = 0;
        if(argc == 3 && argv[1] == std::string_view("-p")){
            pid = std::atoi(argv[2]);
            if(pid <= 0){
                std::cerr << "Invalid PID\n";
                return -1;
            }
            if(ptrace(PTRACE_ATTACH, pid, /*addr=*/ nullptr, /*data=*/ nullptr) < 0){
                std::perror("Could Not Attach");
                return -1;
            }
        } else {
            const char* program_path = argv[1];
            if((pid=fork()) < 0){
                std::perror("Fork failed");
            }
            if(pid == 0){
                if(ptrace(PTRACE_TRACEME, 0, nullptr, nullptr) < 0) {
                    std::perror("Tracing Failed");
                    return -1;
                }
                if(execlp(program_path, program_path, nullptr) < 0){
                    std::perror("Exec Failed");

                    return -1;
                }
            }

        }
        return pid;
    }
}
int main(int argc, const char** argv) {
    if(argc == 1){
        std::cerr << "No arguments\n";
        return -1;
    }
    pid_t pid = attach(argc, argv);
}