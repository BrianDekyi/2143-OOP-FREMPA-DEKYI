#pragma once

#include <chrono>
#include <codecvt>
#include <iostream>
#include <regex>
#include <string>
#include <thread>
#include <deque>
#if defined(WINDOWS)
#include <fcntl.h>
#include <io.h>
#include <windows.h>
#else

#include <unistd.h>
#endif

namespace Term
{

using std::cout;
using std::ostream;
using std::string;
using std::to_string;
using std::deque;
using std::wcout;
using std::wostream;


const unsigned short DEFAULT = 0;
const unsigned short BLACK = 1;
const unsigned short RED = 2;
const unsigned short YELLOW = 3;
const unsigned short GREEN = 4;
const unsigned short BLUE = 5;
const unsigned short CYAN = 6;
const unsigned short MAGENTA = 7;
const unsigned short WHITE = 8;

inline string fuse(string left, string right, bool pad = false);

inline string fuse(std::initializer_list<string> strings, bool pad = false);

inline string fuse(std::deque<string> strings, bool pad = false);

inline deque<string> split(string text, char delim, bool include = false);

inline deque<string> rsplit(string text, string delim, bool include = false);

inline string replace_all(string text, string from, string to);

inline std::wostream &operator<<(wostream &wout, string text);

class Point
{
public:
    unsigned short row;
    unsigned short col;
    // It creates a point 
    inline Point(const unsigned short &row, const unsigned short &col);
};
typedef Point pnt;
typedef Point p;


class Color
{
public:
    unsigned short fg;
    unsigned short bg;
    // It creates a color object
    inline Color(const unsigned short &fg, const unsigned short &bg = 0);
};
typedef Color col;

class Command
{
public:
    virtual void call() = 0;
};
typedef Command com;


class Clear : public Command
{
public:
    inline static Clear &get();
    inline void call() override;

private:
    inline Clear();
};
static Clear &clear = Clear::get();
static Clear &clr = Clear::get();


class Sleep : public Command
{
public:
    inline static Sleep &get();
    
    inline void call() override;
    
    inline Sleep &operator()(int ms);

private:
    unsigned int ms;
    inline Sleep();
};
static Sleep &sleep = Sleep::get();
static Sleep &slp = Sleep::get();

class IO
{
public:
    // constructors
    inline IO();
    inline IO(ostream &out);
    inline IO(wostream &wout);

    // It outputs operations
    inline IO &operator<<(string text);
    // It prints a character 
    inline IO &operator<<(const char &letter);
    // It prints an integer
    inline IO &operator<<(const int &number);
    // It prints a double
    inline IO &operator<<(const double &number);

    // It moves the cursor to a specific row or column 
    inline IO &operator<<(const Point &point);
    // It changes the color to the foreground and 
    // background 
    inline IO &operator<<(const Color &color);
    // It executes a command object.
    inline IO &operator<<(Command &command);

    // input operations
    inline IO &operator>>(char &ch_var);
    inline IO &operator>>(char *&str_var);

private:
    ostream *out;
    wostream *wout;
    bool wide;
    inline void set_color(Color c);

#if defined(WINDOWS)
    bool windows_setup;
    HANDLE stdin_terminal;
    HANDLE stdout_terminal;
    inline void setupWindows();
#endif
};
} 

std::string Term::fuse(string left, string right, bool pad)
{
    string result = "";
    // It splits the strings & it creates deques
    deque<string> lv = split(left, '\n');
    deque<string> rv = split(right, '\n');
    // It corrects the number of lines in the strings 
    if (lv.size() > rv.size())
    {
        int diff = lv.size() - rv.size();
        for (int i = 0; i < diff; i++)
        {
            rv.push_back("");
        }
    }
    else if (lv.size() < rv.size())
    {

        int diff = rv.size() - lv.size();
        for (int i = 0; i < diff; i++)
        {
            lv.push_back("");
        }
    }
    if (pad)
    {
        // It finds the biggest line out of any of the deques
        int max = 0;
        for (int i = 0; i < lv.size(); i++)
        {
            if (lv[i].size() > max)
                max = lv[i].size();
            if (rv[i].size() > max)
                max = rv[i].size();
        }
        
        for (int i = 0; i < lv.size(); i++)
        {
            if (lv[i].size() < max)
            {
                int diff = max - lv[i].size();
                lv[i] += std::string(diff, ' ');
            }
            if (rv[i].size() < max)
            {
                int diff = max - rv[i].size();
                rv[i] += std::string(diff, ' ');
            }
        }
    }
    // It loops through the deques and produces
    // the new string
    for (int i = 0; i < lv.size(); i++)
    {
        result += lv[i] + rv[i] + '\n';
    }
    return result;
}


