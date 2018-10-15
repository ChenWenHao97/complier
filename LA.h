#ifndef LEXICAL_ANALYZER_LA_H
#define LEXICAL_ANALYZER_LA_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

//保留字数组
static string rsv_words[12] = {"int", "double", "char", "if", "else", "for", "while", "do", "return", "break", "continue", "main"};

class LA
{
  private:
    ifstream fin;
    ostringstream sin;
    string txt;  //存放读入的代码段
    string word; //存放构成单词的字符串
    int fg;      //种别码
    int line;    //记录行数
    int num;     //存放整数
    char ch;     //存放每次读入的字符
  public:
    void show() { cout << txt << endl; };
    LA(const char *s);
    void scan();
};

#endif //LEXICAL_ANALYZER_LA_H