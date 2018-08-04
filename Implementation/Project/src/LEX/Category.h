#ifndef CPS2000_CATEGORY_H
#define CPS2000_CATEGORY_H

namespace LEX {

    enum Category {
        CT_Digit,       // digit
        CT_DecimalPt,   // decimal point
        CT_Letter,      // letter
        CT_Printable,   // printable character
        CT_Star,        // asterisk
        CT_FwSlash,     // forward slash
        CT_PlusMinus,   // plus or minus
        CT_GrtrLess,    // greater or less than
        CT_Exclamation, // exclamation mark
        CT_Equals,      // equals symbol
        CT_Underscore,  // underscore symbol
        CT_Quotes,      // double-quotes
        CT_OtherPunct,  // other punctuation
        CT_Newline,     // newline symbol
        CT_EOF,         // end-of-file symbol
        CT_Other,       // other
        NUMBER_OF_CATEGORIES
    };

    Category charCat(const char ch);
}

#endif //CPS2000_CATEGORY_H
