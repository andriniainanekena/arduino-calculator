#include <LiquidCrystal.h>
#include <Keypad.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
    {'1', '2', '3', '/'},
    {'4', '5', '6', '*'},
    {'7', '8', '9', '-'},
    {'C', '0', '=', '+'}
};

byte rowPins[ROWS] = {7, 6, 5, 4};
byte colPins[COLS] = {3, 2, 1, 0};

Keypad keypad = Keypad(
    makeKeymap(keys),
    rowPins,
    colPins,
    ROWS,
    COLS
);

long firstNumber = 0;
long secondNumber = 0;
double result = 0;

char operation = '\0';
char key;
bool enteringSecondNumber = false;

void setup() {
    lcd.begin(16, 2);

    lcd.setCursor(2, 0);
    lcd.print("Pika pika :D!");

    delay(2000);
    lcd.clear();
}

void loop() {
    key = keypad.getKey();

    if (key == NO_KEY) {
        return;
    }

    if (key >= '0' && key <= '9') {
        if (enteringSecondNumber) {
            secondNumber = secondNumber * 10 + (key - '0');
        } else {
            firstNumber = firstNumber * 10 + (key - '0');
        }

        lcd.setCursor(0, 0);
        lcd.print(firstNumber);
        
        if (operation != '\0') {
            lcd.print(operation);
            lcd.print(secondNumber);
        }
    }

    else if (key == '+' || key == '-' ||
             key == '*' || key == '/') {
        operation = key;
        enteringSecondNumber = true;

        lcd.setCursor(0, 0);
        lcd.print(firstNumber);
        lcd.print(operation);
    }

    else if (key == '=') {
        if (operation == '+') {
            result = firstNumber + secondNumber;
        } else if (operation == '-') {
            result = firstNumber - secondNumber;
        } else if (operation == '*') {
            result = firstNumber * secondNumber;
        } else if (operation == '/') {
            if (secondNumber == 0) {
                lcd.setCursor(0, 1);
                lcd.print("Division error");
                return;
            }

            result = (double) firstNumber / secondNumber;
        } else {
            return;
        }

        lcd.setCursor(0, 1);
        lcd.print("= ");
        lcd.print(result);
    }

    else if (key == 'C') {
        firstNumber = 0;
        secondNumber = 0;
        result = 0;
        operation = '\0';
        enteringSecondNumber = false;

        lcd.clear();
    }
}
