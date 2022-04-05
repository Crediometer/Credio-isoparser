#include <iostream>
#include <string>
#include <map>
#include <vector>

#ifndef ISO8583PARSER_DATEELEMENTSCONFIG_H
#define ISO8583PARSER_DATEELEMENTSCONFIG_H

enum class FIELDFORMAT : char { LLVAR, LLLVAR, LLLLVAR, AN, NONE };
enum class CREDITORDEBIT : char {C, D, NONE};
enum class TRANSACTIONMODE : char { CREDIT, DEBIT};
enum class VARIABLETYPE : char {FIXED, VARIABLE};

class DataElementsConfig {
public:
    VARIABLETYPE lengthType;
    DataElementsConfig(size_t Id, std::string fieldName, size_t fieldLength, VARIABLETYPE len = VARIABLETYPE::FIXED, FIELDFORMAT fieldFormat = FIELDFORMAT::NONE,  CREDITORDEBIT x = CREDITORDEBIT::NONE );
    //DataElementsConfig(const DataElementsConfig& copySource);
    std::map<std::string, std::string> ProcessedData();
    std::string getFieldName();
    size_t getFieldId();
    size_t getFieldLength();




private:
    size_t FieldId;
    std::string FieldName;
    size_t FieldLength;
    FIELDFORMAT FieldFormat;
    CREDITORDEBIT X;
};

DataElementsConfig CheckXType(size_t currentVecIndex, std::string FieldName, long FieldLength, VARIABLETYPE len, FIELDFORMAT format = FIELDFORMAT::NONE, TRANSACTIONMODE transactionMode = TRANSACTIONMODE::DEBIT ); /** this checks and returns an DataElementsConfig with either credit (C) | debit (D) **/
DataElementsConfig InputFieldsFromHeader(size_t currentVecIndex, std::string FieldName, long FieldLength = 999, FIELDFORMAT format = FIELDFORMAT::NONE, TRANSACTIONMODE transactionMode = TRANSACTIONMODE::DEBIT );
std::string FIELDFORMATEnum2String(FIELDFORMAT text);
std::string CREDITORDEBITEnum2String (CREDITORDEBIT text);
std::string LENGTHEnum2String(VARIABLETYPE text);
#endif //ISO8583PARSER_DATEELEMENTSCONFIG_H
