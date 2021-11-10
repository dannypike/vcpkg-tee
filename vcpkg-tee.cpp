// vcpkg-tee : Parses vcpkg output and updates the Command Pormpt title to display progress
// 
// Monitors the stdin looking for statements like this:
//   Starting package 2/9: qt5-base:x64-windows
// 
// and inserts a progress report at the start of the Command Prompt title to look something like this:
//  [2/9 qt5-base:x64-windows] Command Prompt - vcpkg upgrade --no-dry-run --keep-going
//
// and echoes the stdin stream to stdout in the same way as 'tee' would

#include <windows.h>
#include <strsafe.h>
#include <algorithm>
#include <boost/regex.hpp>
#include <iostream>
#include <string>

using namespace boost;
using namespace std;

void update_progress(LPWSTR original_title, int instance, int total, const wstring &package)
{
    wchar_t new_title[2048];
    StringCbPrintfW(&new_title[0], sizeof(new_title) / sizeof(new_title[0]), L"[%i/%i %ws] - %ws"
        , instance, total, package.c_str(), original_title);
    SetConsoleTitle(&new_title[0]);
}

int main()
{
    static wchar_t original_title[1024];
    GetConsoleTitle(&original_title[0], sizeof(original_title) / sizeof(original_title[0]));

    string line;
    wstring package;
    smatch results;
    int instance, total;
    regex rx("^Starting package.*([0-9]+) */ *([0-9]+) *:? *(.*)$");

    while (getline(cin, line)) {
        cout << line << endl;

        if (regex_match(line, results, rx)) {
            instance = atoi(results[1].str().c_str());
            total = atoi(results[2].str().c_str());
            package = (wstringstream() << results[3].str().c_str()).str();
            update_progress(&original_title[0], instance, total, package);
            Sleep(1000);
        }
    }
    SetConsoleTitle(&original_title[0]);
}
