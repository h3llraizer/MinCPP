#include <windows.h>

namespace mincpp {

    struct ostream {
        void* hConsole;

        ostream() {
            hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        }

        // Overload << for const char*
        ostream& operator<<(const char* msg) {
            unsigned long written;
            WriteConsoleA(hConsole, msg, lstrlenA(msg), &written, nullptr);
            return *this;
        }

        // Overload << for single char
        ostream& operator<<(char c) {
            unsigned long written;
            WriteConsoleA(hConsole, &c, 1, &written, nullptr);
            return *this;
        }

        // Overload << for integers (simple itoa)
        ostream& operator<<(int n) {
            char buffer[32];
            int i = 31;
            buffer[i--] = 0;

            bool neg = n < 0;
            unsigned int val = neg ? -n : n;

            if (val == 0) buffer[i--] = '0';
            while (val > 0) {
                buffer[i--] = '0' + (val % 10);
                val /= 10;
            }
            if (neg) buffer[i--] = '-';

            return (*this << &buffer[i + 1]);
        }
    };

    ostream* cout = nullptr;
}



int main() {

    mincpp::ostream cout;
    cout << "Hello,dojenoej \n";

    decltype(cout) coutPtr = cout;

    return 0;
}

// Minimal entry point, no CRT
extern "C" void _start() {
    int result = main();
    ExitProcess(result);
}

