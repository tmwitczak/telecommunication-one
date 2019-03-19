/////////////////////////////////////////////////////////////////////// Includes
#include "BinaryFileEncoder.hpp"
#include "CorrectionMatrix.hpp"

#include <fstream>
#include <iostream>

/////////////////////////////////////////////////////////////////////////// Main
int main()
{
    // Constants
    int const NUMBER_OF_PARITY_BITS = 4,
            NUMBER_OF_MESSAGE_BITS = 8;

    // Code for correcting 1 bit
    CorrectionMatrix const correctionMatrixOneBit(
            NUMBER_OF_PARITY_BITS,
            NUMBER_OF_MESSAGE_BITS + NUMBER_OF_PARITY_BITS,
            "110110101000"
            "101101100100"
            "011100010010"
            "000011110001"
    );
    /*CorrectionMatrix const correctionMatrixTwoBits(
            NUMBER_OF_PARITY_BITS,
            NUMBER_OF_MESSAGE_BITS + NUMBER_OF_PARITY_BITS,
            "01111111 10000000"
            "10111111 01000000"
            "11011111 00100000"
            "11101111 00010000"
            "11110111 00001000"
            "11111011 00000100"
            "11111101 00000010"
            "11111110 00000001"
    );*/

    // User dialog
    std::string inputFilename,
                outputFilename;
    char mode;

    std::cout << "Enter input filename: ";
    std::getline(std::cin, inputFilename);
    std::cout << "Enter output filename: ";
    std::getline(std::cin, outputFilename);

    std::cout << "Do you want to [e]ncode or [d]ecode file: ";
    std::cin >> mode;

    // File operations
    BinaryFileEncoder binaryFileEncoder;

    if (mode == 'e' || mode == 'E')
        binaryFileEncoder.encode(inputFilename, outputFilename,
                correctionMatrixOneBit);
    else if (mode == 'd' || mode == 'D')
        binaryFileEncoder.decode(inputFilename, outputFilename,
                correctionMatrixOneBit);

    // End of program
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
