/////////////////////////////////////////////////////////////////////// Includes
#include <fstream>
#include <iostream>
#include <vector>

///////////////////////////////////////////////////////////////////// Namespaces
using namespace std;

/////////////////////////////////////////////////////////////////////// Typedefs
typedef std::vector<bool> BinaryVector;
typedef std::vector<std::vector<bool>> BinaryMatrix;
typedef std::vector<unsigned char> ByteVector;

////////////////////////////////////////////////////////////////////// Functions
inline BinaryVector convertByteToBinaryVector(unsigned char b) {
    BinaryVector vector;
    for (int i = 0; i < 8; i++) {
        vector.push_back(b & (1 << (7 - i)));
    }
    return vector;
}

BinaryVector multiplyMatrixByVector(const BinaryMatrix &matrix,
                                    const BinaryVector &vector) {
    BinaryVector result;
    for (BinaryVector row : matrix) {
        bool rowResult = 0;
        for (int i = 0; i < row.size(); i++) {
            rowResult = rowResult ^ (row[i] & vector[i]);
        }
        result.push_back(rowResult);
    }
    return result;
}

BinaryVector codeWord(const BinaryVector &word, const BinaryMatrix &matrix) {
    int numberOfParityBits = matrix.size();
    BinaryVector encoded(word);
    encoded.insert(encoded.end(), numberOfParityBits, 0);
    BinaryVector parityBits = multiplyMatrixByVector(matrix, encoded);
    encoded.erase(encoded.end() - numberOfParityBits, encoded.end());
    encoded.insert(encoded.end(), parityBits.begin(), parityBits.end());
    return encoded;
}

ByteVector codeBytes(const ByteVector &bytes, const BinaryMatrix &matrix) {
    //output vectors
    ByteVector outputInBytes;
    BinaryVector outputInBits;
    //code bytes to outputInBits
    for (unsigned char b : bytes) {
        BinaryVector encoded = codeWord(convertByteToBinaryVector(b), matrix);
        outputInBits.insert(outputInBits.end(), encoded.begin(), encoded.end());
    }
    //convert outputInBits to outputInBytes
    int counter = 0;
    unsigned char buffer = 0;
    for (bool b : outputInBits) {
        buffer += b;
        if (counter == 7) {
            outputInBytes.push_back(buffer);
            buffer = 0;
        }
        counter = (counter + 1) % 8;
        buffer <<= 1;
    }
    if (counter != 0) {
        buffer <<= 7 - counter;            //filling with zeros
        outputInBytes.push_back(buffer);
    }
    return outputInBytes;
}

/////////////////////////////////////////////////////////////////////////// Main
int main() {

    vector<std::vector<bool>> H1 =
            {
                    {1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0},
                    {1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
                    {1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0},
                    {0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1}
            };

    string filename = "";
    cout << "Enter filename of the file to encode: ";
    cin >> filename;
    ifstream file(filename, ios::binary);
    vector<unsigned char> bytes;
    if (!file) {
        cout << "Wrong file" << endl;
        return 0;
    } else {
        while (file) {
            auto b = static_cast<unsigned char>( file.get());
            if (file)
                bytes.push_back(b);
        }
    }

    vector<unsigned char> encoded = codeBytes(bytes, H1);
    string encodedFilename = "encoded-" + filename;
    ofstream os(encodedFilename, ios::binary);
    for (unsigned char b : encoded) {
        os.put(b);
        cout << b;
    }
    os.close();

    file.close();
}

////////////////////////////////////////////////////////////////////////////////
