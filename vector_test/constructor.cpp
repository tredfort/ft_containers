#include "vector_test.hpp"

time_t timer() {
    struct timeval start = {};
    gettimeofday(&start, nullptr);
    time_t msecs_time = (start.tv_sec * 1000) + (start.tv_usec / 1000);
    return msecs_time;
}

bool constructor_vector() {
    cout << "  constructor:    ";
    g_start = timer();
    std::vector<int>* std = new std::vector<int>();
    g_std_time = timer() - g_start;

    g_start = timer();
    ft::vector<int>* ft = new ft::vector<int>();
    g_ft_time = timer() - g_start;
    if (!veccmp(std, ft))
        return false;

    for (int i = 0; i < 10; ++i) {
        delete std;
        delete ft;
        int n = rand() % 100;
        g_start = timer();
        std = new std::vector<int>(n);
        g_std_time += timer() - g_start;

        g_start = timer();
        ft = new ft::vector<int>(n);
        g_ft_time += timer() - g_start;
        if (!veccmp(std, ft))
            return false;
    }

    for (int i = 0; i < 10; ++i) {
        delete std;
        delete ft;
        int n = rand() % 100;
        g_start = timer();
        std = new std::vector<int>(n, n);
        g_std_time += timer() - g_start;

        g_start = timer();
        ft = new ft::vector<int>(n, n);
        g_ft_time += timer() - g_start;
        if (!veccmp(std, ft))
            return false;
    }


    g_start = timer();
    std::vector<int> v1;
    g_std_time += timer() - g_start;

    g_start = timer();
    ft::vector<int> v2;
    g_ft_time += timer() - g_start;
    if (!veccmp(v1, v1))
        return false;

    for (int i = 0; i < 10; ++i) {
        int n = rand() % 100;
        g_start = timer();
        std::vector<int> v3(n);
        g_std_time += timer() - g_start;

        g_start = timer();
        ft::vector<int> v4(n);
        g_ft_time += timer() - g_start;
        if (!veccmp(v3, v4))
            return false;
    }

    for (int i = 0; i < 10; ++i) {
        int n = rand() % 100;
        g_start = timer();
        std::vector<int> v3(n, n);
        g_std_time += timer() - g_start;

        g_start = timer();
        ft::vector<int> v4(n, n);
        g_ft_time += timer() - g_start;
        if (!veccmp(v3, v4))
            return false;
    }

    int n = rand() % 100;
    g_start = timer();
    std::vector<int> v5(n, n);
    std::vector<int> copy_v5(v5);
    g_std_time += timer() - g_start;

    g_start = timer();
    ft::vector<int> v6(n, n);
    ft::vector<int> copy_v6(v6);
    g_ft_time += timer() - g_start;
    if (!veccmp(copy_v5, copy_v6))
        return false;

    n = rand() % 100;
    g_start = timer();
    std::vector<int>* v7 = new std::vector<int>(n, n);
    std::vector<int>* copy_v7 = new std::vector<int>(*v7);
    g_std_time += timer() - g_start;

    g_start = timer();
    ft::vector<int>* v8 = new ft::vector<int>(n, n);
    ft::vector<int>* copy_v8 = new ft::vector<int>(*v8);
    g_ft_time += timer() - g_start;
    if (!veccmp(copy_v7, copy_v8))
        return false;

    cout << "time:  std = " << g_std_time << " ft = " << g_ft_time << endl;

    return true;
}