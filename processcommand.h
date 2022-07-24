#include <iostream>
#include <windows.h>
#include <string>
#include <ctime>
#include <stdio.h>
#include <limits.h>
#include <direct.h>
#include <errno.h>
#include <fstream>
#include <sstream>
#include<signal.h>
#include<iomanip>

using namespace std;

PROCESS_INFORMATION pi[100];
STARTUPINFO si[100];
string cString[100];
HANDLE hHandless[100];
int status[100];
int n = 0;
HANDLE hForeProcess;

LPCWSTR stringToL(string s)
{
    wstring stemp = wstring(s.begin(), s.end());
    LPCWSTR sw = stemp.c_str();
    return sw;
}
void sighandler(int signum) {
    if (hForeProcess != NULL) {
        TerminateProcess(hForeProcess, 0);
        hForeProcess = NULL;
    }
    cout << "Quit foreground process" << endl;
    cout << setfill('.') << setw(120) << '.' << setfill(' ') << endl;;
}

void openProcessInForeGround(string s)
{
    wstring stemp = wstring(s.begin(), s.end());
    LPCWSTR sw = stemp.c_str();

    PROCESS_INFORMATION pi;                 // lpStartupInfo    // lpProcessInformation
    STARTUPINFO si = { sizeof(STARTUPINFO) }; // cpp string must be modified to use in c
    
    ZeroMemory(&si, sizeof(si)); // fill this block with zeros
    si.cb = sizeof(si);          // CreateProcess(cString, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
    if (!CreateProcess(
        sw,  // path
        NULL,     // commmand line
        NULL,     // Process handle not inheritable
        NULL,     // Thread handle not inheritable
        FALSE,    // Set handle inheritance to FALSE
        CREATE_NEW_CONSOLE,
        NULL, // Use parent's environment block
        NULL, // Use parent's starting directory
        &si,  // Pointer to STARTUPINFO structure
        &pi)  // Pointer to PROCESS_INFORMATION structure
        )
    {
        printf("Opening file not successful!\n");
        return;
    }
    else
    {
        cout << "SUCCEED" << endl;
    }
    hForeProcess = pi.hProcess;
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    //system("start sw");
    //system("pause");
}
void openProcessInBackGround(string s)
{
    wstring stemp = wstring(s.begin(), s.end());
    LPCWSTR sw = stemp.c_str();
    void kill(string s);
    ++n;
    status[n] = 1;
    si[n] = { sizeof(STARTUPINFO) };     // lpStartupInfo // lpProcessInformation
    pi[n];                             // cpp string must be modified to use in c
    ZeroMemory(&si[n], sizeof(si[n])); // fill this block with zeros
    si[n].cb = sizeof(si[n]);
    //string a = 
    cString[n] = s.substr(s.find_last_of("/\\") + 1); // CreateProcess(cString, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
    if (!CreateProcess(sw,  // No module name (use command line)
        NULL,        // Command line
        NULL,        // Process handle not inheritable
        NULL,        // Thread handle not inheritable
        FALSE,       // Set handle inheritance to FALSE
        CREATE_NEW_CONSOLE,
        //NULL,
        NULL,   // Use parent's environment block
        NULL,   // Use parent's starting directory
        &si[n], // Pointer to STARTUPINFO structure
        &pi[n]) // Pointer to PROCESS_INFORMATION structure
        )
    {
        TerminateProcess(pi[n].hProcess, 0);
        CloseHandle(pi[n].hThread);
        CloseHandle(pi[n].hProcess);
        n--;
        printf("Changing of directory or opening file not successful!\n");
        return;
    }  
    else
    {
        cout << "SUCCEED" << endl;
    }
}

void killAll()
{
    for (int i = 1; i <= n; ++i)
    {
        TerminateProcess(pi[i].hProcess, 0);
        CloseHandle(pi[i].hThread);
        CloseHandle(pi[i].hProcess);

    }
    printf("All process killed ...\n");
    n = 0;
}

void stopProcess(int i)
{
    if (i > n)
    {
        cout << "index " << i << " out of range for " << endl;
    }
    if (status[i] == 1)
    {
        status[i] = 0;
        cout << "Stop " << cString[i] << " success\n";
        SuspendThread(pi[i].hThread);
    }
    else
    {
        cout << "Process " << cString[i] << " is still stopping" << endl;
    }
}
void killProcess(int i)
{
    if (i > n)
    {
        cout << "index " << i << " out of range for " << n << endl;
    }
    TerminateProcess(pi[i].hProcess, 0);
    CloseHandle(pi[i].hThread);
    CloseHandle(pi[i].hProcess);
    cout << "killed: " << cString[i] << endl;
    for (int j = i; j < n; ++j)
    {
        status[j] = status[j + 1];
        pi[j] = pi[j + 1];
        si[j] = si[j + 1];
        cString[j] = cString[j + 1];
    }
    n--;
}
void resumeProcess(int i)
{
    if (i > n)
    {
        cout << "index " << i << " out of range for " << n << endl;
    }
    if (status[i] == 0)
    {
        status[i] = 1;
        cout << "Process " << cString[i] << " is running again\n";
        ResumeThread(pi[i].hThread);
    }
    else
    {
        cout << "Process " << cString[i] << " is still running" << endl;
    }
}

