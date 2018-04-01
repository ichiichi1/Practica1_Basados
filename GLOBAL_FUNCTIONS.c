/*
 * GLOBAL_FUNCTIONS.c
 *
 *  Created on: Mar 24, 2018
 *      Author: Lenovo
 */
#include <stdio.h>
#include "board.h"
#include "GLOBAL_FUNCTIONS.h"

uint16_t convertAdressASCII_Hexadecimal_4(uint8_t ASCII_4, uint8_t ASCII_3, uint8_t ASCII_2, uint8_t ASCII_1) {

	/**This local variable will store the end result*/
	uint16_t hexadecimal_Value = 0;

	/**The conversion of the fourth ASCII number is made. This number represents nibble 4 of the hexadecimal number
	 * wanted. Hence, the result is concatenated after being shifted to its appropriate place in the result*/
	if(ASCII_4 == 'F' || ASCII_4 == 'f') {
		hexadecimal_Value |= (0x0F) << 12;
	} else if(ASCII_4 == 'E' || ASCII_4 == 'e') {
		hexadecimal_Value |= (0x0E) << 12;
	} else if(ASCII_4 == 'D' || ASCII_4 == 'd') {
		hexadecimal_Value |= (0x0D) << 12;
	} else if(ASCII_4 == 'C' || ASCII_4 == 'c') {
		hexadecimal_Value |= (0x0C) << 12;
	} else if(ASCII_4 == 'B' || ASCII_4 == 'b') {
		hexadecimal_Value |= (0x0B) << 12;
	} else if(ASCII_4 == 'A' || ASCII_4 == 'a') {
		hexadecimal_Value |= (0x0A) << 12;
	} else {
		hexadecimal_Value |= (ASCII_4 - ASCII_OFFSET) << 12;
	}

	/**The conversion of the third ASCII number is made. This number represents nibble 3 of the hexadecimal number
	 * wanted. Hence, the result is concatenated after being shifted to its appropriate place in the result*/
	if(ASCII_3 == 'F' || ASCII_3 == 'f') {
		hexadecimal_Value |= (0x0F) << 8;
	} else if(ASCII_3 == 'E' || ASCII_3 == 'e') {
		hexadecimal_Value |= (0x0E) << 8;
	} else if(ASCII_3 == 'D' || ASCII_3 == 'd') {
		hexadecimal_Value |= (0x0D) << 8;
	} else if(ASCII_3 == 'C' || ASCII_3 == 'c') {
		hexadecimal_Value |= (0x0C) << 8;
	} else if(ASCII_3 == 'B' || ASCII_3 == 'b') {
		hexadecimal_Value |= (0x0B) << 8;
	} else if(ASCII_3 == 'A' || ASCII_3 == 'a') {
		hexadecimal_Value |= (0x0A) << 8;
	} else {
		hexadecimal_Value |= (ASCII_3 - ASCII_OFFSET) << 8;
	}

	/**The conversion of the second ASCII number is made. This number represents nibble 2 of the hexadecimal number
	 * wanted. Hence, the result is concatenated after being shifted to its appropriate place in the result*/
	if(ASCII_2 == 'F' || ASCII_2 == 'f') {
		hexadecimal_Value |= (0x0F) << 4;
	} else if(ASCII_2 == 'E' || ASCII_2 == 'e') {
		hexadecimal_Value |= (0x0E) << 4;
	} else if(ASCII_2 == 'D' || ASCII_2 == 'd') {
		hexadecimal_Value |= (0x0D) << 4;
	} else if(ASCII_2 == 'C' || ASCII_2 == 'c') {
		hexadecimal_Value |= (0x0C) << 4;
	} else if(ASCII_2 == 'B' || ASCII_2 == 'b') {
		hexadecimal_Value |= (0x0B) << 4;
	} else if(ASCII_2 == 'A' || ASCII_2 == 'a') {
		hexadecimal_Value |= (0x0A) << 4;
	} else {
		hexadecimal_Value |= (ASCII_2 - ASCII_OFFSET) << 4;
	}

	/**The conversion of the first ASCII number is made. This number represents nibble 1 of the hexadecimal number
	 * wanted. Hence, the result is concatenated after being shifted to its appropriate place in the result*/
	if(ASCII_1 == 'F' || ASCII_1 == 'f') {
		hexadecimal_Value |= (0x0F);
	} else if(ASCII_1 == 'E' || ASCII_1 == 'e') {
		hexadecimal_Value |= (0x0E);
	} else if(ASCII_1 == 'D' || ASCII_1 == 'd') {
		hexadecimal_Value |= (0x0D);
	} else if(ASCII_1 == 'C' || ASCII_1 == 'c') {
		hexadecimal_Value |= (0x0C);
	} else if(ASCII_1 == 'B' || ASCII_1 == 'b') {
		hexadecimal_Value |= (0x0B);
	} else if(ASCII_1 == 'A' || ASCII_1 == 'a') {
		hexadecimal_Value |= (0x0A);
	} else {
		hexadecimal_Value |= (ASCII_1 - ASCII_OFFSET);
	}

	/**Returning the value of the conversion*/
	return hexadecimal_Value;
}