std::string Term::fuse(std::initializer_list<string> strings, bool pad)
{
    string result = "";
    deque<string> vstrings;
    vstrings.insert(vstrings.end(), strings.begin(), strings.end());
    // It loops through all strings and fuses them
    for (int i = 0; i < vstrings.size(); i++)
    {
        result = fuse(result, vstrings[i], pad);
    }
    return result;
}

std::string Term::fuse(std::deque<string> strings, bool pad)
{
    string result = "";
    for (int i = 0; i < strings.size(); i++)
    {
        result = fuse(result, strings[i], pad);
    }
    return result;
}


std::deque<std::string> Term::split(string text, char delim, bool include)
{
    
    return rsplit(text, string(1, delim), include);
}

std::deque<std::string> Term::rsplit(string text, string delim, bool include)
{
    std::deque<std::string> elems;
    std::regex rgx(delim);
    
    std::sregex_token_iterator iter(text.begin(), text.end(), rgx, -1);
    std::sregex_token_iterator end;
    while (iter != end)
    {
        elems.push_back(*(iter));
        ++iter;
    }

  
    if (include)
    {
        std::sregex_token_iterator iter(text.begin(), text.end(), rgx, 0);
        std::sregex_token_iterator end;

        int i = 0;
        while (iter != end)
        {
            string temp = elems[i + 1];
            // It assigns the string to the delimiter
            elems[i + 1] = *iter;
            // It adds back the original content
            elems[i + 1] += temp;
            // the iterator moves forward
            ++iter;
            // It increments elems index
            i++;
        }
    }

    return elems;
}

std::string Term::replace_all(string text, string from, string to)
{
    size_t start_pos = 0;
    while ((start_pos = text.find(from, start_pos)) != string::npos)
    {
        text.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return text;
}

std::wostream &Term::operator<<(wostream &wout, string text)
{
   
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wide_text = converter.from_bytes(text);
    wout << wide_text;
    return wout;
}

Term::Sleep::Sleep() {}

Term::Sleep &Term::Sleep::get()
{
    static Sleep instance;
    return instance;
}

Term::Sleep &Term::Sleep::operator()(int ms)
{
    this->ms = ms;
    return get();
}

void Term::Sleep::call()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

Term::Clear::Clear() {}

Term::Clear &Term::Clear::get()
{
    static Clear instance;
    return instance;
}

void Term::Clear::call()
{
#if defined(WINDOWS)
    
    static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = {0, 0}; 
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    if (!FillConsoleOutputCharacter(hConsole, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten))
    {
        return;
    }
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }
    if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten))
    {
        return;
    }
    SetConsoleCursorPosition(hConsole, coordScreen);
#else
    std::cout << "\033[2J";
#endif
}
Term::Point::Point(const unsigned short &row, const unsigned short &col)
{
    this->row = row;
    this->col = col;
}

Term::Color::Color(const unsigned short &fg, const unsigned short &bg)
{
    this->fg = fg;
    this->bg = bg;
}


Term::IO::IO()
{
#if defined(WINDOWS)
    windows_setup = false;
    wide = true;
    wout = &wcout;
#else
    wide = false;
    out = &cout;
#endif
}


Term::IO &Term::IO::operator>>(char &ch_var)
{
#if defined(WINDOWS)
    if (!windows_setup)
        setupWindows();
    DWORD mode;

    GetConsoleMode(stdin_terminal, &mode);

    SetConsoleMode(stdin_terminal, 0);

    ch_var = std::cin.get();
    SetConsoleMode(stdin_terminal, mode);
#else
   
    system("stty -brkint -ignpar -istrip -icrnl -ixon -opost -isig -icanon -echo");

    std::cin >> ch_var;

    system("stty cooked echo");
#endif
    return *this;
}


