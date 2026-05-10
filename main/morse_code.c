/*
 * MIT License
 *
 * Copyright (c) 2026 Robin Kraußer
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */



#include <stdio.h>
#include <ctype.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>

#define USE_LED true
#define LED_PIN 2
#define USE_BUZZER false
#define BUZZER_PIN 4
#define TIME_LENGTH 400

typedef struct {
	char symbol;
	char* morse_code;
} symbol;

void dot() {
	if (USE_LED == true) {
		gpio_set_level(LED_PIN, 1);
	}
	if (USE_BUZZER == true) {
		gpio_set_level(BUZZER_PIN, 1);
	}

	vTaskDelay((1 * TIME_LENGTH) / portTICK_PERIOD_MS);
	
	if (USE_LED == true) {
		gpio_set_level(LED_PIN, 0);
	}
	if (USE_BUZZER == true) {
		gpio_set_level(BUZZER_PIN, 0);
	}
}


void dash() {
	if (USE_LED == true) {
		gpio_set_level(LED_PIN, 1);
	}
	if (USE_BUZZER == true) {
		gpio_set_level(BUZZER_PIN, 1);
	}

	vTaskDelay((3 * TIME_LENGTH) / portTICK_PERIOD_MS);
	
	if (USE_LED == true) {
		gpio_set_level(LED_PIN, 0);
	}
	if (USE_BUZZER == true) {
		gpio_set_level(BUZZER_PIN, 0);
	}
}

void execute_morse_code(const char* morse_code) {
	for (int i = 0; morse_code[i] != '\0'; i++) {
		char c = morse_code[i];
		switch (c) {
			case '.':
				printf(".\n");
				dot();
				break;
			case '-':
				printf("-\n");
				dash();
				break;
		}
		vTaskDelay((1 * TIME_LENGTH) / portTICK_PERIOD_MS);
	}
	vTaskDelay((2 * TIME_LENGTH) / portTICK_PERIOD_MS);
}

void decode_symbol(symbol* symbols, char wanted_symbol, int count) {
	for (int i = 0; i < count; i++) {
		char current_symbol = symbols[i].symbol;
		char* current_morse_code = symbols[i].morse_code;

		if (current_symbol == tolower(wanted_symbol)) {
			execute_morse_code(current_morse_code);
		}
	}
}

void decode_string(char* string, symbol* symbols, int count) {
	for (int i = 0; string[i] != '\0'; i++) {
		if (string[i] == ' ') {
			printf("\n\n\n");
			vTaskDelay((4 * TIME_LENGTH) / portTICK_PERIOD_MS);
		} else {
			printf("\n%c\n", string[i]);
			decode_symbol(symbols, string[i], count);
		}
	}
}

