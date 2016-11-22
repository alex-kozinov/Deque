//#define _CRT_SECURE_NO_WARNINGS
#include "deque.h"
#include <algorithm>
#include <gtest\gtest.h>
#include <deque>
using namespace std;
class CRectTest : public ::testing::Test {};
const int MAXN = 10;

TEST(dequeTests, constructionTest) {
    Deque <int> a;
    a = Deque <int>(a);
    a = a;
    Deque <int> *aa = new Deque <int>(a);
    ASSERT_EQ(0, a.size());
    ASSERT_EQ(0, aa->size());
}
TEST(dequeTests, scobeTest) {
    const int MAXN = 113113;
    Deque <int> a;
    for (int i = 0; i < MAXN; ++i)
        a.push_back(i);
    
    for (int i = 0; i < MAXN; ++i)
        ASSERT_EQ(i, a[i]);

    const Deque <int> ca = a;
    for (int i = 0; i < MAXN; ++i)
        ASSERT_EQ(i, ca[i]);
}
TEST(dequeTests, pushTest) {
    const int MAXN = 113113;
    Deque <int> a;
    a.push_back(0);
    for (int i = 1; i <= MAXN; ++i)
        a.push_back(i);
    for (int i = 1; i <= MAXN; ++i)
        a.push_front(-i);

    ASSERT_EQ(a.size(), 2 * MAXN + 1);
    for (int i = -MAXN; i <= MAXN; ++i)
        ASSERT_EQ(i, a[MAXN + i]);
}
TEST(dequeTests, otherSideTest) {
    const int MAXN = 113113;
    Deque <int> a;
    
    for (int i = 0; i < MAXN; ++i) {
        if (rand() & 2) {
            a.push_back(i);
            ASSERT_EQ(i, a.back());
        } else {
            a.push_front(i);
            ASSERT_EQ(i, a.front());                   
        }
    }
    ASSERT_EQ(a.size(), MAXN);
}
TEST(dequeTests, iteratorTest) {
    const int MAXN = 113113;
    Deque <int> a;
    for (int i = 0; i < MAXN; ++i)
        a.push_back(i);
    int num = 0;
    for (Deque <int> ::iterator it = a.begin(); it != a.end(); ++it) {
        ASSERT_EQ(num, it - a.begin());
        ASSERT_EQ(num, *it);
        ++num;
    }
    for (Deque <int> ::reverse_iterator it = a.rbegin(); it != a.rend(); ++it) {
        --num;
        ASSERT_EQ(MAXN - num - 1, it - a.rbegin());
        ASSERT_EQ(num, a.rend() - it - 1);
        ASSERT_EQ(num, *it);
    }

    //const iterators
    const Deque <int> a1 = a;
    for (Deque <int> ::const_iterator it = a1.begin(); it != a1.end(); ++it) {
        ASSERT_EQ(num, it - a1.begin());
        ASSERT_EQ(num, *it);
        ++num;
    }
    for (Deque <int> ::const_reverse_iterator it = a1.rbegin(); it != a1.rend(); ++it) {
        --num;
        ASSERT_EQ(MAXN - num - 1, it - a1.rbegin());
        ASSERT_EQ(num, a1.rend() - it - 1);
        ASSERT_EQ(num, *it);
    }
    //const iterators through cr**()
    const Deque <int> a2 = a;
    for (Deque <int> ::const_iterator it = a2.cbegin(); it != a2.cend(); ++it) {
        ASSERT_EQ(num, it - a2.cbegin());
        ASSERT_EQ(num, *it);
        ++num;
    }
    for (Deque <int> ::const_reverse_iterator it = a2.crbegin(); it != a2.crend(); ++it) {
        --num;
        ASSERT_EQ(MAXN - num - 1, it - a2.crbegin());
        ASSERT_EQ(num, a2.crend() - it - 1);
        ASSERT_EQ(num, *it);
    }
}

TEST(dequeTests, speedTestMillion) {
    const int MAXN = 1000000;
    Deque <int> q;
    for (int i = 0; i < MAXN; ++i)
        q.push_back(i);
    for (int i = 0; i < MAXN; ++i)
        q.pop_front();
}
TEST(dequeTests, speedTest10Million) {
    const int MAXN = 10000000;
    Deque <int> q;
    for (int i = 0; i < MAXN; ++i)
        q.push_back(i);
    for (int i = 0; i < MAXN; ++i)
        q.pop_front();
}
TEST(dequeTests, speedTest100Million) {
    const int MAXN = 100000000;
    Deque <int> q;
    for (int i = 0; i < MAXN; ++i)
        q.push_back(i);
    for (int i = 0; i < MAXN; ++i)
        q.pop_front();
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}