#include <iostream>
#include <vector>
#include <algorithm>

struct Process {
    int pid, arrival, burst, start, finish, waiting, turnaround;
};

bool compareArrival(Process a, Process b) {
    return a.arrival < b.arrival;
}

int main() {
    std::vector<Process> p = {{1, 0, 4}, {2, 1, 3}, {3, 2, 1}};
    std::sort(p.begin(), p.end(), compareArrival);

    int time = 0;
    for (auto& proc : p) {
        proc.start = std::max(time, proc.arrival);
        proc.finish = proc.start + proc.burst;
        proc.turnaround = proc.finish - proc.arrival;
        proc.waiting = proc.start - proc.arrival;
        time = proc.finish;
    }

    std::cout << "PID\tWT\tTAT\n";
    for (auto& proc : p)
        std::cout << proc.pid << "\t" << proc.waiting << "\t" << proc.turnaround << "\n";

    return 0;
}
