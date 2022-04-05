/* CONTAINS BOTH THE ISOMESSAGE AND BITMAPS CLASS*/

#include "../headers/utils.h"

#include <iostream>
#include <string>
#include <cstddef>
#include <fstream>

enum class BitmapType : char { Binary, Hex }; //the bitmap type 
const static short start_index_bitmap { 4 };

class Isomessage {
public:
	std::string request_iso_message;

	explicit Isomessage(std::string message) : request_iso_message(message) {};

    long long Get_MTI_Value_Type() {
        size_t MTI_NUMERIC_TYPE_VALUE{  };
        std::string mti_value_string{ this->Set_MTI_Type() };
        this->MTI_VALUE_IN_STRING = mti_value_string; // setting the private variable to the MTI_TYPE in string
        std::stringstream String2IntergerConverter;
        String2IntergerConverter << mti_value_string;
        String2IntergerConverter >> MTI_NUMERIC_TYPE_VALUE;
        return MTI_NUMERIC_TYPE_VALUE;
    }

    std::string get() {
        return this->MTI_VALUE_IN_STRING;
    }


    std::fstream CreateAFile() {
        std::fstream File;
        std::string mti = "MTI";
        File.open("Iso8583.txt", std::ios_base::out);
        if(File.is_open()) {
            File << mti << ":" << this->Get_MTI_Value_Type() << std::endl;
            File.close();
        }
        return File;
    }

private:
    std::string Set_MTI_Type() {
        std::string mti_value{""};
        for(short i{ 0 }; i < start_index_bitmap; i++) {
            mti_value.push_back(request_iso_message.at(i));
        }
        return mti_value;
    }

    std::string MTI_VALUE_IN_STRING;

};


/** bitmap class, which inherits the isomessage class, containing the MTI-TYPE and also the bitmaps **/
class Bitmap : public Isomessage {
    /** get the length of the bitmap to know if its a 64bits or a 128 bits **/
public:
    Bitmap(std::string message, BitmapType binBitmap = BitmapType::Hex) : Isomessage(message), _bitmapType(binBitmap), IsSecondaryBitmap(true) {
        if (this->_bitmapType == BitmapType::Hex) {
            for (short i{ 4 }; i < (4 + 32); i++) {
                this->bitmapMessage.push_back(this->request_iso_message.at(i));
            }
        }
        else {
            // when the bitmap is binary i.e BitmapType::Binary
          for(short i{4}; i < (4 + 128); i++) {
              this->bitmapMessage.push_back(this->request_iso_message.at(i));
          }
        }
    }

    /** to Convert the Hexdecimal value to Binary **/
    std::string HEX2BINARYSTRING() {
        this->binaryBitmaps =  Hex2Binary(this->bitmapMessage);
        //std::cout << "The binary size is " << this->bitmapMessage.size()  << " : " << this->binaryBitmaps.size() << std::endl;
        return this->binaryBitmaps;
    }

    /** to confirm if there is a secondary bitmap in the iso_request **/
    bool CheckSecondaryBitmap() {
        if (!this->binaryBitmaps.at(0) == 1) {
            this->IsSecondaryBitmap = false;
            return false;
        }
       return true;
    }

    /** getting the bitmap length **/
    short getBitmapLength() {
        if(this->IsSecondaryBitmap == true)  {
            return 64 * 2;
        }
        else {
            return 64;
        }
    }

    /****/
    std::string getBitmapBinary() const {
        return this->binaryBitmaps;
    }

    /***/
    short getDataElementStartingIndex() {
        if(this->IsSecondaryBitmap) {
            return 36; //main concept
        } else {
            return 20;
        }
    }

    /****/
    std::string getBitmapMessage() const {
        return this->bitmapMessage;
    }

    /** when the bitmaps only contains a primary bitmaps, it will reconstruct the bitmapMessage **/
    void SetForOnlyPrimaryBitmap() {
        this->bitmapMessage.clear(); // to be sure there is nothing in it
        if (this->_bitmapType == BitmapType::Hex) {
            for (short i{ 4 }; i < (4 + 32); i++) {
                this->bitmapMessage.push_back(this->request_iso_message.at(i));
            }
        }
        else  if(this->_bitmapType == BitmapType::Binary) {
            // when the bitmap is binary i.e BitmapType::Binary
            for(short i{4}; i < (4 + 128); i++) {
                this->bitmapMessage.push_back(this->request_iso_message.at(i));
            }
        }
    }

private:
    bool IsSecondaryBitmap; // expect that there should be a secondary bitmaps on initialization
    BitmapType _bitmapType;
    std::string bitmapMessage;
    std::string binaryBitmaps;
};

