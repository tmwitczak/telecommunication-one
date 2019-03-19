/////////////////////////////////////////////////////////////////////// Includes
#include "BinaryFileEncoder.hpp"
#include "CorrectionMatrix.hpp"

#include <fstream>
#include <iostream>

/////////////////////////////////////////////////////////////////////// Typedefs
typedef unsigned char Byte;
typedef bool Bit;

/////////////////////////////////////////////////////////////// Helper functions
template<typename T>
std::vector<T> mergeVectors(
        std::vector<T> a,
        std::vector<T> b)
{
    std::vector<T> result;

    result.reserve(a.size() + b.size());
    result.insert(result.end(), a.begin(), a.end());
    result.insert(result.end(), b.begin(), b.end());

    return result;
}

///////////////////////////////////////// BinaryFileEncoder class implementation
/////////////////////////////////////////////////////////// [ Public methods ] <
//-------------------------------------------------------- Main functionality <<
void BinaryFileEncoder::encode(
        std::string const &inputFilename,
        std::string const &outputFilename,
        CorrectionMatrix const &correctionMatrix)
{
    std::vector<Byte> inputBytes = readBytes(inputFilename);
    std::vector<Byte> outputBytes;

    for (Byte const &byte : inputBytes)
    {
        std::vector<bool> messageBits = convertByteToBitVector(byte);
        std::vector<bool> parityBits(static_cast<unsigned int>(
                                             correctionMatrix.getNumberOfParityBits()),
                                     false);

        std::vector<bool> T = mergeVectors(messageBits, parityBits);
        parityBits = multiplyMatrixByVector(correctionMatrix, T);
        T = mergeVectors(messageBits, parityBits);

        auto outputByte = convertBitsToByteVector(T);
        outputBytes.insert(outputBytes.end(), outputByte.begin(),
                           outputByte.end());
    }

    writeBytes(outputBytes, outputFilename);
}

void BinaryFileEncoder::decode(
        std::string const &inputFilename,
        std::string const &outputFilename,
        CorrectionMatrix const &correctionMatrix)
{
    std::vector<Byte> inputBytes = readBytes(inputFilename);
    std::vector<Byte> outputBytes;

    for (int i = 0; i < inputBytes.size() / 2; i++)
    {
        std::vector<bool> T1 = convertByteToBitVector(inputBytes[2 * i]);
        std::vector<bool> T2 = convertByteToBitVector(inputBytes[2 * i + 1]);
        std::vector<bool> T = mergeVectors(T1, T2);
        T.erase(T.begin() + correctionMatrix.getNumberOfColumns(), T.end());

        std::vector<bool> correctionControl
                = multiplyMatrixByVector(correctionMatrix, T);

        if (int wrongBitPosition
                    = getPositionOfWrongBit(correctionControl,
                                            correctionMatrix);
                wrongBitPosition != -1)
        {
            if (wrongBitPosition < 8)
                T1[wrongBitPosition] = !T[wrongBitPosition];
        }

        auto outputByte = convertBitsToByteVector(T1);
        outputBytes.insert(outputBytes.end(), outputByte.begin(),
                           outputByte.end());
    }

    writeBytes(outputBytes, outputFilename);
}

////////////////////////////////////////////////////// [ Private methods ] <
//------------------------------------------------------ Helper functions <<
std::vector<bool> BinaryFileEncoder::multiplyMatrixByVector(
        CorrectionMatrix const &matrix,
        std::vector<bool> const &vector)
{
    std::vector<bool> result;

    for (int i = 0; i < matrix.getNumberOfRows(); i++)
    {
        bool rowResult = false;

        for (int j = 0; j < matrix.getNumberOfColumns(); j++)
            rowResult ^= (matrix.getBit(i, j) & vector[j]);

        result.push_back(rowResult);
    }

    return result;
}

std::vector<Byte> BinaryFileEncoder::readBytes(
        std::string const &filename)
{
    std::ifstream inputFile(filename, std::ios::binary);

    if (!inputFile)
        return std::vector<Byte>();

    return std::vector<Byte>(std::istreambuf_iterator<char>(inputFile), {});
}

void BinaryFileEncoder::writeBytes(
        std::vector<Byte> const &bytes,
        std::string const &filename)
{
    std::ofstream outputFile;
    outputFile.open(filename, std::ios::binary);

    for (Byte const &byte : bytes)
        outputFile.write((char *) &byte, sizeof(byte));

    outputFile.close();
}

std::vector<bool> BinaryFileEncoder::convertByteToBitVector(
        Byte const &byte)
{
    std::vector<Bit> bits;

    for (int i = 0; i < 8; i++)
        bits.push_back(static_cast<bool>(byte >> (8 - 1 - i) & 1));

    return bits;
}

std::vector<Byte> BinaryFileEncoder::convertBitsToByteVector(
        std::vector<bool> bits)
{
    std::vector<Byte> bytes(((bits.size() - 1) / 8) + 1, 0);
    bits.insert(bits.end(), bytes.size() * 8 - bits.size(), false);

    for (int i = 0; i < bytes.size(); i++)
        for (int j = 0; j < 8; j++)
            bytes[i] |= bits[8 * i + j] << (8 - 1 - j);

    return bytes;
}

int BinaryFileEncoder::getPositionOfWrongBit(
        std::vector<bool> const &correctionControl,
        CorrectionMatrix const &correctionMatrix)
{
    // Get columns as binary vectors
    std::vector<std::vector<bool>> columns;
    for (int i = 0; i < correctionMatrix.getNumberOfColumns(); i++)
    {
        std::vector<bool> column;
        for (int j = 0; j < correctionMatrix.getNumberOfRows(); j++)
            column.push_back(correctionMatrix.getBit(j, i));
        columns.push_back(column);
    }

    for (int i = 0; i < columns.size(); i++)
        if (std::equal(columns[i].begin(), columns[i].end(),
                       correctionControl.begin()))
            return i;

    return -1;
}

////////////////////////////////////////////////////////////////////////////////