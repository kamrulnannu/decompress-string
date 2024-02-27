#if 0
#include <iostream>
#include <vector>
#include <string>
#include <locale>         // std::locale, std::isdigit, std::isalpha
#include <cstdlib>
#endif
#include <bits/stdc++.h>

using namespace std;

std::locale loc;

static string GetRepeatedString(string & base, int count)
{
	string s;
	for (int i=0; (i < count); ++i)
	{
		s += base;
	}
	// cout << "cnt=" << count << " b=" << base << endl;
	return s;
}

static int GetCount(const string &s, size_t startPos, size_t & OpenBktPos)
{
	OpenBktPos = s.find('[', startPos);

	if (string::npos == OpenBktPos)
	{
		cout << "ERROR: Open bracket missing, exiting ..." << endl;
		exit(1);
	}
	string num = s.substr(startPos, OpenBktPos - startPos);

	return (atoi(num.c_str()));
}

static string GetDecompressedString(size_t &start, const string &str)
{
    //static int len = str.length();
	string s;
	int Count = 0;
	size_t openBktPos = 0;
#if 0
    len--;
    cout<<"Start: "<<start<<", str="<<str<<", len ="<<len<<endl;
    if (len < 0)
    {
        cout<<"Exiting ...\n";
        exit(100);
    }
#endif
	while (start < str.length())
	{
		char c = str.at(start);
		if (isalpha(c, loc))
		{
			s += c;
			start++;
		}
		else if (isdigit(c, loc))
		{
			// For a case: ...4[..]..
			Count = GetCount(str, start, openBktPos);

			// Advance to next char after open bracket
			start = openBktPos +1;
			// cout <<" s= " << start << " OB=" << openBktPos <<endl;
			string tmp = GetDecompressedString(start, str);
			s += GetRepeatedString(tmp, Count);
		}
		else if (c == '[')
		{
			// for a case: ..a[...]..
			//Count = 1;
			start++;
			s += GetDecompressedString(start, str);
		}
		else if (c == ']')
		{
			start++;
			return s;
		}
	}
	return s;
}

// Assumption: Incomming string is valid
string GetDecompressedString_v1(const string & str)
{
    stack<std::any> s;  // std::any from C++17
    string tmp;
    size_t pos;
    int i  = 0;
    while (i < str.length())
    {
        if (isdigit(str[i]))
        {
            if (tmp.length())
            {
                /*
                 * Example: ...2[abc3[de]], tmp = abc and str[i] = '3'
                 */
                s.push(std::make_any<string>(tmp));
                tmp = "";
            }
            pos = str.find_first_of('[', i);
            s.push(std::make_any<int>(atoi(str.substr(i, pos-i).c_str())));
            i = pos+1;
        }
        else if (str[i] == ']')
        {
            if (s.empty())
            {
                cout<<"Error: Stack is empty\n";
                return "";
            }
            auto top = s.top();
            while(top.type() == typeid(std::string))
            {
                tmp = std::any_cast<std::string>(top) + tmp;
                s.pop();
                top = s.top();
            }
            int repeat = 0;
            try
            {
                repeat = std::any_cast<int>(top);
                s.pop();
            }
            catch(std::bad_any_cast const & e)
            {
                cout<<"Error: "<<e.what()<<" to int\n";
                return "";
            }
            string t;
            for (int j  = 0; j < repeat; ++j)
            {
                t = t + tmp;
            }
            tmp = t;
            if (!s.empty() && s.top().type() == typeid(std::string))
            {
                tmp = std::any_cast<std::string>(s.top()) + tmp;
                s.pop();
            }
            i++;
        }
        else  // here isalpha(str[i]) == true
        {
            tmp = tmp + str[i];
            i++;
        }

        if (i == str.length() && tmp.length())
            s.push(std::make_any<std::string>(tmp));

    }
    string res;
    while (!s.empty())
    {
        try
        {
            res = std::any_cast<std::string>(s.top()) + res;
            s.pop();
        }
        catch (std::bad_any_cast const & e)
        {
            cout<<"Error: "<<e.what()<<" to std::string\n";
            return "";
        }
    }
    return res;


}
int main()
{
	string input;

	while(true)
	{
		cout <<"Please enter a valid Compresssed string: ";
		cin >> input;

		size_t start = 0;
		string deComp = GetDecompressedString(start, input);
		cout << "DeCompressed String: " << deComp << endl;
		string deComp1 = GetDecompressedString_v1(input);
		cout << "DeCompressed String v1: " << deComp1 << endl;
	}

	return 0;
}
