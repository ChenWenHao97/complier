#include <iostream>
#include <ctype.h>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include<set>
using namespace std;
static string reserve[] = {"int", "double", "char", "if",
                           "else", "for", "while", "do",
                           "return", "break", "continue","printf"};
set<string> table;


enum tokentype
{
    kttempty,
    ktterror,
    kttnum,
    kttvarible,
    kttsymbol,
    kttint,
    kttdouble,
    kttchar,
    kttif,
    kttelse,
    kttfor,
    kttwhile,
    kttdo,
    kttreturn,
    kttbreak,
    kttcontinue
};
class selfexe
{
  private:
    int line;       //行号
    tokentype type; //类型
    ifstream fin;
    ostringstream sin;
    string txt;  //存放读入的代码段
    string word; //存放构成单词的字符串
    char ch;     //输入的字符
    int num;
    bool issymbol(char ch){if(ch =='!'||ch =='^'||ch =='@'||ch =='#'||ch =='$'||ch =='%') return true;else return false;}

  public:
    selfexe(const char *str) : fin(str), line(1), ch('\0'), num(1), type(tokentype::kttempty)
    {
        sin << fin.rdbuf();
        txt = sin.str();
        fin.close();
        fin.clear();
    }
    void show(void)
    {
        cout << txt << endl;
    }
    void scan(void);
};

void selfexe::scan(void)
{
    int i = 0;
    do
    {
        ch = txt[i++];
        if (ch == '\n')
            line++;
    } while (ch == ' ' || ch == '\n');
    cout << "line " << line << " :" << endl;

    // type：0 数字
    // type：1 自己命名
    // type：2 括号等

    while (ch != '\0')
    {
        while (ch == ' ' || ch == '\n')
        {
            if (ch == '\n')
            {
                line++;
                cout<<endl;
                cout << "line:" << line << endl;
            }
            ch = txt[i++];
        }
        if (ch == '_') //带_变量的时候
        {
            word += ch;
            ch = txt[i++];
            // if (isalpha(ch) || isdigit(ch))
            // {
            //     type = kttvarible;
            //     word += ch;
            //     ch=txt[i++];
                while (isalpha(ch) || isdigit(ch)|| ch =='_')
                {
                    type = kttvarible;
                    word += ch;
                    ch = txt[i++];
                }
            // }

            if(issymbol(ch))
            {
                type = ktterror;
            // else
            // {
            //     type = ktterror;
            //     word += ch;
            //     ch = txt[i++];
            //     while (isalpha(ch) || isdigit(ch) || ch == '_')
            //     {
            //         word += ch;
            //         ch = txt[i++];
            //         cout <<"word is:"<<word<<endl;
            //         cout<<"ch is"<<ch<<endl;
            //     }
            }
            switch (type)
            {
                case ktterror:
                    cout << "<-1," << word << ">" << endl;
                    break;
                case kttvarible:
                    cout << "<1," << word << ">" << endl;
                    table.insert(word);
                    break;
            }
            word.clear();
            type = kttempty;
        }

        //处理保留字和字母的变量
        if (isalpha(ch))
        {
            type = kttvarible;
            word += ch;
            ch = txt[i++];

            while (isalpha(ch) || isdigit(ch) || ch == '_')
            {
                word += ch;
                ch = txt[i++];
            }
            int flag = 1;
            for (string i : reserve)
            {
                if (word == i)
                {
                    cout << "<2," << i << ">" << endl;
                    word.clear();
                    flag = 0;
                    type = kttvarible;
                    break;
                }
            }
            if (flag)
            {
                cout << "<2," << word << ">" << endl;
                table.insert(word);
                word.clear();
                type = kttempty;
            }
        }

        //处理整数
        if (isdigit(ch))
        {
            word += ch;
            ch = txt[i++];
            type = kttnum;
            while (isdigit(ch))
            {
                word += ch;
                ch = txt[i++];

            }
            cout << "<3," << word << ">" << endl;
            word.clear();
            type = kttempty;
        }

        //处理符号
        switch (ch)
        {
        case '+':
            cout << "<4," << ch << ">" << endl;
            ch = txt[i++];
            break;
        case '-':
            cout << "<4," << ch << ">" << endl;
            ch = txt[i++];
            break;
        case '*':
            cout << "<4," << ch << ">" << endl;
            ch = txt[i++];
            break;
        // case '/':
        //     cout << "<4," << ch << ">" << endl;
        //     ch = txt[i++];
        //     break;
        case '=':
            if (txt[i] == '=')
            {
                word += ch;
                ch = txt[i++];
                word += ch;
                ch = txt[i++];
                cout << "<4," << word << ">" << endl;
                word.clear();
                break;
            }
            else
            {
                cout << "<4," << ch << ">" << endl;
                ch = txt[i++];
                word.clear();
                break;
            }
        case '<':
            if (txt[i] == '=')
            {
                word += ch;
                ch = txt[i++];
                word += ch;
                ch = txt[i++];
                cout << "<4," << ch << ">" << endl;
                word.clear();
                break;
            }
            else
            {
                cout << "<4," << ch << ">" << endl;
                ch = txt[i++];
                break;
            }
        case '>':
            if (txt[i] == '=')
            {
                word += ch;
                ch = txt[i++];
                word += ch;
                ch = txt[i++];
                cout << "<4," << word << ">" << endl;
                word.clear();
                break;
            }
            else
            {
                cout << "<4," << ch << ">" << endl;
                ch = txt[i++];
                break;
            }
        case '!':
            if (txt[i] == '=')
            {
                word += ch;
                ch = txt[i++];
                word += ch;
                ch = txt[i++];
                cout << "<4," << word << ">" << endl;
                word.clear();
                break;
            }
            else
            {
                cout << "<4," << ch << ">" << endl;
                ch = txt[i++];
                break;
            }

        //处理分隔符
        case ',':
            cout << "<5," << ch << ">" << endl;
            ch = txt[i++];
            break;
        case ';':
            cout << "<5," << ch << ">" << endl;
            ch = txt[i++];
            break;
        case ':':
            cout << "<5," << ch << ">" << endl;
            ch = txt[i++];
            break;

        //处理界符
        case '(':
            cout << "<6," << ch << ">" << endl;
            ch = txt[i++];
            break;
        case ')':
            cout << "<6," << ch << ">" << endl;
            ch = txt[i++];
            break;
        case '[':
            cout << "<6," << ch << ">" << endl;
            ch = txt[i++];
            break;
        case ']':
            cout << "<6," << ch << ">" << endl;
            ch = txt[i++];
            break;
        case '{':
            cout << "<6," << ch << ">" << endl;
            ch = txt[i++];
            break;
        case '}':
            cout << "<6," << ch << ">" << endl;
            ch = txt[i++];
            break;
        case '"':
            cout << "<6," << ch << ">" << endl;
            ch = txt[i++];
            break;
        // case '\'':
        //     cout << "<6," << ch << ">" << endl;
        //     ch = txt[i++];
        //     break;
        case ' ':
            break;
        case '\n':
            break;
        default:
            cout << "<-1," << ch << ">" << endl;
            ch = txt[i++];
            break;
        }
        
    }
}

int main()
{
    const char *fn = "test.c"; //文件名
    selfexe l(fn);
    l.show();
    l.scan();

    cout << "++++++++++++++++++++++++++++++++++++++++++++" << endl;
    for (string i : table)
    {
        cout << i << endl;
    }
    return 0;
}
