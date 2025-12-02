#include <iostream>
#include <string>
#include <fstream>
#include<set>
using namespace std;

string repeat(std::string base, int times)
{
    std::string out = "";
    for (int i = 0; i < times; i++)
    {
        out += base;
    }
    return out;
}

std::set<long> st;

long solve(std::string start, std::string end, int div)
{
    long s = stol(start);
    long e = stol(end);
    long out = 0;
    std::string part = start.substr(0, start.size() / div);
    if (part.empty())
        part = "1";
    while (stol(repeat(part, div)) <= e)
    {
        long curr = stol(repeat(part, div));
        if (curr >= s && st.find(curr) == st.end())
        {
            st.insert(curr);
            out += curr;
        }
        long t = stol(part);
        t++;
        part = to_string(t);
    }
    return out;
}

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
        for (int i = 2; i <= end.size(); i++)
        {
            ans += solve(start, end, i);
        }
    }
    string start = in.substr(0, in.find('-'));
    string end = in.substr(in.find('-') + 1, in.size() - start.size() - 1);
    for (int i = 2; i <= end.size(); i++)
    {
        ans += solve(start, end, i);
    }
    cout << ans;
    return 0;
}