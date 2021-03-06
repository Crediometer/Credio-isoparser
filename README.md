# ISO8583PARSER
 
ISOMESSAGE RULES
* To provide a more consistent presentation, there is a set of rules that govern the use of data descriptions.
Unless otherwise stated, the following rules are in effect for this entire specification:
* You must send numeric fields compressed (4 bit BCD - packed unsigned). In this case, you must
utilize a communication protocol that supports transparency.
* If the data in a fixed-length numeric field does not fully populate the field, you should right justify and
zero fill the data.
** If the data in a fixed-length non-numeric field does not fully populate the field, you should left justify
and blank fill the data.
* Odd length numeric values should contain a leading zero.
* Worldpay assumes that you left justify with trailing zeros all fixed-length binary data elements.
* Worldpay counts all data element positions from left to right; it considers the leftmost position position
* The primary bit map indicates the presence of fields 1-64. The secondary bit map indicates the
presence of fields 65-128.
* This specification uses a fixed set of abbreviations. See Table 1-1 for these abbreviated values and
their corresponding descriptions.
* The maximum length of an LLd-type variable length field is 128 bytes (255 hex digits). The maximum
length of an LLb-type variable length field is 255 bytes. The maximum length of an LLL-type variable
length field is 999 bytes. The maximum length of an LLLL-type variable length field is 9,999 bytes.
* For LLbVAR and LLdVAR fields, the LL (length) value is a one-byte binary field. For LLLVAR fields,
the LLL (length) value is a two-byte binary field. For LLLLVAR fields, the LLLL (length) value is a
two-byte binary field. The length value indicates the length of the data only.
* For LLdVAR fields, the length value indicates the number of digits (nibbles) of data; whereas, the
LLbVAR, LLLVAR and LLLLVAR fields indicate the number of bytes of data.


