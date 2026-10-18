#include <windows.h>
#include <stdio.h>
#include <stdlib.h>


void RunCommandHidden(const char* command) {
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE; 

    ZeroMemory(&pi, sizeof(pi));

    
    char cmdLine[512];
    snprintf(cmdLine, sizeof(cmdLine), "cmd.exe /c %s", command);

    if (CreateProcessA(NULL, cmdLine, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    FILE *fp = NULL;
    int iNo1 = 0, iNo2 = 0, iAns = 0;

    
    RunCommandHidden("powershell -NoProfile -Command \"$null = [Reflection.Assembly]::LoadWithPartialName('Microsoft.VisualBasic'); [Microsoft.VisualBasic.Interaction]::InputBox('Enter first number:', 'Subtraction App') | Out-File -Encoding ascii input1.txt\"");
    
    fp = fopen("input1.txt", "r");
    if (fp != NULL) { 
        fscanf(fp, "%d", &iNo1); 
        fclose(fp); 
    }

    // दुसरी संख्या घेणे
    RunCommandHidden("powershell -NoProfile -Command \"$null = [Reflection.Assembly]::LoadWithPartialName('Microsoft.VisualBasic'); [Microsoft.VisualBasic.Interaction]::InputBox('Enter second number:', 'Subtraction App') | Out-File -Encoding ascii input2.txt\"");
    
    fp = fopen("input2.txt", "r");
    if (fp != NULL) { 
        fscanf(fp, "%d", &iNo2); 
        fclose(fp); 
    }

    // वजाबाकी
    iAns = iNo1 - iNo2;

    // निकाल दाखवणे
    char resultMsg[100];
    sprintf(resultMsg, "Vajabaki (Subtraction) = %d", iAns);
    MessageBox(NULL, resultMsg, "Result Window", MB_OK | MB_ICONINFORMATION);

    // तात्पुरत्या फाईल्स काढून टाकणे
    remove("input1.txt");
    remove("input2.txt");

    return 0;
}