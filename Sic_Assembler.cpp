#include<bits/stdc++.h>
using namespace std;

string format1Arr[] = {"FIX" , "FLOAT" , "HIO" , "NORM" , "SIO" , "TIO"};
string format2Arr[] = {"ADDR" , "CLEAR" , "COMPR" , "DIVR" , "MULR" , "RMO" , "SHIFTL" , "SHIFTR" , "SUBR" , "SVC" , "TIXR"};
pair<string, string> opCodeArr[] = { {"ADD" , "18"} , {"ADDF" , "58"} , {"ADDR" , "90"} , {"AND" , "40"} , {"CLEAR" , "B4"} , {"COMP" , "28"} , {"COMPF" , "88"} , {"COMPR" , "A0"} , {"DIV" , "24"} ,
{"DIVF" , "64"} , {"DIVR" , "9C"} , {"FIX" , "C4"} , {"FLOAT" , "C0"} , {"HIO" , "F4"} , {"J" , "3C"} , {"JEQ" , "30"} , {"JGT" , "34"} , {"JLT" , "38"} , {"JSUB" , "48"} , {"LDA" , "00"} ,
{"LDB" , "68"} , {"LDCH" , "50"} , {"LDF" , "70"} , {"LDL" , "08"} , {"LDS" , "6C"} , {"LDT" , "74"} , {"LDX" , "04"} , {"LPS" , "D0"} , {"MUL" , "20"} , {"SSK" , "EC"} , {"STA" , "0C"} ,
{"STB" , "78"} , {"STCH" , "54"} , {"STF" , "80"} , {"STI" , "D4"} , {"STL" , "14"} , {"STS" , "7C"} , {"STSW" , "E8"} , {"STT" , "84"} , {"STX" , "10"} , {"SUB" , "1C"} , {"SUBF" , "5C"} ,
{"MULF" , "60"} , {"MULR" , "98"} , {"NORM" , "C8"} , {"OR" , "44"} , {"RD" , "D8"} , {"RMO" , "AC"} , {"RSUB" , "4C"} , {"SHIFTL" , "A4"} , {"SHIFTR" , "A8"} , {"SIO" , "F0"} , {"SUBR" , "94"} ,
{"SVC" , "B0"} , {"TD" , "E0"} , {"TIO" , "F8"} , {"TIX" , "2C"} , {"TIXR" , "B8"} , {"WD" , "DC"} };

const int MAX_PC = 2047 , MIN_PC = -2048 , MAX_BASE = 4095 , MIN_BASE = 0;

pair<string, string> registerOP[] = { {"A" , "0"} , {"X" , "1"} , {"L" , "2"} , {"B" , "3"} , {"S" , "4"} , {"T" , "5"} , {"F" , "6"} , {"PC" , "8"} , {"SW" , "9"} };

void writeSymTabintoFile(vector<string> &locArr, vector<string> &symbolsArr, vector<string> &instArr, vector<string> &refArr){
    ofstream outFile("symtab.txt");
    if (outFile.is_open()){
        for (size_t i = 0 ; i < locArr.size() ; i++){
            outFile << locArr[i] << '\t' << symbolsArr[i] << '\t' << instArr[i] << '\t' << refArr[i] << endl;
        }
        outFile.close();
    }
    else
        cout << "Couldn't Write SymTab to file" << endl;
}

void writeObjTabintoFile(vector<string> &locArr, vector<string> &symbolsArr, vector<string> &instArr, vector<string> &refArr, vector<string> &objArr){
    ofstream outFile("objtab.txt");
    if (outFile.is_open()){
        for (size_t i = 0 ; i < locArr.size() ; i++){
            outFile << locArr[i] << '\t' << symbolsArr[i] << '\t' << instArr[i] << '\t' << refArr[i] << '\t' << objArr[i] << endl;
        }
        outFile.close();
    }
    else
        cout << "Couldn't Write ObjTab to file" << endl;
}

void writeHTEintoFile(string headerRecord, vector<string> &textRecords, vector<string> &modificationRecords, string endRecord){
    ofstream outFile("outHTE.txt");
    if (outFile.is_open()){
        outFile << headerRecord << endl;
        for (const auto& record : textRecords){
            outFile << record;
        }
        for (const auto& record : modificationRecords){
            outFile << record << endl;
        }
        outFile << endRecord << endl;
        outFile.close();
    }
}

int convertHexToDec(string hexString){
    int dec;
    stringstream stream(hexString);
    stream >> hex >> dec;
    return dec;
}

int convertStringToInt(string str){
    int value;
    stringstream(str) >> value;
    return value;
}

