#include <string>
#include <cctype>

#include "runCaesarCipher.hpp"

std::string runCaesarCipher( const std::string& inputText, const size_t key, const bool encrypt )
{
  std::string OutputString;
  std::string Alphabet {"ABCDEFGHIJKLMNOPQRSTUVQXYZ"};


  int AsciiStart = 65;
  int position;
  int shifted;
  char out;

  for(char& c : inputText)
  {
    //numerical position in the alphabet, based off (decimal) AScii value
    position = int(c) - 65;

    if (encrypt == true)
    {
      shifted = position + (int)key;
    }
    else
    {
      shifted = position - (int)key;
    }

    
    if (shifted < 0)
    {
      shifted = abs(shifted) + 26;
    }
    if (shifted > 25)
    {
      shifted = abs(shifted - 26);
    }

    OutputString = OutputString + Alphabet[shifted];



  }
  return OutputString;
}