#include "vector_test.hpp"

int main() {
    std::srand(time(0));
    cout << endl <<  BYELLOW << "    *** running tests for a vector ***" << "   |     time" << RESET << endl;
    cout << (constructor_vector() ? (BGREEN + "OK") : (BRED + "KO")) << RESET "    " << std::to_string(g_std_time) << " | " << std::to_string(g_ft_time);
    cout << endl;
    return 0;
}