string convertDecToHex(int decimal){
    stringstream stream2;
    stream2 << hex << decimal;
    string result(stream2.str());
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

string convertHexToBin(string text){
    string binaryResult;
    for (char c : text){
        switch(toupper(c)){
            case '0': binaryResult += "0000"; break;
            case '1': binaryResult += "0001"; break;
            case '2': binaryResult += "0010"; break;
            case '3': binaryResult += "0011"; break;
            case '4': binaryResult += "0100"; break;
            case '5': binaryResult += "0101"; break;
            case '6': binaryResult += "0110"; break;
            case '7': binaryResult += "0111"; break;
            case '8': binaryResult += "1000"; break;
            case '9': binaryResult += "1001"; break;
            case 'A': binaryResult += "1010"; break;
            case 'B': binaryResult += "1011"; break;
            case 'C': binaryResult += "1100"; break;
            case 'D': binaryResult += "1101"; break;
            case 'E': binaryResult += "1110"; break;
            case 'F': binaryResult += "1111"; break;
        }
    }
    return binaryResult;
}

string convertBinToHex(string binText){
    stringstream res;
    bitset<24> set(binText);
    res << hex << uppercase << set.to_ulong();
    return res.str();
}

bool checkIfNumber(const string& str){
    return all_of(str.begin(), str.end(), ::isdigit);
}

bool searchFormat1(const string& str){
    return find(begin(format1Arr), end(format1Arr), str) != end(format1Arr);
}

bool searchFormat2(const string& str){
    return find(begin(format2Arr), end(format2Arr), str) != end(format2Arr);
}

string searchOpCode(const string& str){
    for (const auto& opcode : opCodeArr){
        if (str == opcode.first){
            return opcode.second;
        }
    }
    return "";
}

string searchRegOpCode(const string& str){
    for (const auto& reg : registerOP){
        if (str == reg.first){
            return reg.second;
        }
    }
    return "";
}

string byteXopcode(const string& str){
    string result = str.substr(2 , str.length() - 3);
    return result;
}

string byteCopcode(const string& str){
    string result = str.substr(2 , str.length() - 3);
    stringstream stream;
    for (char c : result) {
        stream << hex << int(c);
    }
    string answer = stream.str();
    transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
    return answer;
}

bool isIndexBased(const string& str){
    return str.size() >= 2 && (str.substr(str.size() - 2) == ",X" || str.substr(str.size() - 2) == ",x");
}

bool checkIfPcRelative(int num){
    return num >= MIN_PC && num <= MAX_PC;
}

string searchForLocation(const string& str){
    ifstream symbolTable("symtab.txt");
    string line;
    while(getline(symbolTable, line)){
        stringstream ss(line);
        string loc, sym;
        ss >> loc >> sym;
        if (sym == str){
            return loc;
        }
    }
    return "";
}

int searchForBaseValue(const vector<string>& locArr, const vector<string>& symbolsArr, const vector<string>& instArr, const vector<string>& refArr){
    for (size_t i = 0 ; i < instArr.size() ; i++){
        if (instArr[i] == "BASE"){
            string hexLoc = searchForLocation(refArr[i]);
            return convertHexToDec(hexLoc);
        }
    }
    return 0;
}

int main()
{
    ifstream inputFile("sicxe.txt");

    vector<string> symbolsArr;
    vector<string> instArr;
    vector<string> refArr;
    vector<string> locArr;
    vector<string> objArr;

    string line, symbolsText, instText, refText;
    while(getline(inputFile, line)){
        stringstream ss(line);
        getline(ss , symbolsText , '\t');
        getline(ss , instText , '\t');
        getline(ss , refText , '\t');
        symbolsArr.push_back(symbolsText);
        instArr.push_back(instText);
        refArr.push_back(refText);
        locArr.push_back("");
        objArr.push_back("");
    }
    inputFile.close();

    locArr[0] = locArr[1] = refArr[0];

    string endAddress = "";
    for (size_t i = 1; i < instArr.size(); ++i){
        if (instArr[i] == ""){
            break;
        }
        if (symbolsArr[i+1] == "" && instArr[i+1] == "" && refArr[i+1] == ""){
            break;
        }

        int countIncr = 0;
        if (instArr[i + 1] == "BASE"){
            countIncr = 0;
            locArr[i + 1] = "";
        }
        else if (instArr[i].substr(0 , 1) == "+"){
            countIncr = 4;
        }
        else if (searchFormat1(instArr[i])){
            countIncr = 1;
        }
        else if (searchFormat2(instArr[i])){
            countIncr = 2;
        }
        else if (instArr[i] == "BYTE"){
            string temp = refArr[i];
            if (temp[0] == 'X' || temp[0] == 'x'){
                countIncr = (temp.length() - 3) / 2 ;
            }
            else if (temp[0] == 'C' || temp[0] == 'c'){
                countIncr = temp.length() - 3;
            }
        }
        else if (instArr[i] == "RESW"){
            countIncr = convertStringToInt(refArr[i]) * 3;
        }
        else if (instArr[i] == "RESB"){
            countIncr = convertStringToInt(refArr[i]);
        }
        else{
            countIncr = 3;
        }
        if (locArr[i].empty()) break;
        int temp = convertHexToDec(locArr[i]);
        locArr[i + 1] = convertDecToHex(temp + countIncr);

        if (instArr[i + 1] == "END"){
            endAddress = locArr[i + 1];
        }
    }

    writeSymTabintoFile(locArr, symbolsArr, instArr, refArr);

    for (size_t i = 0; i < instArr.size(); ++i){
        string temp = instArr[i];
        if (temp.substr(0 , 1) == "+"){
            temp = instArr[i].substr(1 , instArr[i].length() - 1);
        }
        if (temp == "START" || temp == "BASE" || temp == "RESB" || temp == "RESW" || temp == "END"){
            objArr[i] = "";
        }
        else if (temp == "BYTE"){
            string byte = refArr[i];
            if (byte[0] == 'X' || byte[0] == 'x'){
                objArr[i] = byteXopcode(byte);
            }
            else if (byte[0] == 'C' || byte[0] == 'c'){
                objArr[i] = byteCopcode(byte);
            }
        }
        else if (temp == "WORD"){
            string word = convertDecToHex(convertStringToInt(refArr[i]));
            while (word.length() < 6){
                word = "0" + word;
            }
            objArr[i] = word;
        }
        else if (temp == "RSUB"){
            string opRsub = searchOpCode(temp);
            string opRbits = convertHexToBin(opRsub).substr(0 , 6);
            opRbits = opRbits + "110000000000";
            objArr[i] = convertBinToHex(opRbits);
        }
        else if (searchFormat2(temp)){
            string opForm2 = searchOpCode(temp);
            if (refArr[i].length() == 5){
                opForm2 += searchRegOpCode(refArr[i].substr(0 , 2));
                opForm2 += searchRegOpCode(refArr[i].substr(3 , 1));
            }
            else if (refArr[i].length() == 4){
                if (refArr[i].substr(0 , 2) == "PC" || refArr[i].substr(0 , 2) == "SW"){
                    opForm2 += searchRegOpCode(refArr[i].substr(0 , 2));
                    opForm2 += searchRegOpCode(refArr[i].substr(3 , 1));
                }
                else {
                    opForm2 += searchRegOpCode(refArr[i].substr(0 , 1));
                    opForm2 += searchRegOpCode(refArr[i].substr(2 , 1));
                }
            }
            else if (refArr[i].length() == 3){
                if (checkIfNumber(refArr[i].substr(2 , 1))){
                    opForm2 += searchRegOpCode(refArr[i].substr(0 , 1));
                    opForm2 += refArr[i].substr(2 , 1);
                }
                else{
                    opForm2 += searchRegOpCode(refArr[i].substr(0 , 1));
                    opForm2 += searchRegOpCode(refArr[i].substr(2 , 1));
                }
            }
            else if (refArr[i].length() == 2){
                opForm2 += searchRegOpCode(refArr[i]);
            }
            else if (refArr[i].length() == 1){
                opForm2 += searchRegOpCode(refArr[i]);
            }
            while (opForm2.length() < 4){
                opForm2 += "0";
            }
            objArr[i] = opForm2;
        }

        else if (searchFormat1(temp)){
            string opForm1 = searchOpCode(temp);
            objArr[i] = opForm1;
        }
        else if (instArr[i].substr(0 , 1) == "+"){
            string opForm4 = searchOpCode(temp);
            string bits6Op = convertHexToBin(opForm4).substr(0 , 6);
            string n4 = "1", i4 = "1", x4 = "0", b4 = "0", p4 = "0", e4 = "1";
            string symbolLocation = searchForLocation(refArr[i]);
            if (refArr[i].substr(0 , 1) == "#"){
                n4 = "0";
                if (checkIfNumber(refArr[i].substr(1))){
                    symbolLocation = convertDecToHex(convertStringToInt(refArr[i].substr(1)));
                }
                else
                    symbolLocation = searchForLocation(refArr[i].substr(1));
            }
            if (refArr[i].substr(0 , 1) == "@"){
                i4 = "0";
                symbolLocation = searchForLocation(refArr[i].substr(1));
            }
            if (isIndexBased(refArr[i])){
                x4 = "1";
                symbolLocation = searchForLocation(refArr[i].substr(0 , refArr[i].length() - 2));
            }
            if (isIndexBased(refArr[i]) && refArr[i].substr(0 , 1) == "@"){
                i4 = "0";
                x4 = "1";
                symbolLocation = searchForLocation(refArr[i].substr(1 , refArr[i].length() - 3));
            }
            if (isIndexBased(refArr[i]) && refArr[i].substr(0 , 1) == "#"){
                n4 = "0";
                x4 = "1";
                symbolLocation = searchForLocation(refArr[i].substr(1 , refArr[i].length() - 3));
            }
            string nixbpe4 = n4 + i4 + x4 + b4 + p4 + e4;
            opForm4 = bits6Op + nixbpe4;
            while (symbolLocation.length() < 5) {
                symbolLocation = "0" + symbolLocation;
            }
            objArr[i] = convertBinToHex(opForm4) + symbolLocation;
        }
        else if (instArr[i].substr(0 , 1) != "+" && !searchFormat1(temp) && !searchFormat2(temp) && !instArr[i].empty()){
            string opForm3 = searchOpCode(temp);
            string bits6Op3 = convertHexToBin(opForm3).substr(0 , 6);
            string n3 = "1", i3 = "1", x3 = "0", b3 = "0", p3 = "1", e3 = "0";
            string symbolDisp = searchForLocation(refArr[i]);
            bool isImmediate = false;
            if (refArr[i].substr(0 , 1) == "#"){
                n3 = "0";
                if (checkIfNumber(refArr[i].substr(1))){
                    symbolDisp = convertDecToHex(convertStringToInt(refArr[i].substr(1)));
                    p3 = "0";
                    isImmediate = true;
                }
                else
                    symbolDisp = searchForLocation(refArr[i].substr(1));
            }
            if (refArr[i].substr(0 , 1) == "@" && !isImmediate){
                i3 = "0";
                symbolDisp = searchForLocation(refArr[i].substr(1));
            }
            if (isIndexBased(refArr[i]) && !isImmediate){
                x3 = "1";
                symbolDisp = searchForLocation(refArr[i].substr(0 , refArr[i].length() - 2));
            }
            if (isIndexBased(refArr[i]) && refArr[i].substr(0 , 1) == "@" && !isImmediate){
                i3 = "0";
                x3 = "1";
                symbolDisp = searchForLocation(refArr[i].substr(1 , refArr[i].length() - 3));
            }
            if (isIndexBased(refArr[i]) && refArr[i].substr(0 , 1) == "#" && !isImmediate){
                n3 = "0";
                x3 = "1";
                symbolDisp = searchForLocation(refArr[i].substr(1 , refArr[i].length() - 3));
            }
            int pc = locArr[i + 1].empty() ? convertHexToDec(locArr[i + 2]) : convertHexToDec(locArr[i+1]);
            int disp = convertHexToDec(symbolDisp) - pc;
            if (!checkIfPcRelative(disp) && !isImmediate){
                p3 = "0";
                b3 = "1";
                int base = searchForBaseValue(locArr, symbolsArr, instArr, refArr);
                disp = convertHexToDec(symbolDisp) - base;
            }
            else if (checkIfPcRelative(disp) && !isImmediate){
                symbolDisp = convertDecToHex(disp);
            }
            string nixbpe3 = n3 + i3 + x3 + b3 + p3 + e3;
            opForm3 = bits6Op3 + nixbpe3;
            while (symbolDisp.length() < 3){
                symbolDisp = "0" + symbolDisp;
            }
            objArr[i] = convertBinToHex(opForm3) + symbolDisp;
            if (objArr[i].length() > 8){
                objArr[i] = objArr[i].substr(0 , 3) + objArr[i].substr(objArr[i].length() - 3);
            }
        }

        // Nesne kodunu 6 haneye tamamlama
        while (objArr[i].length() < 6){
            if (temp == "BASE" || temp == "LENGTH" || temp == "RESW" || temp == "RESB" || temp == "START" || temp == "END") {
                objArr[i] = "";
                break;
            }
            objArr[i] = "0" + objArr[i];
        }

        // Eðer komut BYTE ise, baþtaki sýfýrlarý kaldýr
        if (temp == "BYTE" && refArr[i][0] == 'X'){
            while (objArr[i].length() > 2 && objArr[i].substr(0, 2) == "00") {
                objArr[i] = objArr[i].substr(2);
            }
        }

        // Eðer komut format1 veya format2 komutlarý ise, baþtaki sýfýrlarý kaldýr
        if (searchFormat1(temp) || searchFormat2(temp)){
            while (objArr[i].length() > 2 && objArr[i].substr(0, 2) == "00") {
                objArr[i] = objArr[i].substr(2);
            }
        }
    }

    writeObjTabintoFile(locArr, symbolsArr, instArr, refArr, objArr);

    string hRecord = symbolsArr[0];
    while (hRecord.length() < 6){
        hRecord += "_";
    }
    string startAddress = locArr[0];
    while (startAddress.length() < 6){
        startAddress = "0" + startAddress;
    }
    string programLength = convertDecToHex(convertHexToDec(endAddress) - convertHexToDec(startAddress));
    while (programLength.length() < 6){
        programLength = "0" + programLength;
    }
    hRecord = "H^" + hRecord + "^" + startAddress + "^" + programLength;
    string endRecord = "E^" + startAddress;

    vector<string> tRecord;
    vector<string> mRecord;
    vector<string> temp;
    int textRLength = 0;
    bool flag = false;
    bool first = true;
    string lastAddress = "";

    for (size_t i = 0, j = 0; i < objArr.size(); ++i, ++j){
        if (objArr[i].empty()) continue;

        if (!flag){
            if (first){
                tRecord.push_back("T^" + locArr[i] + "^");
                first = false;
            }
            if (textRLength + objArr[i].length() / 2 <= 30){
                textRLength += objArr[i].length() / 2;
                temp.push_back(objArr[i]);
            }
            if (textRLength + objArr[i].length() / 2 > 30){
                textRLength = 0;
                flag = true;
                lastAddress = locArr[i + 1];
                tRecord.push_back(convertDecToHex(temp.size() * 3) + "^");
                tRecord.insert(tRecord.end(), temp.begin(), temp.end());
                tRecord.push_back("\n");
                temp.clear();
            }
        }
        else{
            if (!first){
                if (lastAddress.length() == 4)
                    lastAddress = "00" + lastAddress;
                else if (lastAddress.length() == 5)
                    lastAddress = "0" + lastAddress;
                tRecord.push_back("T^" + lastAddress + "^");
                first = true;
            }
            if (textRLength + objArr[i].length() / 2 <= 30){
                textRLength += objArr[j].length() / 2;
                temp.push_back(objArr[j]);
            }
            if (textRLength + objArr[i].length() / 2 > 30 || instArr[i] == "RESW" || instArr[i] == "RESB" || instArr[i] == "END"){
                textRLength = 0;
                string tLength = convertDecToHex(temp.size() * 3);
                if (tLength.length() == 1){
                    tLength = "0" + tLength;
                }
                tRecord.push_back(tLength + "^");
                tRecord.insert(tRecord.end(), temp.begin(), temp.end());
                tRecord.push_back("\n");
                temp.clear();

                while (instArr[i] == "RESW" || instArr[i] == "RESB"){
                    ++i;
                }
                j = i - 1;
                lastAddress = locArr[i];
                first = false;
                if (instArr[i] == "END")
                    break;
            }
        }
    }

    if (!temp.empty()) {
        tRecord.push_back(convertDecToHex(temp.size() * 3) + "^");
        tRecord.insert(tRecord.end(), temp.begin(), temp.end());
        tRecord.push_back("\n");
    }

    for (size_t i = 0; i < objArr.size(); ++i){
        if (objArr[i].length() == 8){
            string tempLoc = locArr[i];
            tempLoc = convertDecToHex(convertHexToDec(tempLoc) + 1);
            while (tempLoc.length() < 6){
                tempLoc = "0" + tempLoc;
            }
            if (refArr[i].substr(0 , 1) == "#"){
                if (!checkIfNumber(refArr[i].substr(1))){
                    mRecord.push_back("M^" + tempLoc + "^05");
                }
            }
            else{
                mRecord.push_back("M^" + tempLoc + "^05");
            }
        }
    }

    writeHTEintoFile(hRecord, tRecord, mRecord, endRecord);

    cout << "Loc  |" << '\t' << "Symb  |" << '\t' << "Inst  |" << '\t' << " Ref   |" << "   Obj   |" << endl << "_____|________|_______|________|_________|" << endl;

    for (size_t i = 0; i < instArr.size(); ++i){
        cout << locArr[i] << '\t' << symbolsArr[i] << '\t' << instArr[i] << '\t' << refArr[i] << '\t' << "  " << objArr[i] <<endl;
    }

    cout << hRecord << endl;

    for (const auto& record : tRecord){
        cout << record;
    }

    for (const auto& record : mRecord){
        cout << record << endl;
    }

    cout << endRecord << endl;

    return 0;
}
