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

namespace mincpp{

template<typename T>
class unique_ptr {
public:

    // Constructors
    unique_ptr() noexcept
        : ptr_(0) {}

    explicit unique_ptr(T* ptr) noexcept
        : ptr_(ptr) {}

    
    // delete copy semenatics
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;


    // move constructor
    unique_ptr(unique_ptr&& other) noexcept
        : ptr_(other.ptr_) {
        other.ptr_ = 0;
    }

    // move assignment
    unique_ptr& operator=(unique_ptr&& other) noexcept {
        if (this != &other) {
            reset();
            ptr_ = other.ptr_;
            other.ptr_ = 0;
        }
        return *this;
    }

    // destructor
    ~unique_ptr() {
        delete ptr_;
    }
  
    // observers
    T* get() const noexcept {
        return ptr_;
    }

    T& operator*() const noexcept {
        return *ptr_;
    }

    T* operator->() const noexcept {
        return ptr_;
    }

    explicit operator bool() const noexcept {
        return ptr_ != 0;
    }


    // modifiers
    T* release() noexcept {
        T* tmp = ptr_;
        ptr_ = 0;
        return tmp;
    }

    void reset(T* new_ptr = 0) noexcept {
        if (ptr_ != new_ptr) {
            delete ptr_;
            ptr_ = new_ptr;
        }
    }

private:
    T* ptr_;
};

}
//
//template <typename T> T myMax(T x, T y){
//    return (x > y) ? x : y;
//}

class Widget {
    private:
        int x_{};
    public:
        Widget() = default;
        Widget(int x) : x_(x) {}

        ~Widget() = default;
        
        auto getX()
        {
           return x_;  
        }

};

int main() {

    mincpp::ostream cout;
    cout << "Hello,dojenoej \n";

    auto w = Widget(1); 

    mincpp::unique_ptr<Widget> uw(new Widget(42));

    cout << "Unique-Widget X Value: "  <<  uw->getX() << "\n";

    return 0;
}

// Minimal entry point, no CRT
extern "C" void _start() {
    int result = main();
    ExitProcess(result);
}

