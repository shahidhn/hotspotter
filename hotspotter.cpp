using namespace std;

WiFiAccessPoint aps[40];

String initList;
String chosen;
String targetName;
String locateOutput;

int idx;

void setup() {
    Serial.begin(9600);
    
    Particle.variable("initList", &initList, STRING);
    Particle.variable("chosen", &chosen, STRING);
    Particle.variable("locateOutput", &locateOutput, STRING);
    
    Particle.function("initScan", initScan);
    Particle.function("choose", choose);
    Particle.function("locating", locating);
}

void loop() {

    
}

int initScan(String command){
    initList = "";

    int found = WiFi.scan(aps, 40);
    
    for (int i=0; i<found; i++) {
        WiFiAccessPoint& ap = aps[i];
        initList = initList + (String) i;
        initList = initList + "\t";
        initList = initList + aps[i].ssid;
        initList = initList + "\n";
    }
    return found;
} 

 /*
void wifi_scan_callback(WiFiAccessPoint* wap, void* data)
{
    aps = wap;
    
    Serial.print("SSID: ");
    Serial.println(ap.ssid);
    Serial.print("Security: ");
    Serial.println(ap.security);
    Serial.print("Channel: ");
    Serial.println(ap.channel);
    Serial.print("RSSI: ");
    Serial.println(ap.rssi);
    
}
*/

int choose(String input){
    chosen = "";
    idx = input.toInt();
    targetName = aps[idx].ssid;
    chosen = chosen + "SSID: ";
    chosen = chosen + aps[idx].ssid;
    chosen = chosen + "\nSignal Strength: ";
    chosen = chosen + (String) aps[idx].rssi;
    
    return aps[idx].rssi;
}

int locating(String command){
    locateOutput = "";
    
    int found = WiFi.scan(aps, 40);
    for (int i=0; i<found; i++) {
        String name = (String) aps[i].ssid;
        if ((name).compareTo(targetName) == 0){
            locateOutput = locateOutput + targetName;
            locateOutput = locateOutput + "\nStrength: ";
            locateOutput = locateOutput + (String) aps[i].rssi;
            return 1;
        }
    }
    
    locateOutput = "Lost signal!";
    return 0;
}

