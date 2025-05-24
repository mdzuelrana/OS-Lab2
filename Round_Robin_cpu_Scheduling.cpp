#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

struct Process {
    int pid, arrival, burst, remaining, waiting = 0, turnaround = 0;
};

int main() {
    int quantum = 2;
    std::vector<Process> p = {{1, 0, 5, 5}, {2, 1, 4, 4}, {3, 2, 2, 2}};
    std::queue<Process*> q;
    int time = 0;
    int n = p.size();

    std::vector<bool> inQueue(n, false);
    int completed = 0;

    while (completed < n) {
        for (int i = 0; i < n; ++i)
            if (p[i].arrival <= time && !inQueue[i]) {
                q.push(&p[i]);
                inQueue[i] = true;
            }

        if (q.empty()) {
            time++;
            continue;
        }

        Process* curr = q.front();
        q.pop();

        int exec = std::min(quantum, curr->remaining);
        curr->remaining -= exec;
        time += exec;

        for (int i = 0; i < n; ++i)
            if (p[i].arrival <= time && !inQueue[i]) {
                q.push(&p[i]);
                inQueue[i] = true;
            }

        if (curr->remaining > 0)
            q.push(curr);
        else {
            curr->turnaround = time - curr->arrival;
            curr->waiting = curr->turnaround - curr->burst;
            completed++;
        }
    }

    std::cout << "PID\tWT\tTAT\n";
    for (auto& proc : p)
        std::cout << proc.pid << "\t" << proc.waiting << "\t" << proc.turnaround << "\n";

    return 0;
}
