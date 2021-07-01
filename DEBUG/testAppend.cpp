#include <iostream>
#include <fstream>
using namespace std;

void func()
{
    ofstream outfile("test.txt", ios::out | ios::app);
    outfile << "Helloworld";
    outfile.close();
}

void testString()
{
    char buffer[10] = {97, 98, 99, 0, 0, 100};
    string str(buffer);
    cout << str << endl;
    cout << str.length() << endl;
}

int main()
{
    testString();
    return 0;
}