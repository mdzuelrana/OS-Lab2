#include <windows.h>
#include <iostream>

using namespace std;

int main() {
    STARTUPINFOA si = { sizeof(STARTUPINFOA) };
    PROCESS_INFORMATION pi;

    char processName[] = "C:\\Windows\\System32\\notepad.exe"; 

    if (!CreateProcessA(NULL, processName, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        cerr << "Failed to create process. Error: " << GetLastError() << endl;
        return 1;
    }

    cout << "Process created. PID: " << pi.dwProcessId << endl;

   
    Sleep(300000);

   
    if (!TerminateProcess(pi.hProcess, 0)) {
        cerr << "Failed to terminate process. Error: " << GetLastError() << endl;
    } else {
        cout << "Process terminated after 5 minutes." << endl;
    }

    
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
