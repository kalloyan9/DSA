//factorization + gtest
// to run in terminal:
// g++ factorization_task.cpp -lgtest -lgtest_main -p 

// note: itoa is not STD func!!!

#include <iostream>
#include <string>
#include <gtest/gtest.h>
using namespace std;


void itoa( char *str, int num) // decimal
{
    sprintf( str, "%d", num );
}

string factorization(int n)
{
        string ans = "";
        char helper[10];
        int how, i, j;
        i = 1; // i starts from 2 ...
        while (n != 1){
                ++i; // ... 2
                how = 0;
                while (n % i == 0){
                        ++how;
                        n /= i;
                }
                for (j = 0; j < how; ++j){
                        itoa(helper, i);
                        ans += helper;
                        ans += "x";
                }
        }
        return ans;
}

int howManyZeroesHasTheProduct(int arr[], int size)
{
        int n;
        int result = 0;
        int twoes = 0, fives = 0;
        for (int multiplier = 0; multiplier < size; ++multiplier){
                int how, i;
                i = 1;
                n = arr[multiplier];
                while (n != 1){
                        ++i;
                        if (i > 5)
                                break;
                        how = 0;
                        while (n % i == 0){
                                ++how;
                                n /= i;
                        }
                        if (i == 2)
                                twoes += how;
                        else if (i == 5)
                                fives += how;
                }
        }
        return twoes < fives ? twoes : fives;
}

TEST(factorizationTest, testCorrect)
{
        string ans = "2x2x2x3x3x7x11x";
        ASSERT_EQ(factorization(5544), ans);
}


TEST(howManyZeroesHasTheProductTest, testCorrect)
{
        int n = 6;
        int arr[] = {5, 4, 2, 15, 30, 1};
        ASSERT_EQ(howManyZeroesHasTheProduct(arr, n), 3);
}

int main(int argc, char** argv)
{
        testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}

// void factorization(int n) // print in console
// {
//         int how, i, j;
//         i = 1; // i starts from 2 ...
//         while (n != 1){
//                 ++i; // ... 2
//                 how = 0;
//                 while (n % i == 0){
//                         ++how;
//                         n /= i;
//                 }
//                 for (j = 0; j < how; ++j){
//                         cout << i << "x";
//                 }
//         }
// }