#ifndef TELECOMMUNICATION_ONE_CORRECTIONMATR_HPP
#define TELECOMMUNICATION_ONE_CORRECTIONMATR_HPP
/////////////////////////////////////////////////////////////////////// Includes
#include <string>
#include <vector>

///////////////////////////////////////////////////////////// BinaryMatrix class
class CorrectionMatrix
{
public:
    /////////////////////////////////////////////////////// [ Public methods ] <
    //----------------------------------------------------------- Constructor <<
    CorrectionMatrix(int const &n, int const &m,
                     std::string const &stringMatrix);

    //--------------------------------------------------------------- Getters <<
    bool getBit(int const &n, int const &m) const;
    int getNumberOfRows() const;
    int getNumberOfColumns() const;
    int getNumberOfMessageBits() const;
    int getNumberOfParityBits() const;

private:
    ////////////////////////////////////////////////////// [ Private methods ] <
    //------------------------------------------------------ Helper functions <<
    std::vector<std::vector<bool>> convertStringToBinaryMatrix(
            int const &n, int const &m, std::string const &stringMatrix) const;

    /////////////////////////////////////////////////////// [ Private fields ] <
    //------------------------------------------------- Matrix representation <<
    std::vector<std::vector<bool>> const matrix;

};

////////////////////////////////////////////////////////////////////////////////
#endif /* TELECOMMUNICATION_ONE_CORRECTIONMATR_HPP */
