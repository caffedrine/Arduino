#include <WString.h>
#include <Arduino.h>

String to_string(int intNumber);
int to_int(String str);
int getNumberOfChars(String str, char checkCharacter);
String getStringPartByNr(String data, char separator, int index);
void printPeriodicData(String data, int interval);
