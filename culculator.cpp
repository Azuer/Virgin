#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <cctype> //isalpha()等

namespace Error {
    struct Zero_divide{};
    struct Syntax_error
    {
        const char* p;
        Syntax_error(const char* q) {
            p = q;
        }
    };
}
namespace Driver {
    int no_of_errors;
    std::istream* input;
    void skip();
}
// program:
//     END
//     expr_list END
//     expr_list:
//         expression PRINT            //PRINT是分号
//         expression PRINT expr_list
//     expression:
//         expression + term
//         expression - term
//     term:
//         term / primary
//         term * primary
//         primary
//     primary:
//         NUMBER
//         NAME
//         NAME = expression
//         - primary
//         ( expression )
namespace Parser{
    double expr(bool);
    double prim(bool);
    double term(bool);
}
namespace Lexer{
    enum Token_value { 
    NAME,   NUMBER, END,
    PLUS = '+',   MINUS = '-',  MUL = '*',  DIV = '/',
    PRINT = ';',    ASSIGN = '=',   LP = '(',   RP = ')'
 };
    Token_value curr_tok = PRINT;
    double number_value;
    std::string string_value;
}
using namespace std;
using namespace Lexer;
using namespace Parser;
using namespace Driver;
int no_of_errors;
map<string ,double>table;
double error (const string& s) {
    no_of_errors++;
    cerr << "error : " << s << '\n';
    return 1;
}
Token_value get_token () {
    char ch;
    do {
        if (!cin.get(ch))
            return curr_tok = END;
    } while (ch != '\n' && isspace(ch));

    switch (ch) {
        case ';' :
        case '\n' :
             return curr_tok;
        default : {
            if (isalpha(ch)) {
                string_value = ch;
                while (cin.get(ch) && isalnum(ch))
                    string_value.push_back(ch);
                cin.putback(ch);
                return curr_tok = NAME;
            }
            throw Error::Syntax_error("bad token");
        }
    }
}
//double expr (bool);
double prim (bool get) {
    if (get) 
        get_token();
    switch (curr_tok) {
        case NUMBER : {
            double v = number_value;
            get_token();
            return v;
        }
        case NAME : {
            double& v = table[string_value];
            if(get_token() == ASSIGN)
                v = expr(true);
            return v;
        }
        case MINUS :
            return -prim(true);
        case LP : {
            double e = expr(true);
            if (curr_tok != RP)
                return error( ") expected" );
            get_token();
            return e;
        }
        default :
            throw Error:Syntax_error("primary expected");

    }
}
double term (bool get) {//乘和除
    double left = prim(get);
    for (;;) {
        switch (curr_tok) {
            case MUL : {
                left *= prim(true);
                break;
            }
            case DIV : {
                if (double d = prim(true)){
                    left /= d;
                    break;
                }
                throw Error::Zero_divide();
            }
            default :
            return left;
        }
    }
}
double expr (bool get){//加和减
    double left = term(get);
    for (;;) {
        switch (curr_tok) {
            case PLUS : {
                left += term(true);
                break;
            }
            case MINUS : {
                left -=term (true);
                break;
            }
            default : 
                return left;
        }
    }
 }
void skip () {
    no_of_errors++;
    while (*input) {
        char ch;
        input -> get(ch);
        switch (ch) {
            case '\n' :
            case ';' :
                return;
        }
    }
}











// Token_vale get_token () {
//     char ch = 0;
//     cin >> ch;
//     switch (ch) {
//         case 0 :
//             return curr_tok = END;
//         case ';' :
//         case '*' :
//         case '/' :
//         case '+' :
//         case '-' :
//         case '(' :
//         case ')' :
//         case '=' :
//             return curr_tok = Token_vale(ch);
//         case '0' :
//         case '1' :
//         case '2' :
//         case '3' :
//         case '4' :
//         case '5' :
//         case '6' :
//         case '7' :
//         case '8' :
//         case '9' :
//         case '.' :
//             cin.putback(ch);
//             cin >> number_value;
//             return curr_tok = NUMBER;
//         default :
//             if (isalpha(ch)) //是否为字母 alphabat 
//             {
//                 cin.putback(ch);
//                 cin >> string_value;
//                 return curr_tok = NAME;
//             }
//             error("bad token");
//             return curr_tok = PRINT;
//     }
// }


istream* input; //指向输出流
int main(int argc, char const *argv[])
{
    switch (argc) {
        case 1 : {
            input = &cin;
            break;
        }
        case 2 : {
            input = new istringstream(argv[1]);
            break;
        }
        default : {
            error("too many arguments");
            return 1;
        }
    }
    table["pi"] = 3.1415926535897932385;
    table["e"] = 2.7182818284590452354;
    while (*input) {
        try {
            get_token();
        if (curr_tok == END)
            break;
        if (curr_tok == PRINT)
            continue;
        cout << expr(false) << '\n';
        }
        catch (Error::Zero_divide) {
            cerr << "attemp to divide by zero\n";
            if (curr_tok != PRINT)
                skip();
        }
        catch (Error::Syntax_error e) {
            cerr << "syntax error:" << e.q << "\n";
            if (curr_tok != PRINT)
                skip ();
        }
    }
    if(input != &cin)
        delete input;
    return no_of_errors;
}
void fuck (int a ...){
    //
}