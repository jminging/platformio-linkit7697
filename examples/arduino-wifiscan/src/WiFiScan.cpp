#include "Arduino.h"
#include "LWiFi.h"

static void printEncryptionType(int thisType)
{
    // read the encryption type and print out the name:
    switch (thisType)
    {
    case ENC_TYPE_WEP:
        Serial.println("WEP");
        break;
    case ENC_TYPE_TKIP:
        Serial.println("WPA");
        break;
    case ENC_TYPE_NONE:
        Serial.println("None");
        break;
    case ENC_TYPE_CCMP:
        Serial.println("WPA2 (AES)");
        break;
    case ENC_TYPE_TKIP_AES:
        Serial.println("TKIP AES MIX");
        break;
    default:
        Serial.println("Unknown");
    }
}

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    int numSsid = WiFi.scanNetworks();
    if (numSsid == -1)
    {
        Serial.println("Couldn't get a wifi connection");
        while (true)
            ;
    }

    // print the list of networks seen:
    Serial.print("number of available networks:");
    Serial.println(numSsid);

    // print the network number and name for each network found:
    for (int thisNet = 0; thisNet < numSsid; thisNet++)
    {
        Serial.print(thisNet);
        Serial.print(") ");
        Serial.print(WiFi.SSID(thisNet));
        Serial.print("\tSignal: ");
        Serial.print(WiFi.RSSI(thisNet));
        Serial.print(" dBm");
        Serial.print("\tEncryption: ");
        int encr = WiFi.encryptionType(thisNet);
        printEncryptionType(encr);
    }

    Serial.println("");

    // Wait a bit before scanning again
    delay(5000);
}