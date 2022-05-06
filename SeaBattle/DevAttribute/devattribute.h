#pragma once
#ifndef _DEVATTRIBUTE_
#define _DEVATTRIBUTE_

#include <yvals_core.h>
#pragma execution_character_set( "utf-8" )

#if _STL_COMPILER_PREPROCESSOR

#if _HAS_CXX17 && defined(_FILESYSTEM_USE_)
#include <filesystem>
#endif // _HAS_CXX17 && _FILE_SYSTEM_USE_

#if !defined(_FILESYSTEM_)
#include <vector>
#endif //!_FILESYSTEM_

//
// Include
//

#include <conio.h>
#include <Windows.h>
#include <string>
#include <codecvt>
#include <Psapi.h>
#include <fstream>

//
// Types
//

typedef struct _SYSTEM_FILECACHE_INFORMATION
{
    SIZE_T CurrentSize;
    SIZE_T PeakSize;
    ULONG PageFaultCount;
    SIZE_T MinimumWorkingSet;
    SIZE_T MaximumWorkingSet;
    SIZE_T CurrentSizeIncludingTransitionInPages;
    SIZE_T PeakSizeIncludingTransitionInPages;
    ULONG TransitionRePurposeCount;
    ULONG Flags;
} SYSTEM_FILECACHE_INFORMATION;

typedef struct _MEMORY_COMBINE_INFORMATION_EX
{
    HANDLE Handle;
    ULONG_PTR PagesCombined;
    ULONG Flags;
} MEMORY_COMBINE_INFORMATION_EX, * PMEMORY_COMBINE_INFORMATION_EX;

//
// Enums
//

typedef enum _SYSTEM_INFORMATION_CLASS
{
    SystemFileCacheInformation = 21,
    SystemMemoryListInformation = 80,
    SystemCombinePhysicalMemoryInformation = 130
};

typedef enum _SYSTEM_MEMORY_LIST_COMMAND
{
    nul = -1,
    CaptureAccessedBits,
    CaptureAndResetAccessedBits,
    EmptyWorkingSets,
    FlushModifiedList,
    PurgeStandbyList,
    PurgeLowPriorityStandbyList,
    CommandMax
} SYSTEM_MEMORY_LIST_COMMAND;

typedef enum  consoleColor {
    NUL = -1,BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY, DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE
};

//
// Functions prototypes
//

void pause();

void winPause();

void setConsoleFullscreen();

COORD getConsoleCursorPosition();

void setColor(
    consoleColor foreground, 
    consoleColor background
);

void GotoXY(
    short X, 
    short Y, 
    std::string print = "", 
    consoleColor foreground = WHITE, 
    consoleColor background = BLACK
);

const char* WinFileDialog(
    HWND hwnd, 
    const char* mode, 
    const char* lpstrFilters
);


void sheetGenerator(
    int x,
    int y,
    const int sizeX,
    const int sizeY,
    int lengthX,
    int lengthY,
    int boardStyle=0,
    consoleColor text = WHITE,
    consoleColor background = BLACK
);

void cleaning(
    int x, 
    int y, 
    int width, 
    int height, 
    consoleColor background = BLACK
);

void setConsoleSize(
    int columnsX,
    int linesY
);

int getConsoleSize(
    std::string position
);

void setConsoleNoSelection(
    BOOL status
);

BOOL showConsoleCursor(
    BOOL bShow
);

void setConsoleNoSelection(
    BOOL status
);


void consoleResize(
    BOOL status
);



bool removeLineFromFile(
    std::string filename,
    int index
);

LONG calc_percentof64(
    _In_ LONG64 length,
    _In_ LONG64 total_length
);

COORD setConsoleButton(
    int x,
    int y,
    int width,
    int height,
    int countButtonsX,
    int countButtonsY = 1,
    int returnButton = VK_RBUTTON,
    consoleColor inactiveButton = DARKGRAY,
    consoleColor activeButton = WHITE,
    int YCorrect = 1,
    bool boarder = false,
    int boarder_style = 0,
    consoleColor boarderColor = WHITE,
    consoleColor backBoarderColor = BLACK,
    std::string titles[] = 0,
    int titlesIndent = 2,
    consoleColor titlesColor = WHITE
);

std::string printFilter(
    int length,
    int x=getConsoleCursorPosition().X, 
    int y=getConsoleCursorPosition().Y, 
    std::string mode = "str", 
    std::string min = " ",
    std::string max = "z", 
    int minDig = INT_MIN, 
    int maxDig = INT_MAX
);


//
// Classes
//

