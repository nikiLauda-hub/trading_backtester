#include <pybind11/pybind11.h>

int add(int i, int j) {
    return i + j;
}

// Это макрос, который создает "вход" для Python
PYBIND11_MODULE(backtest_core, m) {
    m.doc() = "C++ trading engine core"; // Описание модуля
    m.def("add", &add, "A function that adds two numbers");
}