void killProcessID(int id)
{
    int a = 1;
    for (int i = 1; i <= n; ++i)
    {
        if (pi[i].dwProcessId == id)
        {
            killProcess(i);
            a = 0;
            break;
        }
    }
    if (a)
    {
        printf("Can't find process with this id = %d\n", id);
    }
}
void stopProcessID(int id)
{
    int a = 1;
    for (int i = 1; i <= n; ++i)
    {
        if (pi[i].dwProcessId == id)
        {
            a = 0;
            stopProcess(i);
            break;
        }
    }
    if (a)
    {
        printf("Can't find process with this id = %d\n", id);
    }
}
void resumeProcessID(int id)
{
    int a = 1;
    for (int i = 1; i <= n; ++i)
    {
        if (pi[i].dwProcessId == id)
        {
            a = 0;
            resumeProcess(i);
            break;
        }
    }
    if (a)
    {
        printf("Can't find process with this id = %d\n", id);
    }
}

int getProcessID(int i)
{
    if (i >= n)
        return -1;
    return pi[i].dwProcessId;
}

void listOfCurrent()
{
    char* buffer;
    if ((buffer = _getcwd(NULL, 0)) == NULL)
        perror("_getcwd error");
    if (_chdir(buffer))
    {
        switch (errno)
        {
        case ENOENT:
            printf("No such file or directory.\n");
            break;
        case EINVAL:
            printf("Invalid buffer.\n");
            break;
        default:
            printf("Unknown error.\n");
            break;
        }
    }
    else
        system("dir");

    free(buffer);
}
void listProcess()
{

    printf("\n");
    cout << "List of process: " << endl;
    cout << setw(10) << "Index" << setw(12) << "IdProcess" << setw(20) << "hProcess" << setw(12) << "status" << setw(25) << "name" << endl;
    for (int i = 1; i <= n; ++i)
    {
        DWORD dwExitCode;
        GetExitCodeProcess(pi[i].hProcess, &dwExitCode);
        if (dwExitCode != 259)
        {
            TerminateProcess(pi[i].hProcess, 0);
            CloseHandle(pi[i].hThread);
            CloseHandle(pi[i].hProcess);
            for (int j = i; j < n; ++j)
            {
                status[j] = status[j + 1];
                pi[j] = pi[j + 1];
                si[j] = si[j + 1];
                cString[j] = cString[j + 1];
            }
            n--;
            i--;
        }
        else
        {
            const char* statusOut = (status[i] == 0) ? "stopping" : "Running";
            cout << setw(10) << i << setw(12) << pi[i].dwProcessId << setw(20) << pi[i].hProcess << setw(12) << statusOut << setw(25) << cString[i] << endl;
        }
    }
    cout << setfill('_') << setw(80)<<  "_" << endl;
    cout << setfill(' ');
}
void cd(string s)
{
    char dir[100];
    LPSTR cString = const_cast<char*>(s.c_str());
    int ch = _chdir(cString);           
    if (ch < 0)
    {
        openProcessInBackGround(s);
    }
}














void read_env(string envname) {
    //LPCWSTR stringToL(string);
    #define MAX_NAME 16383
    #define MAX_VALUE 100000
    HKEY hkey;
    BYTE value[MAX_VALUE];
    DWORD valsize = sizeof(value);
    RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("Environment"), 0, KEY_ALL_ACCESS, &hkey);
    
    if (envname == "") {
        for (int i = 0; ; i++) {
            TCHAR name[MAX_NAME];
            DWORD namesz = MAX_NAME;
            value[0] = '\0';
            DWORD valsize = MAX_VALUE;
            if (RegEnumValue(hkey, i, name, &namesz, NULL, NULL, value, &valsize) == 0) {
                cout << (i < 9 ? "0" : "") << i + 1 << ". " << name
                    << " = " << value << "\n";
            }
            else {
                break;
            }
        }

    }
    else if (RegQueryValueEx(hkey, stringToL(envname), NULL, NULL, value, &valsize) == 0) {
        cout << "The value of " << envname << " is: " << value << "\n";
    }
    else {
        cout << "There no variables has the name " << envname << "\n";
    }

    RegCloseKey(hkey);
}

void add_env(string envname,const char* envvalue) {
    //LPCWSTR stringToL(string);
    cout << "The environment variable " << envname << " is added\n";
    HKEY hkey;
    static BYTE value[100000];
    DWORD valsize = sizeof(value);
    RegOpenKeyEx(HKEY_CURRENT_USER,TEXT("Environment"), 0, KEY_ALL_ACCESS, &hkey);
    if (RegQueryValueEx(hkey, stringToL(envname), NULL, NULL, value, &valsize) == 0) {
        char* name = (char*)value;
        strcat_s(name, 100000, "; ");
        strcat_s(name, 100000, envvalue);
        RegSetValueEx(hkey, stringToL(envname), 0, REG_SZ, (BYTE*)name, strlen(name));
    }
    else {
        RegSetValueEx(hkey, stringToL(envname), 0, REG_SZ, (BYTE*)envvalue, strlen(envvalue));
    }
    RegCloseKey(hkey);
}

void del_env(string envname) {
    //LPCWSTR stringToL(string);
    HKEY hkey;
    RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("Environment"), 0, KEY_ALL_ACCESS, &hkey);
    if (RegDeleteValue(hkey, stringToL(envname)) == 0) {
        cout << "The environment variable " <<(envname) << " is deleted\n";
    }
    else {
        cout << "There no variables has the name " << envname << "\n";
    }
    RegCloseKey(hkey);
}