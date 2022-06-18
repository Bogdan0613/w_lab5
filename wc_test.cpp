#include "word_counter.h"
#include <iostream>
#include <sstream>
using namespace std;

#define TEST_STAGE 5

#if TEST_STAGE > 0

void check_empty(word_counter const& wc)
{
    if (not wc.is_empty())
        cerr << "is_empty() false on empty counter\n";
    if (wc.size() != 0)
        cerr << "Non-zero size() on empty counter\n";
    if (wc.get_first() != nullptr)
        cerr << "get_first() returned not nullptr on empty counter\n";
}

void check_on_stream(word_counter const& wc, string const& expected)
{
    stringstream ss;

    ss << wc;
    if (ss.str() != expected)
    {
        cerr << "Invalid output to stream\n";
        cerr << "***Expected: " << expected << "\n";
        cerr << "***Received: " << ss.str() << "\n";
    }
}

#endif // TEST_STAGE

int main()
{
#if TEST_STAGE > 0

    word_counter wc;
    check_empty(wc);
    check_on_stream(wc, "[]");

#endif // TEST_STAGE

#if TEST_STAGE > 1

    wc["Florida"]++;
    check_on_stream(wc, "[(Florida : 1) ]");

    wc["Florida"] += 2;
    check_on_stream(wc, "[(Florida : 3) ]");

    wc["Alabama"]++;
    check_on_stream(wc, "[(Alabama : 1) (Florida : 3) ]");

    wc["Tennessee"] = 7;
    check_on_stream(wc, "[(Alabama : 1) (Florida : 3) (Tennessee : 7) ]");

    wc["Georgia"] = wc["Tennessee"] - wc["Florida"];
    check_on_stream(wc, "[(Alabama : 1) (Florida : 3) (Georgia : 4) (Tennessee : 7) ]");

#endif // TEST_STAGE

#if TEST_STAGE > 2

    {
    word_counter second(wc);
    check_on_stream(second, "[(Alabama : 1) (Florida : 3) (Georgia : 4) (Tennessee : 7) ]");

    word_counter third;
    third["Alaska"] = 1;
    third["Arizona"] = 2;
    third["Arkansas"] = 3;
    check_on_stream(third, "[(Alaska : 1) (Arizona : 2) (Arkansas : 3) ]");
    third = wc;
    check_on_stream(third, "[(Alabama : 1) (Florida : 3) (Georgia : 4) (Tennessee : 7) ]");
}

#endif // TEST_STAGE

#if TEST_STAGE > 3
    {
    word_counter second;
    second["Main"] = 6;
    second["California"] += 2;
    second["Hawaii"] = 5;
    second["Tennessee"] = 1;
    second["Pennsylvania"] = 7;
    check_on_stream(second, "[(California : 2) (Hawaii : 5) (Main : 6) (Pennsylvania : 7) (Tennessee : 1) ]");

    word_counter third = second;
    check_on_stream(third, "[(California : 2) (Hawaii : 5) (Main : 6) (Pennsylvania : 7) (Tennessee : 1) ]");

    third += wc;
    check_on_stream(third, "[(Alabama : 1) (California : 2) (Florida : 3) (Georgia : 4) (Hawaii : 5) (Main : 6) (Pennsylvania : 7) (Tennessee : 8) ]");

    word_counter fourth;
    fourth = second + wc;
    check_on_stream(fourth, "[(Alabama : 1) (California : 2) (Florida : 3) (Georgia : 4) (Hawaii : 5) (Main : 6) (Pennsylvania : 7) (Tennessee : 8) ]");
}

#endif // TEST_STAGE

#if TEST_STAGE > 4

    wc += wc;
    check_on_stream(wc, "[(Alabama : 2) (Florida : 6) (Georgia : 8) (Tennessee : 14) ]");

#endif // TEST_STAGE


    cout << "End of tests.\n";
    return 0;
}

