#include <iostream>
#include <vector>
#include <algorithm>

struct Process {
    int pid, arrival, burst, start, finish, waiting, turnaround;
};

int main() {
    std::vector<Process> p = {{1, 0, 6}, {2, 1, 4}, {3, 2, 2}, {4, 3, 1}};
    std::vector<Process> done;
    int time = 0;

    while (!p.empty()) {
        std::vector<Process> ready;
        for (auto& proc : p)
            if (proc.arrival <= time)
                ready.push_back(proc);

        if (ready.empty()) {
            time++;
            continue;
        }

        auto shortest = std::min_element(ready.begin(), ready.end(), [](Process a, Process b) {
            return a.burst < b.burst;
        });

        Process next = *shortest;
        next.start = time;
        next.finish = next.start + next.burst;
        next.turnaround = next.finish - next.arrival;
        next.waiting = next.start - next.arrival;

        done.push_back(next);
        time = next.finish;

        
        p.erase(std::remove_if(p.begin(), p.end(), [&](Process x) {
            return x.pid == next.pid;
        }), p.end());
    }

    std::cout << "PID\tWT\tTAT\n";
    for (auto& proc : done)
        std::cout << proc.pid << "\t" << proc.waiting << "\t" << proc.turnaround << "\n";

    return 0;
}
