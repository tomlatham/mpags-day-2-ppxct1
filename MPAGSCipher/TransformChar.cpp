#include <string>
#include <cctype>

#include "TransformChar.hpp"

std::string transformChar( const char inChar )
{
// Uppercase alphabetic characters
     if (std::isalpha(inChar)) {
       std::string temp{""};
       temp = std::toupper(inChar);
       return temp;
    //   //continue;
     }

    // Transliterate digits to English words
    switch (inChar) {
      case '0':
	return "ZERO";
	break;
      case '1':
	return "ONE";
	break;
      case '2':
	return "TWO";
	break;
      case '3':
	return "THREE";
	break;
      case '4':
	return "FOUR";
	break;
      case '5':
	return "FIVE";
	break;
      case '6':
	return "SIX";
	break;
      case '7':
	return "SEVEN";
	break;
      case '8':
	return "EIGHT";
	break;
      case '9':
	return "NINE";
	break;
  default:
  return "";
  break;
    }

    // If the character isn't alphabetic or numeric, DONT add it.
    // Our ciphers can only operate on alphabetic characters.
    return "";
}