#include <iostream>
#include <ctype.h>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include<vector>
using namespace std;
static string reserve[] = {"int", "double", "char", "if",
                           "else", "for", "while", "do",
                           "return", "break", "continue"};
vector<string> table;
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

  public:
    selfexe(const char *str) : fin(str), line(1), ch('\0'), num(1),type(tokentype::kttempty)
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
        if (txt[i] == '\n')
            line++;
        i++;
    } while (txt[i] == '\0' || txt[i] == '\n');

    // type：0 数字
    // type：1 自己命名
    // type：2 括号等

    while (ch != '\0')
    {
        while (ch == '\0' || ch == '\n')
        {
            if (ch == '\n')
            {
                line++;
                cout << "line:" << line << endl;
            }
        }
        if (ch == '_')//带_变量的时候
        {
            word += ch;
            ch = txt[i++];
            if (isalpha(ch) || isdigit(ch))
            {
                type = kttvarible;
                word += ch;
                txt[i++];
                while (isalpha(ch) || isdigit(ch))
                {
                    word+=ch;
                    ch = txt[i++];
                }
            }
            else
            {
                type = ktterror;
                word += ch;
                ch = txt[i++];
                while(isalpha(ch)||isdigit(ch)||ch=='_')
                {
                    word += ch;
                    ch = txt[i++];
                }
            }
            switch(type) 
            {
                case ktterror:
                    cout <<"<-1,"<<word<<">"<<endl;
                    break;
                case kttvarible:
                    cout <<"<1,"<<word<<">"<<endl;
                    table.push_back(word);
                    break;
            }

            word.clear();
            type = kttempty;
        }

        //处理保留字和字母的变量
        if(isalpha(ch)||isdigit(ch))
        {
            type = kttvarible;
        }
        //处理整数
        //处理符号
    }
}
int main()
{
    const char *fn = "test.c"; //文件名
    selfexe l(fn);
    l.show();
    l.scan();
    return 0;
}