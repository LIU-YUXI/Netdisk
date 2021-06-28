#include "./readfile.h"
int read(const char* filename,string &content)
{
    ofstream out;
    out.open(filename, ios::out);
    if(!out.is_open())
        return -1;
    out << content;
    out.close();
    return 0;
}