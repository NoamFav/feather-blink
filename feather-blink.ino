// --- timing (unchanged) ---
const int DOT = 200;
const int DASH = DOT * 3;
const int GAP_INTRA = DOT;      // between symbols of same letter
const int GAP_LETTER = DOT * 3; // between letters
const int GAP_WORD = DOT * 7;   // between words

inline void ledOn(int ms) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(ms);
    digitalWrite(LED_BUILTIN, LOW);
}

// Print each symbol as we blink it
void symbol(char s) {
    if (s == '.') {
        Serial.print('.');
        ledOn(DOT);
    } else {
        Serial.print('-');
        ledOn(DASH);
    }
}

void letter(const char *pat) {
    for (int i = 0; pat[i]; ++i) {
        symbol(pat[i]);
        if (pat[i + 1])
            delay(GAP_INTRA); // only between symbols
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
    Serial.println(); // newline after each message
}

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(115200);
    // Feather M0: wait briefly so the monitor attaches without hanging forever
    unsigned long t0 = millis();
    while (!Serial && millis() - t0 < 2000) { /* wait up to ~2s */
    }

    // heartbeat
    for (int i = 0; i < 3; i++) {
        ledOn(120);
        delay(120);
    }
}

void loop() {
    morse("HELLO WORLD");
    delay(2000);
}
