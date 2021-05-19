#pragma once
#include <ph_scanner/token.hpp>

using namespace std;

#define IS_DIGIT(x) (x >= '0' and x <= '9')



struct scanner
{
    string m_source;
    vector <token> m_tokens;
    
    int m_start {0};
    int m_current {0};
    int m_line {1};
    
    
    
    vector <token> scan_tokens ()
    {
        while (not is_at_end ())
        {
            m_start = m_current;
            
            
        }
    }
    
    
    
private:
    void scan_token ()
    {
        char c = advance ();
        
        if (c == '-')
        {
            //            value.push_back ('-');
            add_token (token::type::minus);
            //            goto minus;
            
        } else if (c == '+')
        {
            //            cout << "ADD" << endl;
            add_token (token::type::star);
            
        } else if (c == '(')
        {
            add_token (token::type::left_paranthesis);
            
        } else if (c == ')')
        {
            add_token (token::type::right_paranthesis);
            
        } else if (c == '/')
        {
            if (match ('/'))
            {
                while (peek () != '\n')
                {
                    advance ();
                }
                add_token (token::type::comment);
                
            } else
            {
                add_token (token::type::slash);
            }
            
        } else if (c == '*')
        {
            add_token (token::type::star);
            
        } else if (c == ' ')
        {
            add_token (token::type::space);
            
        } else if (c == '.')
        {
            add_token (token::type::dot);
            
        } else if (c == ',')
        {
            add_token (token::type::comma);
            
        } else if (c == ';')
        {
            add_token (token::type::semicolon);
            
        } else if (c == ':')
        {
            add_token (token::type::colon);
            
        }  else if (c == '\n')
        {
            add_token (token::type::newline);
            ++ m_line;
            
        } else if (c == '\t')
        {
            add_token (token::type::tab);
            
        } else if (IS_DIGIT (c))
        {
            number ();
        } else if (c == '!')
        {
            add_token (match ('=') ? token::type::bang_equal : token::type::bang);
        }
    }
    auto advance () -> char
    {
        return m_source [m_current++];
    }
    /**
     It’s like a conditional advance(). We only consume the current character if it’s what we’re looking for.
     */
    auto match (char expected) -> bool
    {
        if (is_at_end ()) return false;
        if (m_source [m_current] != expected) return false;
        
        m_current++;
        return true;
    }
    void add_token (token::type type)
    {
        m_tokens.push_back (token {
            type,
            string {m_source.begin (), m_source.begin () + m_current},
            m_line
        });
    }
    auto is_at_end () -> bool
    {
        return m_current >= m_source.length ();
    }
    auto peek() -> char
    {
        if (is_at_end ()) return '\0';
        return m_source [m_current];
    }
    auto number () -> void
    {
        while (IS_DIGIT (peek ()))
        {
            advance ();
        }
        
        if (peek () == '.')
        {
            while (IS_DIGIT (peek ()))
            {
                advance ();
            }
        }
        
        add_token (token::type::number);
    }
};
