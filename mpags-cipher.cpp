// Standard Library includes
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
// For std::isalpha and std::isupper
#include <cctype>

#include "TransformChar.hpp"
#include "runCaesarCipher.hpp"

bool processCommandLine(const std::vector<std::string>& args, bool& helpRequested,bool& versionRequested,std::string& inputFileName,std::string& outputFileName )
{
  typedef std::vector<std::string>::size_type size_type;
  const size_type nargs {args.size()};

   for (size_type i {1}; i < nargs; ++i) {

    if (args[i] == "-h" || args[i] == "--help") {
      helpRequested = true;
    }
    else if (args[i] == "--version") {
      versionRequested = true;
    }
    else if (args[i] == "-i") {
      // Handle input file option
      // Next element is filename unless -i is the last argument
      if (i == nargs-1) {
	    std::cerr << "[error] -i requires a filename argument" << std::endl;
	// exit main with non-zero return to indicate failure
	    return false;
      }
      else {
	// Got filename, so assign value and advance past it
	    inputFileName = args[i+1];
	    ++i;
      }
    }
    else if (args[i] == "-o") {
      // Handle output file option
      // Next element is filename unless -o is the last argument
      if (i == nargs-1) {
	      std::cerr << "[error] -o requires a filename argument" << std::endl;
	      // exit main with non-zero return to indicate failure
	      return false;
      }
      else {
      	// Got filename, so assign value and advance past it
	      outputFileName = args[i+1];
	      ++i;
      }
    }
    else {
      // Have an unknown flag to output error message and return non-zero
      // exit status to indicate failure
      std::cerr << "[error] unknown argument '" << args[i] << "'\n";
      return false;
    }
  }

   return true;
	
	

}



/*
std::string runCaesarCipher(  std::string& inputText, const size_t key, const bool encrypt )
{
  std::string OutputString;
  std::string Alphabet {"ABCDEFGHIJKLMNOPQRSTUVQXYZ"};


  int AsciiStart = 65;
  int position;
  int shifted;
  char out;

  for(char& c : inputText)
  {
    position = int(c) - 65;

    if (encrypt == 1)
    {
      shifted = position + (int)key;
    }
    else
    {
      shifted = position - (int)key;
    }

    
    if (shifted < 0)
    {
      shifted = abs(shifted) + 13;
    }
    if (shifted > 25)
    {
      shifted = abs(shifted - 26);
    }

    OutputString = OutputString + Alphabet[shifted];



  }
  return OutputString;
}
*/


// Main function of the mpags-cipher program
int main(int argc, char* argv[])
{
  // Convert the command-line arguments into a more easily usable form
  const std::vector<std::string> cmdLineArgs {argv, argv+argc};

  // Add a typedef that assigns another name for the given type for clarity
  typedef std::vector<std::string>::size_type size_type;
  const size_type nCmdLineArgs {cmdLineArgs.size()};

  // Options that might be set by the command-line arguments
  bool helpRequested {false};
  bool versionRequested {false};
  std::string inputFile {""};
  std::string outputFile {""};
  std::string outputText {""};

  // Process command line arguments - ignore zeroth element, as we know this to
  // be the program name and don't need to worry about it

 bool processedOK { processCommandLine(cmdLineArgs, helpRequested, versionRequested,inputFile, outputFile) };
 if ( ! processedOK ) {
   std::cerr << "[error] problem processing command line arguments" << std::endl;
	 return 1;
 }

  // Handle help, if requested
  if (helpRequested) {
    // Line splitting for readability
    std::cout
      << "Usage: mpags-cipher [-i <file>] [-o <file>]\n\n"
      << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
      << "Available options:\n\n"
      << "  -h|--help        Print this help message and exit\n\n"
      << "  --version        Print version information\n\n"
      << "  -i FILE          Read text to be processed from FILE\n"
      << "                   Stdin will be used if not supplied\n\n"
      << "  -o FILE          Write processed text to FILE\n"
      << "                   Stdout will be used if not supplied\n\n";
    // Help requires no further action, so return from main
    // with 0 used to indicate success
    return 0;
  }

  // Handle version, if requested
  // Like help, requires no further action,
  // so return from main with zero to indicate success
  if (versionRequested) {
    std::cout << "0.1.0" << std::endl;
    return 0;
  }

  // Initialise variables for processing input text
  char inputChar {'x'};
  std::string inputText {""};

  // Read in user input from stdin/file
  if (!inputFile.empty()) {
    std::ifstream in_file {inputFile};
    bool ok_to_read = in_file.good();

    if ( ! ok_to_read )
    {
      std::cerr << "[error] reading from file " << inputFile << std::endl;
      return 1;
    }

    while (in_file >> inputChar)
    {
      outputText += transformChar(inputChar);
    }

  } else {

    // Loop over each character from user input
    // (until Return then CTRL-D (EOF) pressed)
    while(std::cin >> inputChar)
    {
      outputText += transformChar(inputChar);
    }
  }

  outputText = runCaesarCipher(outputText,1,true);

  // Output the transliterated text
  if (!outputFile.empty()) {

      

          std::ofstream out_file{ outputFile, std::ios::app };
          bool ok_to_read = out_file.good();

    if ( ! ok_to_read )
    {
      std::cerr << "[error] writing to file " << outputFile << std::endl;;
      return 1;
    }

    out_file << outputText << std::endl;;
  } else {

  std::cout << outputText  << std::endl;
  }

  // No requirement to return from main, but we do so for clarity
  // and for consistency with other functions
  return 0;
}