void morse_code(char* string) {
	int symbol_count = 50;
	symbol* symbols = malloc(symbol_count * sizeof(symbol));

	if (symbols != NULL) {
    		// Lowercase letters a-z
    		symbols[0].symbol = 'a';
    		symbols[0].morse_code = ".-";
    		symbols[1].symbol = 'b';
    		symbols[1].morse_code = "-...";
    		symbols[2].symbol = 'c';
    		symbols[2].morse_code = "-.-.";
    		symbols[3].symbol = 'd';
    		symbols[3].morse_code = "-..";
    		symbols[4].symbol = 'e';
    		symbols[4].morse_code = ".";
    		symbols[5].symbol = 'f';
    		symbols[5].morse_code = "..-.";
    		symbols[6].symbol = 'g';
    		symbols[6].morse_code = "--.";
    		symbols[7].symbol = 'h';
    		symbols[7].morse_code = "....";
    		symbols[8].symbol = 'i';
    		symbols[8].morse_code = "..";
    		symbols[9].symbol = 'j';
    		symbols[9].morse_code = ".---";
    		symbols[10].symbol = 'k';
    		symbols[10].morse_code = "-.-";
    		symbols[11].symbol = 'l';
    		symbols[11].morse_code = ".-..";
    		symbols[12].symbol = 'm';
    		symbols[12].morse_code = "--";
    		symbols[13].symbol = 'n';
    		symbols[13].morse_code = "-.";
    		symbols[14].symbol = 'o';
    		symbols[14].morse_code = "---";
    		symbols[15].symbol = 'p';
    		symbols[15].morse_code = ".--.";
    		symbols[16].symbol = 'q';
    		symbols[16].morse_code = "--.-";
    		symbols[17].symbol = 'r';
    		symbols[17].morse_code = ".-.";
    		symbols[18].symbol = 's';
    		symbols[18].morse_code = "...";
    		symbols[19].symbol = 't';
    		symbols[19].morse_code = "-";
    		symbols[20].symbol = 'u';
    		symbols[20].morse_code = "..-";
    		symbols[21].symbol = 'v';
    		symbols[21].morse_code = "...-";
    		symbols[22].symbol = 'w';
    		symbols[22].morse_code = ".--";
    		symbols[23].symbol = 'x';
    		symbols[23].morse_code = "-..-";
    		symbols[24].symbol = 'y';
    		symbols[24].morse_code = "-.--";
    		symbols[25].symbol = 'z';
    		symbols[25].morse_code = "--..";

    		// Digits 0-9
    		symbols[26].symbol = '0';
    		symbols[26].morse_code = "-----";
    		symbols[27].symbol = '1';
    		symbols[27].morse_code = ".----";
    		symbols[28].symbol = '2';
    		symbols[28].morse_code = "..---";
    		symbols[29].symbol = '3';
    		symbols[29].morse_code = "...--";
    		symbols[30].symbol = '4';
    		symbols[30].morse_code = "....-";
    		symbols[31].symbol = '5';
    		symbols[31].morse_code = ".....";
    		symbols[32].symbol = '6';
    		symbols[32].morse_code = "-....";
    		symbols[33].symbol = '7';
    		symbols[33].morse_code = "--...";
    		symbols[34].symbol = '8';
    		symbols[34].morse_code = "---..";
    		symbols[35].symbol = '9';
    		symbols[35].morse_code = "----.";

    		// Symbols
    		symbols[36].symbol = '.';
    		symbols[36].morse_code = ".-.-.-";
    		symbols[37].symbol = ',';
    		symbols[37].morse_code = "--..--";
    		symbols[38].symbol = '?';
    		symbols[38].morse_code = "..--..";
    		symbols[39].symbol = '\'';
    		symbols[39].morse_code = ".----.";
    		symbols[40].symbol = '!';
    		symbols[40].morse_code = "-.-.--";
    		symbols[41].symbol = '/';
    		symbols[41].morse_code = "-..-.";
    		symbols[42].symbol = '(';
    		symbols[42].morse_code = "-.--.";
    		symbols[43].symbol = ')';
    		symbols[43].morse_code = "-.--.-";
    		symbols[44].symbol = '&';
    		symbols[44].morse_code = ".-...";
    		symbols[45].symbol = ':';
    		symbols[45].morse_code = "---...";
    		symbols[46].symbol = '=';
    		symbols[46].morse_code = "-...-";
    		symbols[47].symbol = '+';
    		symbols[47].morse_code = ".-.-.";
    		symbols[48].symbol = '-';
    		symbols[48].morse_code = "-....-";
    		symbols[49].symbol = '"';
            	symbols[49].morse_code = ".-..-.";
    		symbols[50].symbol = '@';
    		symbols[50].morse_code = ".--.-.";
	}

	decode_string(string, symbols, symbol_count);

	free(symbols);
}

void app_main(void)
{
	gpio_reset_pin(LED_PIN);
	gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
	gpio_reset_pin(BUZZER_PIN);
	gpio_set_direction(BUZZER_PIN, GPIO_MODE_OUTPUT);

	while(true) {
		morse_code("Hello world!");
		putchar('\n');
		for (int i = 0; i < 10; i++) {
			printf("ESP32 wil restart in %i seconds.\n", (10 - i));
			vTaskDelay((1000) / portTICK_PERIOD_MS);
		}
	}
}
