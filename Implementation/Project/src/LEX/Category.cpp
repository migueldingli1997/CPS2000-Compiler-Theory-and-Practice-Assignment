#include <cstdio>
#include "Category.h"

namespace LEX {

    Category charCat(const char ch) {

        switch (ch) {
            case '.':
                return CT_DecimalPt;
            case '+':
            case '-':
                return CT_PlusMinus;
            case '*':
                return CT_Star;
            case '/':
                return CT_FwSlash;
            case '>':
            case '<':
                return CT_GrtrLess;
            case '!':
                return CT_Exclamation;
            case '=':
                return CT_Equals;
            case '_':
                return CT_Underscore;
            case '"':
                return CT_Quotes;
            case ':':
            case '(':
            case ')':
            case ',':
            case ';':
            case '{':
            case '}':
                return CT_OtherPunct;
            case '\n':
                return CT_Newline;
            case EOF:
                return CT_EOF;
            default:
                break;
        }

        if (ch >= '0' && ch <= '9') {
            return CT_Digit;
        } else if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
            return CT_Letter;
        } else if (ch >= '\x20' && ch <= '\x7E') {
            return CT_Printable;
        } else {
            return CT_Other;
        }
    }
}