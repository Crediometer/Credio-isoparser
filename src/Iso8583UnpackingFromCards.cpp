#include "../headers/Iso8583UnpackingFromCards.h"
#include "./Isomessage.cpp"
#include "./data.cpp"
#include "../headers/utils.h"

#include <bitset>
#include <vector>
#include <map>

void Iso8583UnpackingFromCards(std::string text) {
    std::string mess{ text };
    Bitmap bitmap = Bitmap(mess);

    std::vector<short> DataElmFields {};
    std::vector<std::map<std::string, std::string>> elements {};

    /**We LOOP THROUGH THE WHOLE BINARY TO PICK THE INDEX OF THAT ARE AVAILABLE: ALWAYS REMEMEBER THAT THE FIRST INDEX (0) INDICATES WHETHER THERE IS A SECONDARY*/
    for(short i{0}; i < bitmap.getBitmapLength(); i++) {
        const std::string binary {bitmap.HEX2BINARYSTRING()};
        const char BinaryOnes{ '1' }; // this is the binary that have data-element in them
        if(binary.at(i) == BinaryOnes ) {
            DataElmFields.push_back(i);
        }
    }

    /** This is a for loop that loops through the vector of DataElements Config and check to see if the class Id match the element in a particular index,
    * if it does it pushes the map of that class to a vetor
    * (NOTE) Hence element in index 1 of the DataElmFields has its dataConfiguration in index 0 of the  dataElementsConfig vector
    **/
    for(short i{1}; i < DataElmFields.size(); i++) {
        short el { DataElmFields.at(i) }; // the element in vector DataElmFields
        /** TO REMEMBER THAT THE ARRAY CONTAINING THE DATA_ELEMENTS_CONFIG CLASS START WITH THE ID 2 WHICH IS INDEX 0 IN THE dataElementsConfig ARRAY , WHICH IS AT INDEX 1 IN THE DATA_ELM_FIELDS ARRAY */
        DataElementsConfig e = dataElementsConfig.at(el - 1);
        elements.push_back(e.ProcessedData());
    }


    short currentDataElementsIndex { bitmap.getDataElementStartingIndex() };

    //Opening the and Writing to the File
    bitmap.CreateAFile();
    dataElementEntry(currentDataElementsIndex, elements, bitmap.request_iso_message); // the function is from the utility file


}
