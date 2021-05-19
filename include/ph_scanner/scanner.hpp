#pragma once
#include <ph_scanner/token.hpp>
#include <unordered_map>

using namespace std;

#define IS_DIGIT(x) (x >= '0' and x <= '9')
#define IS_ALPHA(x) (x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z') || x == '_'

/**
 maximal munch. When two lexical grammar rules can both match a chunk of code that the scanner is looking at, whichever one matches the most characters wins.
 */


struct scanner
{
    string m_source {};
    vector <token> m_tokens {};
    inline static unordered_map <string, token::type> m_keywords = {
    #define X(x, y) \
        {y, token::type::x},
        
        KEY_WORDS
    #undef X
    };

    
    
    int m_start {0};
    int m_current {0};
    int m_line {1};
    
    
    
    vector <token> scan_tokens ()
    {
        while (not is_at_end ())
        {
            m_start = m_current;
            scan_token ();
        }
        
        return m_tokens;
    }
    
    
    
private:
    void scan_token ()
    {
        char c = advance ();
        
        if (c == '-')
        {
            add_token (token::type::minus);
            
        } else if (c == '+')
        {
            add_token (token::type::plus);
            
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
            
        } else if (c == '!')
        {
            add_token (match ('=') ? token::type::bang_equal : token::type::bang);
            
        } else if (IS_DIGIT (c))
        {
            number ();
            
        }  else if (IS_ALPHA (c))
        {
            identifier ();
            
        } else
        {
            throw;
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
        add_token (type, string {m_source.begin (), m_source.begin () + m_current});
    }
    void add_token (token::type type, string s)
    {
        m_tokens.push_back (token {
            type,
            s,
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
    auto peek_next () -> char
    {
        if (m_current + 1 >= m_source.size ()) return '\0';
        return m_source [m_current + 1];
    }
    auto number () -> void
    {
        while (IS_DIGIT (peek ()))
        {
            advance ();
        }
        
        if (peek () == '.' and IS_DIGIT (peek_next ()))
        {
            advance ();
            
            while (IS_DIGIT (peek ()))
            {
                advance ();
            }
        }
        
        add_token (token::type::number);
    }
    auto _string () -> void
    {
        while (peek () != '"' and not is_at_end ())
        {
            if (peek () == '\n')
            {
                ++ m_line;
            }
            
            advance ();
        }
        
        if (is_at_end ())
        {
            //      Lox.error(line, "Unterminated string.");
            return;
        }
        
        // the closing "
        advance ();
        
        
        string value = string {m_source.begin () + 1, m_source.begin () + (m_current - 1)};
        add_token (token::type::string, value);
    }
    auto identifier () -> void
    {
        while (IS_ALPHA (peek ()) or IS_DIGIT (peek ()))
        {
            advance ();
        }
        
        string text = string {m_source.begin () + m_start, m_source.begin () + m_current};
        
        if (auto found = m_keywords.find (text);
                found != m_keywords.end ()) {
            
            add_token (found -> second);
            
        } else
        {
            add_token (token::type::identifier);
        }
    }
   
};
