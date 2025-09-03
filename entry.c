#include <windows.h>
#include "beacon.h"

DECLSPEC_IMPORT HANDLE WINAPI kernel32$OpenProcess(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProcessId);
DECLSPEC_IMPORT BOOL WINAPI kernel32$TerminateProcess(HANDLE hProcess, UINT uExitCode);
DECLSPEC_IMPORT DWORD WINAPI kernel32$GetLastError(void);
DECLSPEC_IMPORT BOOL WINAPI kernel32$CloseHandle(HANDLE hObject);

VOID go(char *args, int len) {

  DWORD pid = 0;
  datap parser;
  BeaconDataParse(&parser, args, len);
  pid = BeaconDataInt(&parser);

  HANDLE hProcess = kernel32$OpenProcess(PROCESS_TERMINATE, FALSE, pid);
  if (hProcess == NULL) {
      BeaconPrintf(CALLBACK_ERROR, "Failed to open process with PID %d. Error code: %lu\n", pid, kernel32$GetLastError());
      return;
  }
  BOOL result = kernel32$TerminateProcess(hProcess, 0);
  if (!result) {
      BeaconPrintf(CALLBACK_ERROR, "Failed to terminate process with PID %d. Error code: %lu\n", pid, kernel32$GetLastError());
      kernel32$CloseHandle(hProcess);
      return;
  }
  BeaconPrintf(CALLBACK_OUTPUT, "Terminated process %d\n", pid);
  kernel32$CloseHandle(hProcess);
}
