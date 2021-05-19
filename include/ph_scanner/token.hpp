#pragma once

using namespace std;

/**
 // Single-character tokens.
   LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
   COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

   // One or two character tokens.
   BANG, BANG_EQUAL,
   EQUAL, EQUAL_EQUAL,
   GREATER, GREATER_EQUAL,
   LESS, LESS_EQUAL,

   // Literals.
   IDENTIFIER, STRING, NUMBER,

   // Keywords.
   AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
   PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

   EOF
 */
#define KEY_WORDS \
X (AND, "and") \
X (OR, "or") \
X (TRUE, "true") \
X (FALSE, "false") \
X (IF, "if") \
X (ELSE, "else") \
X (THEN, "then") \




#define TOKENS \
KEY_WORDS \
X (bang) \
X (bang_equal) \
X (equal_equal) \
X (equal) \
X (less) \
X (greater) \
X (left_paranthesis) \
X (right_paranthesis) \
X (plus) \
X (minus) \
X (star) \
X (division) \
X (number) \
X (variable) \
X (left_curly_bracket) \
X (right_curly_bracket) \
X (left_bracket) \
X (right_bracket) \
X (dot) \
X (semicolon) \
X (space) \
X (comma) \
X (tab) \
X (newline) \
X (colon) \
X (unknown) \
X (factor) \
X (term) \
X (expression) \
X (slash) \
X (comment) \
X (string) \
X (identifier)






struct token
{
    enum struct type
    {
#define X(a, ...) \
a,
        TOKENS
#undef X
        
    };
    
//    auto operator== (token const& other) -> bool
//    {
//        return m_type == other.m_type and m_lexeme == other.m_lexeme;
//    }
//
//    auto operator== (type const& t) -> bool
//    {
//        return m_type == t;
//    }
    
    type m_type;
    string m_lexeme;
    int m_line;
    
    
};






inline ostream& operator<< (ostream& os, token const& t)
{
    switch (t.m_type)
    {
#define X(x, ...) \
case token::type::x: \
os << "<" << #x << ">"; \
break;
            
            TOKENS
#undef X
    }
    
    return os;
}

#undef TOKENS