uint8_t convertAdressASCII_Hexadecimal_2(uint8_t ASCII_2, uint8_t ASCII_1)
{
	/**This local variable will store the end result*/
		uint8_t hexadecimal_Value = 0;

		if(ASCII_2 == 'F' || ASCII_2 == 'f') {
				hexadecimal_Value |= (0x0F) << 4;
			} else if(ASCII_2 == 'E' || ASCII_2 == 'e') {
				hexadecimal_Value |= (0x0E) << 4;
			} else if(ASCII_2 == 'D' || ASCII_2 == 'd') {
				hexadecimal_Value |= (0x0D) << 4;
			} else if(ASCII_2 == 'C' || ASCII_2 == 'c') {
				hexadecimal_Value |= (0x0C) << 4;
			} else if(ASCII_2 == 'B' || ASCII_2 == 'b') {
				hexadecimal_Value |= (0x0B) << 4;
			} else if(ASCII_2 == 'A' || ASCII_2 == 'a') {
				hexadecimal_Value |= (0x0A) << 4;
			} else {
				hexadecimal_Value |= (ASCII_2 - ASCII_OFFSET) << 4;
			}

			/**The conversion of the first ASCII number is made. This number represents nibble 1 of the hexadecimal number
			 * wanted. Hence, the result is concatenated after being shifted to its appropriate place in the result*/
			if(ASCII_1 == 'F' || ASCII_1 == 'f') {
				hexadecimal_Value |= (0x0F);
			} else if(ASCII_1 == 'E' || ASCII_1 == 'e') {
				hexadecimal_Value |= (0x0E);
			} else if(ASCII_1 == 'D' || ASCII_1 == 'd') {
				hexadecimal_Value |= (0x0D);
			} else if(ASCII_1 == 'C' || ASCII_1 == 'c') {
				hexadecimal_Value |= (0x0C);
			} else if(ASCII_1 == 'B' || ASCII_1 == 'b') {
				hexadecimal_Value |= (0x0B);
			} else if(ASCII_1 == 'A' || ASCII_1 == 'a') {
				hexadecimal_Value |= (0x0A);
			} else {
				hexadecimal_Value |= (ASCII_1 - ASCII_OFFSET);
			}
			return hexadecimal_Value;
}

uint8_t convertAdressASCII_Hexadecimal_1( uint8_t ASCII_1)
{
	               uint8_t hexadecimal_Value = 0;

					   if(ASCII_1 == 'F' || ASCII_1 == 'f') {
					hexadecimal_Value |= (0x0F);
				} else if(ASCII_1 == 'E' || ASCII_1 == 'e') {
					hexadecimal_Value |= (0x0E);
				} else if(ASCII_1 == 'D' || ASCII_1 == 'd') {
					hexadecimal_Value |= (0x0D);
				} else if(ASCII_1 == 'C' || ASCII_1 == 'c') {
					hexadecimal_Value |= (0x0C);
				} else if(ASCII_1 == 'B' || ASCII_1 == 'b') {
					hexadecimal_Value |= (0x0B);
				} else if(ASCII_1 == 'A' || ASCII_1 == 'a') {
					hexadecimal_Value |= (0x0A);
				} else {
					hexadecimal_Value |= (ASCII_1 - ASCII_OFFSET);
				}
				return hexadecimal_Value;
}