class strtools
{
public:
    std::string tolower(std::string str, std::string flag ="");
    std::string toupper(std::string str,std::string flag="");
    std::string strexplus(std::string str1, std::string str2);
    std::wstring stows(const std::string& str) { return converter.from_bytes(str); }
    std::string wstos(const std::wstring& str) { return converter.to_bytes(str); }
    int strfind(std::string str1, std::string str2);
    void setUtfLocale() {
        if (init == false) {
            SetConsoleOutputCP(65001);
            SetConsoleCP(65001);
            init = true;
        }
    }

#if defined(_FILESYSTEM_)
    std::string getPath(std::string mode = "path") {
        if (mode == "path")
            return std::filesystem::absolute(std::filesystem::current_path()).string() + "\\";
        if (mode == "username") {
            DWORD userNameBuff = 256 + 1;
#if defined(_UNICODE)
            wchar_t buff[256 + 1];
            GetUserName(buff, &userNameBuff);
            std::wstring ws(buff);
            std::string username(ws.begin(), ws.end());
#elif defined(_MBCS)
            char buff[256 + 1];
            GetUserName(buff, &userNameBuff);
            std::string username;
#endif
            return username;
        }
    }
std::vector < std::string> fileNameList(bool only_names = 0, std::string path_to_dir = "auto", std::string extension = "") {
        if (path_to_dir == "auto") path_to_dir = getPath("path");
        if (std::filesystem::is_directory(path_to_dir)) {
            std::vector < std::string> file_names;
            int counter = 0,extLen = extension.length();
            for (const auto& entry : std::filesystem::directory_iterator(path_to_dir))
                if (entry.is_regular_file()) {
                    file_names.push_back(std::filesystem::absolute(entry.path()).string());
                    if (only_names == 1) {
                        file_names[counter].erase(0, path_to_dir.length());
                        if (extension != "") file_names[counter].erase(file_names[counter].length() - extLen, extLen);
                        counter++;
                    }
                }
            return file_names;
        }
    }

    void fileRename(std::string old_name, std::string new_name, std::string path_to_dir = "auto") {
        std::filesystem::path p;
        if (path_to_dir == "auto") p = std::filesystem::current_path();
        else  p = path_to_dir;
        std::filesystem::rename(p / old_name, p / new_name);
    }
#endif // defined(_FILESYSTEM_)

private:
    std::wstring RUup = (L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ");
    std::wstring RUdown = (L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя");
    std::wstring UAdown = (L"ґєії"), UAup = (L"ҐЄІЇ");
    std::wstring GRup = (L"ABГΔEZHΘIKΛMNΞOПPΣTΥΦΧΨΩ");
    std::wstring GRdown = (L"αβγδεζηθικλμνξοπρστυφχψω");
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    bool init = false;

};

static strtools utf;

//
// Templates
//

#if ( __cplusplus >= 201103L || _MSC_VER)
#define SWITCH_DECLTYPE decltype
#else
#define SWITCH_DECLTYPE typeof
#endif //( __cplusplus >= 201103L || _MSC_VER)

namespace switch_data {
    template<class T>
    struct SwitchData {
        bool bEnterFall;
        bool bEnterDefault;
        bool bDone;
        T strPtrThrSw;
        SwitchData(T arg) : strPtrThrSw(arg) {}
        inline bool transition(bool fall, const T& cnst, bool ndeflt) {
            if (bDone)
                return false;
            if (fall && bEnterFall)
                return 1;
            if (!fall && bEnterFall) {
                bDone = 1;
                return 0;
            }
            if (ndeflt) {
                bEnterFall = strPtrThrSw == cnst;
                if (bEnterFall) bEnterDefault = false;
            }
            return ndeflt ?
                bEnterFall :
                bEnterDefault;
        }
        void cpp97() {};
    };
} // namespace switch_data

#define SWITCH(arg) if(1){switch_data::SwitchData< SWITCH_DECLTYPE(arg) > \
    switch__d_a_t_a(arg); \
  switch__d_a_t_a.bEnterDefault=true;switch__d_a_t_a.bEnterFall=false; \
  switch__d_a_t_a.bDone=false;if(switch__d_a_t_a.transition(false,

#define CASE(cnst)  cnst,true)){

#define BREAK       switch__d_a_t_a.bDone=true; \
                    ;} if(switch__d_a_t_a.transition(false,

#define FALL        ;} if(switch__d_a_t_a.transition(true,

#define DEFAULT     switch__d_a_t_a.strPtrThrSw,false)){

#define END         ;}};
#endif // _STL_COMPILER_PREPROCESSOR
#endif // _DEVATTRIBUTE_
