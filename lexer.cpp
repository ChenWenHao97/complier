#include<iostream>
#include<string>
#include<map>
#include<ctype>
using namespace std;
enum Tag{NUM=256,ID,TRUE,FALSE};//限定在全局变量Tag之中
map<string,Word> words;

class Token{
    public:
        Tag tag;
        Token(Tag t):tag(t){}
};
class Num:public Token{
    public:
        int value;
        Num(int v):Token(Tag::NUM),value(v){}
};
class Word:public Token{
    public:
        string lexeme;
        Word(Tag t,string s):Token(t),lexeme(s){}
};
class lexer{
    public:  
        int line;
        void reserve(Word t){words.emplace(t.lexeme,t);};
        lexer():line(1),peek(' ')
        {
            reserve(Word(Tag::TRUE,"true"));
            reserve(Word(Tag::FALSE,"false"));
        }
        Token scan()
        {
            for(;;cin >> peek;)
            {
                if(peek == ' '|| peek == '\t') 
                    continue;
                else if(peek == '\n')
                {
                    line += 1;
                }
                else  
                    break;
            }
            if(isdigit(peek))
            {
                int v = 0;
                do{
                    v = 10*v + peek-'0';
                    cin >> peek;
                }while(isdigit(peek));
            }
            if(isalpha(peek))
            {
                string b;
                do{
                    b += peek;
                    cin >>peek;
                }while(isalpha(peek));
                Word w = words.get(b);
                if(w!=NULL) return w;
                w = new Word(Tag::ID,b);
                words.put(b,w);

                return w;
            }
            Token t = new Token(peek);
            peek = ' ';//peek设置成一个空格，下一次使用scan时，空格被删除
            return t;
        }

    private: 
        char peek;
    
};
int main()
{
    lexer analysize();
    Token result = analysize.scan();

    
}