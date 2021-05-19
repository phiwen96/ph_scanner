#include <catch2/catch.hpp>
#include <ph_scanner/scanner.hpp>
#include <ph_scanner/token.hpp>

using namespace std;

TEST_CASE("")
{
    scanner sc {.m_source = "2then+3(false/-2.4"};
    vector <token> tk = sc.scan_tokens ();
    
    
    REQUIRE (tk.size() == 9);

    REQUIRE (tk [0].m_type == token::type::number);
    REQUIRE (tk [1].m_type == token::type::THEN);
    REQUIRE (tk [2].m_type == token::type::plus);
    REQUIRE (tk [3].m_type == token::type::number);
    REQUIRE (tk [4].m_type == token::type::left_paranthesis);
    REQUIRE (tk [5].m_type == token::type::FALSE);
    REQUIRE (tk [6].m_type == token::type::slash);
    REQUIRE (tk [7].m_type == token::type::minus);
    REQUIRE (tk [8].m_type == token::type::number);
//    for (auto i : scanner::m_keywords)
//        cout << i.first << " : " << i.second << endl;
}





