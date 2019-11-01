#include <string>

#include "runCaesarCipher.hpp"

std::string runCaesarCipher( const std::string& inputText, const size_t key, const bool encrypt )
{
  std::string OutputString;
  std::string alphabet {"ABCDEFGHIJKLMNOPQRSTUVQXYZ"};
  std::string::size_type alphabetSize {alphabet.size()};

  const size_t truncatedKey { key % alphabetSize };

  for(const char& c : inputText)
  {
    //numerical position in the alphabet
    const std::string::size_type position { alphabet.find(c) };

    std::string::size_type shifted { 0 };
    if (encrypt == true)
    {
      shifted = (position + key) % alphabetSize;
    }
    else
    {
      shifted = (position + alphabetSize - key) % alphabetSize;
    }

    OutputString += alphabet[shifted];
  }
  return OutputString;
}
