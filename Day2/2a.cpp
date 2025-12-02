#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    ifstream f("input.txt");
    std::string in;
    f >> in;
    size_t begin = 0;
    std::string range;
    long ans = 0;
    while (in.find(',') != std::string::npos)
    {
        begin = in.find(',');
        range = in.substr(0, begin);
        in.erase(0, begin + 1);
        string start = range.substr(0, range.find('-'));
        string end = range.substr(range.find('-') + 1, range.size() - start.size() - 1);
        std::string sh = start.substr(0, (start.size()) / 2);
        if (sh.empty())
            sh = "1";
        long sfl = stol(sh + sh);
        long e = stol(end);
        long s = stol(start);
        cout << sfl << " " << e << endl;
        while (sfl <= e)
        {
            if (sfl >= s)
                ans += sfl;
            cout << sfl << endl;
            long t = stol(sh);
            t++;
            sh = to_string(t);
            sfl = stol(sh + sh);
        }
    }
    string start = in.substr(0, in.find('-'));
    string end = in.substr(in.find('-') + 1, in.size() - start.size() - 1);
    long e = stol(end);
    std::string sh = start.substr(0, (start.size()) / 2);
    if (sh.empty())
        sh = "1";
    long sfl = stol(sh + sh);
    long s = stol(start);
    while (sfl <= e)
    {
        if (sfl >= s)
            ans += sfl;
        cout << sfl << endl;
        long t = stol(sh);
        t++;
        sh = to_string(t);
        sfl = stol(sh + sh);
    }
    cout << ans;
    return 0;
}