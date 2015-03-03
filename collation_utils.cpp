#include <vector>
#include <algorithm>

#include <windows.h>

#include "collation_utils.h"

using namespace std;

wstring Codepage866ToUnicode(const string& toConvert)
{
    // Convert multi byte text to Unicode

    int nBufferSize = MultiByteToWideChar(866, 0, toConvert.c_str(), toConvert.length(), 0, 0) + 1;
    wchar_t* buffer = new wchar_t[nBufferSize];

    ZeroMemory(buffer, nBufferSize);
    int n = MultiByteToWideChar(866, 0, toConvert.c_str(), toConvert.length(), buffer, nBufferSize);
    buffer[n] = '\0';

    wstring result(buffer);

    delete[] buffer;

    // On Windows \n equals to 0x0A so lets replace all 0x0D line endings to 0x0A
    // For more info on topic you can look at http://en.wikipedia.org/wiki/Escape_sequences_in_C#Notes

    size_t pos = 0;

    while ((pos = result.find(0xD, pos)) != result.npos) {
        result[pos] = '\n';
        pos += 1;
    }

    return result;
}

string UnicodeToCodepage866(const wstring& toConvert)
{
    // Convert Unicode text to multi byte

    int nBufferSize = WideCharToMultiByte(866, 0, toConvert.c_str(), toConvert.length(), NULL, 0, NULL, NULL) + 1;
    char* buffer = new char[nBufferSize];

    ZeroMemory(buffer, nBufferSize);
    int n = WideCharToMultiByte(866, 0, toConvert.c_str(), toConvert.length(), buffer, nBufferSize, NULL, NULL);
    buffer[n] = '\0';

    string result(buffer);

    delete[] buffer;

    // Replace all \n endings with \r

    size_t pos = 0;

    while ((pos = result.find('\n', pos)) != result.npos) {
        result[pos] = 0xD;
        pos += 1;
    }

    return result;
}
