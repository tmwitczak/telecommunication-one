#ifndef TELECOMMUNICATION_ONE_BINARYFILEENCODER_HPP
#define TELECOMMUNICATION_ONE_BINARYFILEENCODER_HPP
/////////////////////////////////////////////////////////////////////// Includes
#include <vector>

/////////////////////////////////////////////////////////// Forward declarations
class CorrectionMatrix;

//////////////////////////////////////////////////////// BinaryFileEncoder class
class BinaryFileEncoder
{
public:
    /////////////////////////////////////////////////////// [ Public methods ] <
    //---------------------------------------------------- Main functionality <<
    void encode(std::string const &inputFilename,
                std::string const &outputFilename,
                CorrectionMatrix const &correctionMatrix);

    void decode(std::string const &inputFilename,
                std::string const &outputFilename,
                CorrectionMatrix const &correctionMatrix);

private:
    ////////////////////////////////////////////////////// [ Private methods ] <
    //------------------------------------------------------ Helper functions <<
    std::vector<bool> multiplyMatrixByVector(CorrectionMatrix const &matrix,
            std::vector<bool> const &vector);
    std::vector<unsigned char> readBytes(std::string const &filename);
    void BinaryFileEncoder::writeBytes(std::vector<unsigned char> const &bytes,
                                       std::string const &filename);
    std::vector<bool> convertByteToBitVector(unsigned char const &bytes);
    std::vector<unsigned char> convertBitsToByteVector(std::vector<bool> bits);
    int getPositionOfWrongBit(std::vector<bool> const &T,
            CorrectionMatrix const &correctionMatrix);
};

////////////////////////////////////////////////////////////////////////////////
#endif /* TELECOMMUNICATION_ONE_BINARYFILEENCODER_HPP */
