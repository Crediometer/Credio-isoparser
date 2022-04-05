/** Implementation of the DataConfiguration Class **/
#include "../headers/DataElementsConfig.h"
#include <sstream>
#include <vector>


DataElementsConfig::DataElementsConfig(size_t Id, std::string fieldName, size_t fieldLength, VARIABLETYPE len, FIELDFORMAT fieldFormat, CREDITORDEBIT x)  :  FieldId(Id), FieldName(fieldName), FieldLength(fieldLength), lengthType(len), FieldFormat(fieldFormat), X(x) {
    //std::cout << this->FieldId << " " << this->FieldName << " " << this->FieldLength << std::endl;
};

std::map<std::string, std::string> DataElementsConfig::ProcessedData() {
    std::map<std::string, std::string> dataProcessed {};
    std::string FieldLengthInString { std::to_string(this->FieldLength) };
    std::string FieldIdInString { std::to_string(this->FieldId)};
    dataProcessed.insert(std::make_pair("Id", FieldIdInString));
    dataProcessed.insert(std::make_pair("FieldLength", FieldLengthInString));
    dataProcessed.insert(std::make_pair("FieldName", this->FieldName));
    dataProcessed.insert(std::make_pair("FieldFormat", FIELDFORMATEnum2String(this->FieldFormat)));
    dataProcessed.insert(std::make_pair("TranFormat", CREDITORDEBITEnum2String(this->X)));
    dataProcessed.insert(std::make_pair("LengthType", LENGTHEnum2String(this->lengthType)));
    return dataProcessed;
};

std::string DataElementsConfig::getFieldName() {
    return this->FieldName;
};
size_t  DataElementsConfig::getFieldId() {
    return this->FieldId;
}
size_t DataElementsConfig::getFieldLength() {
    return this->FieldLength;
}

std::string FIELDFORMATEnum2String(FIELDFORMAT text) {
    std::string result {""};
    switch (text) {
        case FIELDFORMAT::LLVAR:
            result = "LLVAR";
            break;
        case FIELDFORMAT::LLLVAR:
            result = "LLLVAR";
            break;
        case FIELDFORMAT::LLLLVAR:
            result = "LLLLVAR";
            break;
        case FIELDFORMAT::AN:
            result = "AN";
            break;
        case FIELDFORMAT::NONE:
            result = "NONE";
            break;
    }
    return result;
};

std::string CREDITORDEBITEnum2String(CREDITORDEBIT text) {
    std::string result {""};
    switch (text) {
        case CREDITORDEBIT::NONE:
            result = "NONE";
            break;
        case CREDITORDEBIT::C:
            result = "C";
            break;
        case CREDITORDEBIT::D:
            result = "D";
            break;
    };

    return result;
}

std::string LENGTHEnum2String(VARIABLETYPE text) {
    std::string result {""};
    switch (text) {
        case VARIABLETYPE::VARIABLE:
            result = "VARIABLE";
            break;
        case VARIABLETYPE::FIXED:
            result = "FIXED";
            break;
    };
    return result;
};


DataElementsConfig CheckXType(size_t currentVecIndex, std::string FieldName, long FieldLength, VARIABLETYPE len, FIELDFORMAT format, TRANSACTIONMODE transactionMode) {
    /** How to determine the X type, whether its a credit or debit, hence we will collect it from the entry **/
    CREDITORDEBIT x;

    if(transactionMode == TRANSACTIONMODE::DEBIT) {
         x  = CREDITORDEBIT::D;
    }
    else if(transactionMode == TRANSACTIONMODE::CREDIT) {
         x  = CREDITORDEBIT::C;
    } else {
        x  = CREDITORDEBIT::NONE;
    }
    return DataElementsConfig(currentVecIndex, FieldName, FieldLength, len, format, x);
};


DataElementsConfig InputFieldsFromHeader(size_t currentVecIndex, std::string FieldName, long FieldLength, VARIABLETYPE len, FIELDFORMAT format, TRANSACTIONMODE transactionMode) {
    /** How to determine the X type, whether its a credit or debit, hence we will collect it from the entry **/
    CREDITORDEBIT x;

    if(transactionMode == TRANSACTIONMODE::DEBIT) {
        x  = CREDITORDEBIT::D;
    }
    else if(transactionMode == TRANSACTIONMODE::CREDIT) {
        x  = CREDITORDEBIT::C;
    } else {
        x  = CREDITORDEBIT::NONE;
    }

    return DataElementsConfig(currentVecIndex, FieldName, FieldLength, len, format, x);
}

