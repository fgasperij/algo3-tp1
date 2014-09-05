#include <iostream>
#include <time.h>
#include <cstdlib>

using namespace std;

int main(int argc, const char *argv[])
{
    srand (time(NULL));
    int i;
    for(i=1;i<=1000; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            cout << i <<"\n";
            for (int k = 0; k < i; k++)
            {
                int y = rand() % (1000) + 2;
                int x = rand() % (y-1);
                int h = rand() % (1000);
                cout << x << " " << h << " " << y << "\n";
            }
            cout << "\n";
        }
    }
    cout << "0"; 
    return 0;
}