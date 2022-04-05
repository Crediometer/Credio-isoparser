/** This Utility class contains the Conversion from HEX-DECIMAL to BINARY, and also returns the binary has strings
 *  Also we will be creating a function that runs through the whole data-elements configuration showing there FORMAT(LLLVAR || LL), MAXIMUM DIGITS
 * */
#include "../headers/utils.h"
#include <sstream>
#include <fstream>

std::string Hex2Binary(std::string hex_val) {
    using namespace std;
    string binaryVal{ "" };
    string* binaryPointer { &binaryVal };

    for (short i{ 0 }; i < hex_val.length(); i++) {
        switch (hex_val.at(i)) {
            case '0':
                binaryPointer->append("0000");
                break;
            case '1':
                binaryPointer->append("0001");
                break;
            case '2':
                binaryPointer->append("0010");
                break;
            case '3':
                binaryPointer->append("0011");
                break;
            case '4':
                binaryPointer->append("0100");
                break;
            case '5':
                binaryPointer->append("0101");
                break;
            case '6':
                binaryPointer->append("0110");
                break;
            case '7':
                binaryPointer->append("0111");
                break;
            case '8':
                binaryPointer->append("1000");
                break;
            case '9':
                binaryPointer->append("1001");
                break;
            case 'A':
            case 'a':
                binaryPointer->append("1010");
                break;
            case 'B':
            case 'b':
                binaryPointer->append("1011");
                break;
            case 'C':
            case 'c':
                binaryPointer->append("1100");
                break;
            case 'D':
            case 'd':
                binaryPointer->append("1101");
                break;
            case 'E':
            case 'e':
                binaryPointer->append("1110");
                break;
            case 'F':
            case 'f':
                binaryPointer->append("1111");
                break;
            default:
                throw invalid_argument("The Value inputted is not a hexdecimal");
        }
    }
    return binaryVal;
    
}

size_t String2Numbers(std::string t) {
    size_t ResultValue {0};
    std::stringstream converter;
    converter << t;
    converter >> ResultValue;
    return ResultValue;
}

/*std::vector<std::map<std::string, std::string>>*/ void dataElementEntry(short dataElmIndex, std::vector<std::map<std::string, std::string>> _elm, std::string isoMessage) {
    //std::vector<std::map<std::string, std::string>> v {};
    //std::map<std::string, std::string> v_map;

    for(short i {0}; i < 24; i++) {
        std::string FieldName { (_elm.at(i)).at("FieldName") };

        std::string FieldId { (_elm.at(i)).at("Id") };
        short FieldIdInt {(short)String2Numbers(FieldId)};

        short FieldLength { (short)String2Numbers((_elm.at(i)).at("FieldLength")) };
        std::string FieldFormat {(_elm.at(i)).at("FieldFormat")};
        std::string LengthType {(_elm.at(i)).at("LengthType")};

        std::string val {""};

        int totalSize {0};
        int* totalSizePointer {&totalSize};

        /** For data elements with fixed length  **/
        if(LengthType == "FIXED") {
            /** check for data-elements that take in a character and eight numeric **/
            if(FieldIdInt == 28 || FieldIdInt == 29 || FieldIdInt == 30 || FieldIdInt == 31) {
                FieldLength +=1;
            }
            totalSize = FieldLength + dataElmIndex;
        }


        /** if the data-type has a variable configuration, then the rule is that:
         * This has a variable length up to a maximum of 17 characters. Additionally all variable length fields contain one or two bytes at the beginning of the field to identify the number of positions to follow
        * **/
        if(LengthType == "VARIABLE") {
            std::string VariableDataLength {""}; // for data that are variable
            short p = dataElmIndex + 2;

            /** The only variable that objects this, is the one on ID 62*/
            if(FieldIdInt == 62) {
                p = dataElmIndex + 3;
            }

            for(dataElmIndex; dataElmIndex < p; dataElmIndex++ ) {
                VariableDataLength.push_back(isoMessage.at(dataElmIndex));
            }
            //std::cout << "Variable length " << VariableDataLength.size() << std::endl;
            FieldLength = (int)String2Numbers(VariableDataLength);
            //std::cout << " variable size " << *totalSizePointer  << " data index " << dataElmIndex << std::endl;
            totalSize = FieldLength + dataElmIndex;
        }

        while (dataElmIndex < *totalSizePointer) {
            val.push_back(isoMessage.at(dataElmIndex));
            dataElmIndex ++;
        }

        std::fstream File;
        File.open("Iso8583.txt", std::ios_base::app);
        if(File.is_open()) {
            File << FieldId << ":" << FieldName << " > " << val << std::endl;
            File.close();
        }
        val.clear();
    }

}