Term::IO &Term::IO::operator<<(string text)
{
#if defined(WINDOWS)
  
    if (!windows_setup)
        setupWindows();
#endif
    text = replace_all(text, "\n", "&00\n");

    text = replace_all(text, "&&", '&' + string(1, char(0)));
    deque<string>
        strings = rsplit(text, "&[0-8][0-8]", true);

    // It prints each line of the deque
    for (int i = 0; i < strings.size(); i++)
    {

        strings[i] = replace_all(strings[i], "&" + string(1, char(0)), string(1, '&'));

        if (strings[i].size() > 3 && i > 0)
        {
            set_color(Color(strings[i][1] - '0', strings[i][2] - '0'));
        }

        if (wide)
        {
  
            if (strings[i].size() > 3 && i > 0)
                *wout << strings[i].substr(3);
            else
                *wout << strings[i];
        }
        else
        {
            if (strings[i].size() > 3 && i > 0)
                *out << strings[i].substr(3);
            else
                *out << strings[i];
        }

        set_color(Color(0, 0));
    }

    return *this;
}

Term::IO &Term::IO::operator<<(const char &letter)
{
#if defined(WINDOWS)
  
    if (!windows_setup)
        setupWindows();
#endif

    if (wide)
    {
        *wout << letter;
    }
    else
    {
        *out << letter;
    }
    return *this;
}

Term::IO &Term::IO::operator<<(const int &number)
{
#if defined(WINDOWS)
    if (!windows_setup)
        setupWindows();
#endif

    if (wide)
    {
        *wout << number;
    }
    else
    {
        *out << number;
    }
    return *this;
}

Term::IO &Term::IO::operator<<(const double &number)
{
#if defined(WINDOWS)

    if (!windows_setup)
        setupWindows();
#endif

    if (wide)
    {
        *wout << number;
    }
    else
    {
        *out << number;
    }
    return *this;
}


Term::IO &Term::IO::operator<<(const Point &point)
{
#if defined(WINDOWS)
    if (!windows_setup)
    {
        setupWindows();
    }
  
    COORD cor = {(short)point.col, (short)point.row};
    SetConsoleCursorPosition(stdout_terminal, cor);
#else
  
    int r = point.row + 1;
    int c = point.col + 1;

    std::string pos = "\033[" + std::to_string(r) + ';' + std::to_string(c) + 'f';
    std::cout << pos;
#endif
    return *this;
}

Term::IO &Term::IO::operator<<(const Color &color)
{
    set_color(color);
    return *this;
}

Term::IO &Term::IO::operator<<(Command &command)
{
    command.call();
    return *this;
}

void Term::IO::set_color(Color c)
{
#if defined(WINDOWS)
    static const unsigned short _fg[] = {7, 0, 4, 6, 2, 1, 3, 5, 7};
    static const unsigned short _bg[] = {0, 0, 64, 96, 32, 16, 48, 80, 112};
#else
    static const unsigned short _fg[] = {39, 30, 31, 33, 32, 34, 36, 35, 37};
    static const unsigned short _bg[] = {49, 40, 41, 43, 42, 44, 46, 45, 47};
#endif

#if defined(WINDOWS)
    if (!windows_setup)
        setupWindows();
    SetConsoleTextAttribute(stdout_terminal, _fg[c.fg] + _bg[c.bg]);
#else
    if (wide)
    {
        *wout << "\033[" + to_string(_fg[c.fg]) + to_string(_bg[c.bg]) + 'm';
    }
    else
    {
        *out << "\033[" + to_string(_fg[c.fg]) + ';' + to_string(_bg[c.bg]) + 'm';
    }
#endif
}

#if defined(WINDOWS)
void Term::IO::setupWindows()
{

    if (!windows_setup)
    {
        // It sets the console mode for unicode
        _setmode(_fileno(stdout), _O_U16TEXT);
        stdin_terminal = GetStdHandle(STD_INPUT_HANDLE);
        stdout_terminal = GetStdHandle(STD_OUTPUT_HANDLE);
        windows_setup = true;
    }
}
#endif
