#include <iostream>
#include <chrono>

// Index-based strlen
size_t strlen_index(const char *str)
{
    size_t len = 0;
    while (str[len] != '\0')
    {
        len++;
    }
    return len;
}

// Pointer-based strlen
size_t strlen_pointer(const char *str)
{
    const char *ptr = str;
    while (*ptr != '\0')
    {
        ptr++;
    }
    return ptr - str;
}

int main()
{
    const char *testString = "Hello, World!";

    // Test index-based strlen
    auto start = std::chrono::high_resolution_clock::now();
    size_t len1 = strlen_index(testString);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed1 = end - start;
    std::cout << "Index-based strlen: " << len1 << " (Time: " << elapsed1.count() << "s)\n";

    // Test pointer-based strlen
    start = std::chrono::high_resolution_clock::now();
    size_t len2 = strlen_pointer(testString);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed2 = end - start;
    std::cout << "Pointer-based strlen: " << len2 << " (Time: " << elapsed2.count() << "s)\n";

    return 0;
}