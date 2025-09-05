// --- Timings (unchanged) ---
const int DOT = 200;
const int DASH = DOT * 3;
const int GAP_INTRA = DOT;
const int GAP_LETTER = DOT * 3;
const int GAP_WORD = DOT * 7;

// --- External bi-color LED on D5 (leg A) and D6 (leg B) ---
// Wire each leg through 220Ω. Middle pin = 3V if common anode, GND if common cathode.
const int LED_A = 10;           // e.g., red
const int LED_B = 11;           // e.g., green
const bool COMMON_ANODE = true; // set false if yours is common cathode

inline void colorWrite(int pin, bool on) {
    // sink for common anode, source for common cathode
    digitalWrite(pin, COMMON_ANODE ? !on : on);
}

inline void bothOff() {
    colorWrite(LED_A, false);
    colorWrite(LED_B, false);
}

inline void ledOn(int ms, bool dash) {
    // choose color: dot→A, dash→B (change if you want)
    int pin = dash ? LED_B : LED_A;
    colorWrite(pin, true);
    delay(ms);
    colorWrite(pin, false);
}

// Print each symbol as we blink it
void symbol(char s) {
    if (s == '.') {
        Serial.print('.');
        ledOn(DOT, false);
    } else {
        Serial.print('-');
        ledOn(DASH, true);
    }
}

void letter(const char *pat) {
    for (int i = 0; pat[i]; ++i) {
        symbol(pat[i]);
        if (pat[i + 1])
            delay(GAP_INTRA);
    }
}

void sendChar(char c) {
    switch (toupper(c)) {
    case 'A':
        letter(".-");
        break;
    case 'B':
        letter("-...");
        break;
    case 'C':
        letter("-.-.");
        break;
    case 'D':
        letter("-..");
        break;
    case 'E':
        letter(".");
        break;
    case 'F':
        letter("..-.");
        break;
    case 'G':
        letter("--.");
        break;
    case 'H':
        letter("....");
        break;
    case 'I':
        letter("..");
        break;
    case 'J':
        letter(".---");
        break;
    case 'K':
        letter("-.-");
        break;
    case 'L':
        letter(".-..");
        break;
    case 'M':
        letter("--");
        break;
    case 'N':
        letter("-.");
        break;
    case 'O':
        letter("---");
        break;
    case 'P':
        letter(".--.");
        break;
    case 'Q':
        letter("--.-");
        break;
    case 'R':
        letter(".-.");
        break;
    case 'S':
        letter("...");
        break;
    case 'T':
        letter("-");
        break;
    case 'U':
        letter("..-");
        break;
    case 'V':
        letter("...-");
        break;
    case 'W':
        letter(".--");
        break;
    case 'X':
        letter("-..-");
        break;
    case 'Y':
        letter("-.--");
        break;
    case 'Z':
        letter("--..");
        break;
    case '1':
        letter(".----");
        break;
    case '2':
        letter("..---");
        break;
    case '3':
        letter("...--");
        break;
    case '4':
        letter("....-");
        break;
    case '5':
        letter(".....");
        break;
    case '6':
        letter("-....");
        break;
    case '7':
        letter("--...");
        break;
    case '8':
        letter("---..");
        break;
    case '9':
        letter("----.");
        break;
    case '0':
        letter("-----");
        break;
    case ' ':
        Serial.print(" / "); // word separator in monitor
        delay(GAP_WORD);
        return;
    default:
        return;
    }
    Serial.print(' '); // letter separator in monitor
    delay(GAP_LETTER);
}

void morse(const char *msg) {
    for (int i = 0; msg[i]; ++i)
        sendChar(msg[i]);
    Serial.println();
}

void setup() {
    pinMode(LED_A, OUTPUT);
    pinMode(LED_B, OUTPUT);
    bothOff();

    Serial.begin(115200);
    unsigned long t0 = millis();
    while (!Serial && millis() - t0 < 2000) {
    }

    // heartbeat on LED_A so you know wiring works
    for (int i = 0; i < 3; i++) {
        colorWrite(LED_A, true);
        delay(120);
        colorWrite(LED_A, false);
        delay(120);
    }
}

void loop() {
    morse("HELLO WORLD");
    delay(2000);
}
