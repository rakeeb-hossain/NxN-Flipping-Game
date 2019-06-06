//
//  main.cpp
//  SG-Values
//
//  Created by Hossain, Rakeeb on 2018-09-24.
//  Copyright © 2018 Hossain, Rakeeb. All rights reserved.
//


#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <time.h>
using namespace std;
/*
#define N 10
vector<unsigned int> squareSG;
vector<unsigned int> triSG;

int mex(vector<unsigned int> mexValues)
{
    bool exist = true;
    int counter = 0;
    while (exist == true)
    {
        exist = false;
        for (int i = 0; i < mexValues.size(); i++)
        {
            if (counter == mexValues[i])
            {
                exist = true;
            }
        }
        if (exist == true)
        {
            counter++;
        }
    }
    return counter;
}

int squareGame() {
    vector<unsigned int> squareNums;
    vector<unsigned int> possibleValuesX;
    vector<unsigned int> mexValues;

    for (int x = 1; x <= N; x++)
    {
        int xorSum = 0;

        if (sqrt(x) == floor(sqrt(x))) {possibleValuesX.push_back(x);}
        
        for (int z = 0; z < possibleValuesX.size(); z++)
        {
            if (possibleValuesX[z] == 1)
            {
                mexValues.push_back(0);
            }
            else {
                for (int b = x - possibleValuesX[z] + 1; b < x - possibleValuesX[z-1] + 1; b++)
                {
                    xorSum = xorSum ^ squareSG[b - 1];
                }
                mexValues.push_back(xorSum);
            }
        }
        unsigned int minExcludant = mex(mexValues);
        
        squareSG.push_back(minExcludant);
        mexValues.clear();
    }
    return 1;
}

int triangleGame() {
    vector<unsigned int> triangleNums;
    vector<unsigned int> possibleValuesY;
    vector<unsigned int> mexValues;

    for (int x = 1; x <= N; x++)
    {
        int xorSum = 0;

        if ((sqrt(8*x + 1) - 1)/2 == floor((sqrt(8*x + 1) - 1)/2)) {possibleValuesY.push_back(x);}
        for (int z = 0; z < possibleValuesY.size(); z++)
        {
            
            if (possibleValuesY[z] == 1)
            {
                mexValues.push_back(0);
            }
            else {
                for (int b = x - possibleValuesY[z] + 1; b < x - possibleValuesY[z-1] + 1; b++)
                {
                    xorSum = xorSum ^ triSG[b - 1];
                }
                mexValues.push_back(xorSum);
            }
        }
        unsigned int minExcludant = mex(mexValues);
        
        triSG.push_back(minExcludant);
        mexValues.clear();
    }
    return 1;
}

// prod[i][j] is nim-product of numbers 2^i and 2^j
static int prod[9][9]={
    {1},
    {2, 3},
    {4, 8, 6},
    {8, 12, 11, 13},
    {16, 32, 64, 128, 24},
    {32, 48, 128, 192, 44, 52},
    {64, 128, 96, 176, 75, 141, 103},
    {128, 192, 176, 208, 141, 198, 185, 222},
    {256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 384}
};

int highestBit(int x){
    int count = 0;
    while (x != 1)
    {
        x = x >> 1;
        count++;
    }
    return (count);
}
bool isFermatTwoPower(int x){
    if ((x & (x-1)) == 0){
        x = log2(x);
        if ((x & (x-1)) == 0){
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}
unsigned int nimProduct(int a, int b) {
    if (a > b) {
        int c = a;
        a = b;
        b = c;
    }
    if (a == 0 || b == 0) {return 0;}
    if (a == 1 || b == 1) {return a*b;}
    if (a == b && isFermatTwoPower(a) && isFermatTwoPower(b)) {return (3*a)/2;}
    if (isFermatTwoPower(b)) {return a*b;}
    
    int product = 0;

    product ^= prod[highestBit(b)][highestBit(a)];
    
    product ^= nimProduct(pow(2, highestBit(a)), b - pow(2, highestBit(b)));
    
    product ^= nimProduct(a - pow(2, highestBit(a)), pow(2, highestBit(b)));
    
    product ^= nimProduct(a - pow(2, highestBit(a)), b - pow(2, highestBit(b)));

    return product;
}

int main(int argc, const char * argv[]) {
    clock_t t1,t2;
    t1=clock();

    squareGame();
    triangleGame();
    
    unsigned int squareVal = 0;
    unsigned int triVal = 0;
    for (int a = 0; a < squareSG.size(); a++) {
        squareVal = squareVal ^ squareSG[a];
    }
    for (int b = 0; b < triSG.size(); b++) {
        triVal = triVal ^ triSG[b];
    }
    
    unsigned int startingSG = nimProduct(squareVal, triVal);
    cout << startingSG << endl;
    int winningMoveCount = 0;
    for (int a = 1; a <= floor(sqrt(N)); a++){
        cout << a << endl;
        for (int b = 1; b <= floor((sqrt(8*N + 1)-1)/2); b++) {
            for (int i = 1; i <= N; i++) {
                int xSum = 0;
                if (i - a*a >= 0) {
                    for (int x = i - a*a + 1; x <= i; x++) {
                        xSum ^= squareSG[x-1];
                    }
                    for (int j = 1; j <= N; j++) {
                        int ySum = 0;

                        if (j - b*(b+1)/2 >= 0) {
                            for (int y = j - b*(b+1)/2 + 1; y <= j; y++) {
                                ySum ^= triSG[y-1];
                            }
                            if (nimProduct(xSum, ySum) == startingSG) {winningMoveCount++;}
                        }
                    }
                }
            }
        }
    }
    cout << winningMoveCount << endl;

    t2=clock();
    float diff ((float)t2-(float)t1);
    float seconds = diff / CLOCKS_PER_SEC;
    cout<<seconds<<endl;
    return 0;
}

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 1000000
#define M 512
static short res_triangle[N];
static short res_square[N];
static int inv_triangle[M];
static int inv_square[M];

void fill_triangle()
{
    int x, n;
    res_triangle[0] = 1;
    for (x = 1; x < N; x++) {
        int i, j;
        char known[M];
        int max = 0;
        for (n = 1; n*(n+1)/2 <= x+1; n++) {
            int s = res_triangle[x-1] ^ (x+1 == n*(n+1)/2 ? 0 : res_triangle[x-n*(n+1)/2]);
            if (s >= M) {
                printf("error in fill_triangle\n");
                exit(1);
            }
            for (; max <= s; max++)
                known[max] = 0;
            known[s] = 1;
        }
        for (i = 0; i < max; i++)
            if (!known[i])
                break;
        if (i >= M) {
            printf("error in fill_triangle\n");
            exit(1);
        }
        res_triangle[x] = res_triangle[x-1] ^ i;
    }
    memset(inv_triangle, 0, sizeof(inv_triangle));
    for (x = 0; x < N; x++) {
        for (n = 1; n*(n+1)/2 < x+1; n++)
            inv_triangle[res_triangle[x] ^ res_triangle[x-n*(n+1)/2]]++;
        if (n*(n+1)/2 == x+1)
            inv_triangle[res_triangle[x]]++;
    }
}

void fill_square()
{
    int x, n;
    res_square[0] = 1;
    for (x = 1; x < N; x++) {
        int i, j;
        int max = 0;
        char known[M];
        for (n = 1; n*n <= x+1; n++) {
            int s = res_square[x-1] ^ (x+1 == n*n ? 0 : res_square[x-n*n]);
            if (s >= M) {
                printf("error in fill_square\n");
                exit(1);
            }
            for (; max <= s; max++)
                known[max] = 0;
            known[s] = 1;
        }
        for (i = 0; i < max; i++)
            if (!known[i])
                break;
        if (i >= M) {
            printf("error in fill_square\n");
            exit(1);
        }
        res_square[x] = res_square[x-1] ^ i;
    }
    memset(inv_square, 0, sizeof(inv_square));
    for (x = 0; x < N; x++) {
        for (n = 1; n*n < x+1; n++)
            inv_square[res_square[x] ^ res_square[x-n*n]]++;
        if (n*n == x+1)
            inv_square[res_square[x]]++;
    }
}

static unsigned short product_table[M][M];
unsigned short nim_product(unsigned short x, unsigned short y)
{
    int i, j;
    int max = 0;
    static char known[65536];
    for (i = 0; i < x; i++)
        for (j = 0; j < y; j++) {
            int z = product_table[i][y] ^ product_table[x][j] ^ product_table[i][j];
            if (z >= 65536) {
                printf("error in nim_product\n");
                exit(1);
            }
            for (; max <= z; max++)
                known[max] = 0;
            known[z] = 1;
        }
    for (i = 0; i < max; i++)
        if (!known[i])
            break;
    if (i >= 65536) {
        printf("error in nim_product\n");
        exit(1);
    }
    return i;
}

int main()
{
    int i, j;
    long long result = 0;
    fill_triangle();
    fill_square();
    for (i = 0; i < M; i++) {
        for (j = 0; j < M; j++) {
            if (i & (i-1)) {
                product_table[i][j] = product_table[i & -i][j] ^ product_table[i - (i & -i)][j];
            } else if (j & (j-1)) {
                product_table[i][j] = product_table[i][j & -j] ^ product_table[i][j - (j & -j)];
            } else
                product_table[i][j] = nim_product(i, j);
        }
    }
    int target = product_table[res_triangle[N-1]][res_square[N-1]];
    for (i = 0; i < M; i++) if (inv_triangle[i])
        for (j = 0; j < M; j++) if (inv_square[j])
            if (product_table[i][j] == target)
                result += (long long)inv_triangle[i] * inv_square[j];
    printf("%lld\n", result);
    return 0;
}
