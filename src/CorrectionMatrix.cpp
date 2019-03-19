/////////////////////////////////////////////////////////////////////// Includes
#include "CorrectionMatrix.hpp"

////////////////////////////////////////////// BinaryMatrix class implementation
/////////////////////////////////////////////////////////// [ Public methods ] <
//--------------------------------------------------------------- Constructor <<
CorrectionMatrix::CorrectionMatrix(
        int const &n,
        int const &m,
        std::string const &stringMatrix)
    :
    matrix(convertStringToBinaryMatrix(n, m, stringMatrix))
{
}

//--------------------------------------------------------------- Getters <<
bool CorrectionMatrix::getBit(
        int const &n,
        int const &m) const
{
    return matrix[n][m];
}

int CorrectionMatrix::getNumberOfRows() const
{
    return matrix.size();
}

int CorrectionMatrix::getNumberOfColumns() const
{
    return matrix[0].size();
}

int CorrectionMatrix::getNumberOfMessageBits() const
{
    return getNumberOfColumns() - getNumberOfParityBits();
}

int CorrectionMatrix::getNumberOfParityBits() const
{
    return getNumberOfRows();
}

////////////////////////////////////////////////////////// [ Private methods ] <
//---------------------------------------------------------- Helper functions <<
std::vector<std::vector<bool>> CorrectionMatrix::convertStringToBinaryMatrix(
        int const &n,
        int const &m,
        std::string const &stringMatrix) const
{
    std::vector<std::vector<bool>> binaryMatrix;

    for (int i = 0; i < n; i++)
    {
        std::vector<bool> row;

        for (int j = 0; j < m; j++)
        {
            switch (stringMatrix.at(m * i + j))
            {
                case '0':
                    row.push_back(false);
                    break;
                case '1':
                    row.push_back(true);
                    break;
            }
        }

        binaryMatrix.push_back(row);
    }

    return binaryMatrix;
}

////////////////////////////////////////////////////////////////////////////////
