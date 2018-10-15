#include <iostream>
#include "LA.h"

using namespace std;

LA::LA(const char * s):fin(s),line(1), num(0), fg(0), ch('\0')
{
    sin <<fin.rdbuf();
    txt = sin.str();
    fin.close();
    fin.clear();
}

void LA::scan()
{
    int p = 0;

    //读取第一个非空字符
    do{
        ch = txt[p++];
        if(ch == '\n')
            line++;
    } while(ch == ' ' || ch == '\n');
    cout<<"line "<<line<<" :"<<endl;

    while(ch != '\0'){
        while(ch == ' ' || ch == '\n'){
            if(ch == '\n'){
                line++;
                cout<<"line "<<line<<" :"<<endl;
            }
            ch = txt[p++];
        }

        //处理'_'开头的变量
        if(ch == '_'){
            word += ch;
            ch = txt[p++];
            if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')){
                fg = 2;
                word += ch;
                ch = txt[p++];
                while((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || ch == '_'){
                    word += ch;
                    ch = txt[p++];
                }
            }
            else{
                fg = -1;
                word += ch;
                ch = txt[p++];
                while((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || ch == '_'){
                    word += ch;
                    ch = txt[p++];
                }
            }
            switch(fg){
                case -1: cout<<"error: "<<'<'<<word<<'>'<<endl; break;
                case 2: cout<<'<'<<fg<<','<<word<<'>'<<endl; break;
                default: break;
            }
            word.clear();
            fg = 0;
        }

        //处理保留字和字母开头的变量
        if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')){
            fg = 1;
            word += ch;
            ch = txt[p++];
            while((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || ch == '_'){
                word += ch;
                ch = txt[p++];
            }
            for(int i = 0; i < 12; i++){
                if(i == 11 && word != rsv_words[i])
                    fg++;
                if(word == rsv_words[i]){
                    cout<<'<'<<fg<<','<<word<<'>'<<endl;
                    word.clear();
                    break;
                }
            }
            if(fg == 2)
                cout<<'<'<<fg<<','<<word<<'>'<<endl;
            word.clear();
            fg = 0;
        }

        //处理整数
        if(ch >= '0' && ch <= '9'){
            fg = 3;
            num = 10 * num + (ch - '0');
            ch = txt[p++];
            while(ch >= '0' && ch <= '9'){
                num = 10 * num + (ch - '0');
                ch = txt[p++];
            }
            cout<<'<'<<fg<<','<<num<<'>'<<endl;
            num = 0;
            fg = 0;
        }

        //处理符号
        switch(ch){
            //处理运算符
            case '+': fg = 4; cout<<'<'<<fg<<','<<ch<<'>'<<endl; ch = txt[p++]; break;
            case '-': fg = 4; cout<<'<'<<fg<<','<<ch<<'>'<<endl; ch = txt[p++]; break;
            case '*': fg = 4; cout<<'<'<<fg<<','<<ch<<'>'<<endl; ch = txt[p++]; break;
            case '/': fg = 4; cout<<'<'<<fg<<','<<ch<<'>'<<endl; ch = txt[p++]; break;
            case '=':
                fg = 4;
                if(txt[p] == '='){
                    word += ch;
                    ch = txt[p++];
                    word += ch;
                    ch = txt[p++];
                    cout<<'<'<<fg<<','<<word<<'>'<<endl;
                    word.clear();
                    break;
                }
                else{
                    cout<<'<'<<fg<<','<<ch<<'>'<<endl;
                    ch = txt[p++];
                    break;
                }
            case '<':
                fg = 4;
                if(txt[p] == '='){
                    word += ch;
                    ch = txt[p++];
                    word += ch;
                    ch = txt[p++];
                    cout<<'<'<<fg<<','<<word<<'>'<<endl;
                    word.clear();
                    break;
                }
                else{
                    cout<<'<'<<fg<<','<<ch<<'>'<<endl;
                    ch = txt[p++];
                    break;
                }
            case '>':
                fg = 4;
                if(txt[p] == '='){
                    word += ch;
                    ch = txt[p++];
                    word += ch;
                    ch = txt[p++];
                    cout<<'<'<<fg<<','<<word<<'>'<<endl;
                    word.clear();
                    break;
                }
                else{
                    cout<<'<'<<fg<<','<<ch<<'>'<<endl;
                    ch = txt[p++];
                    break;
                }
            case '!':
                fg = 4;
                if(txt[p] == '='){
                    word += ch;
                    ch = txt[p++];
                    word += ch;
                    ch = txt[p++];
                    cout<<'<'<<fg<<','<<word<<'>'<<endl;
                    word.clear();
                    break;
                }
                else{
                    cout<<'<'<<fg<<','<<ch<<'>'<<endl;
                    ch = txt[p++];
                    break;
                }

            //处理分隔符
            case ',': fg = 5; cout<<'<'<<fg<<','<<ch<<'>'<<endl; ch = txt[p++]; break;
            case ';': fg = 5; cout<<'<'<<fg<<','<<ch<<'>'<<endl; ch = txt[p++]; break;
            case ':': fg = 5; cout<<'<'<<fg<<','<<ch<<'>'<<endl; ch = txt[p++]; break;

            //处理界符
            case '(': fg = 6; cout<<'<'<<fg<<','<<ch<<'>'<<endl; ch = txt[p++]; break;
            case ')': fg = 6; cout<<'<'<<fg<<','<<ch<<'>'<<endl; ch = txt[p++]; break;
            case '[': fg = 6; cout<<'<'<<fg<<','<<ch<<'>'<<endl; ch = txt[p++]; break;
            case ']': fg = 6; cout<<'<'<<fg<<','<<ch<<'>'<<endl; ch = txt[p++]; break;
            case '{': fg = 6; cout<<'<'<<fg<<','<<ch<<'>'<<endl; ch = txt[p++]; break;
            case '}': fg = 6; cout<<'<'<<fg<<','<<ch<<'>'<<endl; ch = txt[p++]; break;
            case '"': fg = 6; cout<<'<'<<fg<<','<<ch<<'>'<<endl; ch = txt[p++]; break;
            case '\'': fg = 6; cout<<'<'<<fg<<','<<ch<<'>'<<endl; ch = txt[p++]; break;
        }
    }


}
#include <iostream>
#include "LA.h"

int main() {
    const char *fn = "test.c";
    LA l(fn);
    l.show();
    l.scan();
    return 0;
}