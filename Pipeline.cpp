#include<bits/stdc++.h>
using namespace std;

class Function{
private:
    map<string,string> funOpcode;
public:
    Function();
    string getType(string &fun);
};

class Registers{
private:
    map<string,string> regBin;
public:
    Registers();
    string getRegister(string &reg);
};

class Trimming{
public:
    void removeSpace(string &ins, int &ptr);
    string extractString(string &ins, int &ptr);
    int extraCode(string &ins, int &ptr);
};

class File{
public:
    vector<string> readFile();
    void writeFile(vector<string> binary);
};

class R_type : public Registers, public Trimming{
private:
    string opcode;
    map<string,string> func7;
    map<string,string> func3;
public:
    R_type();
    int setValues(string &ins, int &ptr, string &rs1Bin, string &rs2Bin, string &rdBin);
    string getBinary(string &rs1, string &rs2, string &rd, string &function);
};

class I_type : public Registers, public Trimming{
private:
    string opcode;
    map<string,string> func3;
public:
    I_type();
    string intToImm(int &num);
    int setValues(string &ins, int &ptr, string &rs1Bin, int &imm, string &rdBin);
    string getBinary(string &rs1, int &immediate, string &rd, string &function);
};

class I_type2 : public Registers, public Trimming{
private:
    string opcode;
    map<string,string> func3;
    map<string,string> func7;
public:
    I_type2();
    string intToImm(int &num);
    int setValues(string &ins1, int &ptr, string &rs1Bin, int &imm, string &rdBin);
    string getBinary(string &rs1, int &immediate, string &rd, string &function);
};

class I_type3 : public Registers, public Trimming{
private:
    string opcode;
    map<string,string> func3;
public:
    I_type3();
    string intToImm(int &num);
    int setValues(string &ins, int &ptr, string &rs1Bin, int &imm, string &rdBin);
    string getBinary(string &rs1, int &immediate, string &rd, string &function);
};

class L_type : public Registers, public Trimming{
private:
    string opcode;
    map<string,string> func3;
public:
    L_type();
    string intToImm(int &num);
    int setValues(string &ins, int &ptr, string &rs1Bin, int &imm, string &rdBin);
    string getBinary(string &rs1, int &immediate, string &rd, string &function);
};

class S_type : public Registers, public Trimming{
private:
    string opcode;
    map<string,string> func3;
public:
    S_type();
    string intToImm(int &num);
    int setValues(string &ins, int &ptr, string &rs1Bin, int &imm, string &rs2Bin);
    string getBinary(string &rs1, string &rs2, int &immediate, string &function);
};

class B_type : public Registers, public Trimming{
private:
    string opcode;
    map<string,string> func3;
public:
    B_type();
    string intToImm(int &num);
    int setValues(string &ins, int &ptr, string &rs1Bin, int &imm, string &rs2Bin);
    string getBinary(string &rs1, string &rs2, int &immediate, string &function);
};

class J_type : public Registers, public Trimming{
private:
    string opcode;
public:
    J_type();
    string intToImm(int &num);
    int setValues(string &ins, int &ptr, string &rdBin, int &imm);
    string getBinary(string &rd, int &immediate);
};

class U_type : public Registers, public Trimming{
private:
    string opcode;
public:
    U_type();
    string intToImm(int &num);
    int setValues(string &ins, int &ptr, string &rdBin, int &imm);
    string getBinary(string &rd, int &immediate);
};

class Instruction : public Trimming, public Function{
private:
    int ptr;
    string ins;
    string type;
    string function;
    string rs1;
    string rs2;
    string rd;
    int imm;
public:
    int setIns(string);
    string getBin();
};

Function :: Function(){
    funOpcode = {
        {"ADD","R_type"},
        {"SUB","R_type"},
        {"MUL","R_type"},
        {"DIV","R_type"},
        {"REM","R_type"},
        {"AND","R_type"},
        {"OR","R_type"},
        {"XOR","R_type"},
        {"SLL","R_type"},
        {"SRL","R_type"},
        {"SRA","R_type"},
        {"SLT","R_type"},
        {"SLTU","R_type"},
        
        {"ADDI","I_type"},
        {"XORI","I_type"},
        {"ORI","I_type"},
        {"ANDI","I_type"},
        {"SLTI","I_type"},
        
        {"SLLI","I_type2"},
        {"SRLI","I_type2"},
        {"SRAI","I_type2"},
        
        {"JALR","I_type3"},
        
        {"LW","L_type"},
        {"LD","L_type"},
        {"LH","L_type"},
        {"LB","L_type"},
        {"LWU","L_type"},
        {"LHU","L_type"},
        {"LBU","L_type"},
        
        {"SW","S_type"},
        {"SB","S_type"},
        {"SH","S_type"},
        {"SD","S_type"},
        
        {"BEQ","B_type"},
        {"BNE","B_type"},
        {"BLT","B_type"},
        {"BGE","B_type"},
        {"BLTU","B_type"},
        {"BGEU","B_type"},
        
        {"JAL","J_type"},
        
        {"LUI","U_type"}
    };
}

string Function :: getType(string &fun){
    if(funOpcode.find(fun) != funOpcode.end()){
        return funOpcode[fun];
    }
    return "NULL";
}

Registers :: Registers(){
    regBin = {
        {"x0","00000"},{"zero","00000"},
        {"x1","00001"},{"ra","00001"},
        {"x2","00010"},{"sp","00010"},              // ---------------------------------
        {"x3","00011"},{"gp","00011"},
        {"x4","00100"},{"tp","00100"},
        {"x5","00101"},{"t0","00101"},
        {"x6","00110"},{"t1","00110"},
        {"x7","00111"},{"t2","00111"},
        {"x8","01000"},{"s0","01000"},{"fp","01000"},
        {"x9","01001"},{"s1","01001"},
        {"x10","01010"},{"a0","01010"},
        {"x11","01011"},{"a1","01011"},
        {"x12","01100"},{"a2","01100"},
        {"x13","01101"},{"a3","01101"},
        {"x14","01110"},{"a4","01110"},
        {"x15","01111"},{"a5","01111"},
        {"x16","10000"},{"a6","10000"},
        {"x17","10001"},{"a7","10001"},
        {"x18","10010"},{"s2","10010"},
        {"x19","10011"},{"s3","10011"},
        {"x20","10100"},{"s4","10100"},
        {"x21","10101"},{"s5","10101"},
        {"x22","10110"},{"s6","10110"},
        {"x23","10111"},{"s7","10111"},
        {"x24","11000"},{"s8","11000"},
        {"x25","11001"},{"s9","11001"},
        {"x26","11010"},{"s10","11010"},
        {"x27","11011"},{"s11","11011"},
        {"x28","11100"},{"t3","11100"},
        {"x29","11101"},{"t4","11101"},
        {"x30","11110"},{"t5","11110"},
        {"x31","11111"},{"t6","11111"}
    };
}

string Registers :: getRegister(string &reg){
    if(regBin.find(reg) != regBin.end()){
        return regBin[reg];
    }
    return "NULL";
}

void Trimming :: removeSpace(string &ins, int &ptr){
    while(ptr < ins.size() and (ins[ptr] == ' ' or ins[ptr] == ',' or ins[ptr] == '(' or ins[ptr] == ')'))
        ptr++;
}

string Trimming :: extractString(string &ins, int &ptr){
    string s = "";
    while(ptr < ins.size() and (ins[ptr] != ' ' and ins[ptr] != ',' and ins[ptr] != '(' and ins[ptr] != ')'))
        s.push_back(ins[ptr++]);
    return s;
}

int Trimming :: extraCode(string &ins, int &ptr){
    while(ptr < ins.size() and ins[ptr] == ' ') ptr++;
    if(ptr < ins.size() and ins[ptr] == ')'){
        ptr++;
        while(ptr < ins.size() and ins[ptr] == ' ') ptr++;
    }
    if(ptr != ins.size()){
        cout << "Error Extra Code\n";
        return 1;
    }
    return 0;
}

vector<string> File :: readFile(){
    ifstream fin;
    fin.open("assemblyCode.s");
    vector<string> instructions;
    char line[100];
    while(fin){
        fin.getline(line,100);
        string s = line;
        for(int i = 0; i < s.size(); i++){
            if(s[i] != ' '){
                instructions.push_back(s);
                break;
            }
        }
    }
    fin.close();
    return instructions;
}

void File :: writeFile(vector<string> binary){
    ofstream fout;
    fout.open("binaryCode.txt");
    for(int i = 0; i < binary.size(); i++){
        fout << binary[i] << "\n";
    }
    fout.close();
}

int Instruction :: setIns(string ins){
    this->ins = ins;
    ptr = 0;
    removeSpace(ins,ptr);
    function = extractString(ins,ptr);  
    for(int i = 0; i < function.size(); i++){
        function[i] = toupper(function[i]);
    }
    if(getType(function) == "NULL"){
        cout << "Wrong Function Used\n";
        return 1;
    }
    type = getType(function);
    return 0;
}

string Instruction :: getBin(){
    if(type == "R_type"){
        R_type rtype;
        if(rtype.setValues(ins,ptr,rs1,rs2,rd)) return "NULL";
        return rtype.getBinary(rs1,rs2,rd,function);
    }
    else if(type == "I_type"){
        I_type itype;
        if(itype.setValues(ins,ptr,rs1,imm,rd)) return "NULL";
        return itype.getBinary(rs1,imm,rd,function);
    }
    else if(type == "I_type2"){
        I_type2 itype2;
        if(itype2.setValues(ins,ptr,rs1,imm,rd)) return "NULL";
        return itype2.getBinary(rs1,imm,rd,function);
    }
    else if(type == "I_type3"){
        I_type3 itype3;
        if(itype3.setValues(ins,ptr,rs1,imm,rd)) return "NULL";
        return itype3.getBinary(rs1,imm,rd,function);
    }
    else if(type == "L_type"){
        L_type ltype;
        if(ltype.setValues(ins,ptr,rs1,imm,rd)) return "NULL";
        return ltype.getBinary(rs1,imm,rd,function);
    }
    else if(type == "S_type"){ 
        S_type stype;
        if(stype.setValues(ins,ptr,rs1,imm,rs2)) return "NULL";
        return stype.getBinary(rs1,rs2,imm,function);
    }
    else if(type == "B_type"){
        B_type btype;
        if(btype.setValues(ins,ptr,rs1,imm,rs2)) return "NULL";
        return btype.getBinary(rs1,rs2,imm,function);
    }
    else if(type == "J_type"){
        J_type jtype;
        if(jtype.setValues(ins,ptr,rd,imm)) return "NULL";
        return jtype.getBinary(rd,imm);
    }
    else if(type == "U_type"){
        U_type utype;
        if(utype.setValues(ins,ptr,rd,imm)) return "NULL";
        return utype.getBinary(rd,imm);
    }
    
    return "NULL";
}

R_type :: R_type(){
    opcode = "0110011";
    func7 = {
        {"ADD","0000000"},
        {"SUB","0100000"},
        {"MUL","0000001"},
        {"DIV","0000001"},
        {"REM","0000001"},
        {"AND","0000000"},
        {"OR","0000000"},
        {"XOR","0000000"},
        {"SLL","0000000"},
        {"SRL","0000000"},
        {"SRA","0100000"},
        {"SLT","0000000"},
        {"SLTU","0000000"}
    };
    func3 = {
        {"ADD","000"},
        {"SUB","000"},
        {"MUL","000"},
        {"DIV","100"},
        {"REM","110"},
        {"AND","111"},
        {"OR","110"},
        {"XOR","100"},
        {"SLL","001"},
        {"SRL","101"},
        {"SRA","101"},
        {"SLT","010"},
        {"SLTU","011"}
    };
}

int R_type :: setValues(string &ins, int &ptr, string &rs1Bin, string &rs2Bin, string &rdBin){
    removeSpace(ins,ptr);
    string rd = extractString(ins,ptr);
    removeSpace(ins,ptr);
    string rs1 = extractString(ins,ptr);
    removeSpace(ins,ptr);
    string rs2 = extractString(ins,ptr);
    if(extraCode(ins,ptr)){
        return 1;
    }
    if(getRegister(rs1) == "NULL" or getRegister(rs2) == "NULL" or getRegister(rd) == "NULL"){
        cout << "Wrong Register Used\n";
        return 1;
    }
    rdBin = getRegister(rd);
    rs1Bin = getRegister(rs1);
    rs2Bin = getRegister(rs2);
    return 0;
}

string R_type :: getBinary(string &rs1, string &rs2, string &rd, string &function){
    string encoded = func7[function] + rs2 + rs1 + func3[function] + rd + opcode;
    return encoded;
}

I_type :: I_type(){
    opcode = "0010011";
    func3 = {
        {"ADDI","000"},
        {"XORI","100"},
        {"ORI","110"},
        {"ANDI","111"},
        {"SLTI","010"}
    };
}

string I_type :: intToImm(int &num){
    string binary;
    bool neg = false;
    if(num < 0){
        neg = true;
        num *= -1;
    }
    while(num > 0){
        binary = (num % 2 == 0 ? "0" : "1") + binary;
        num /= 2;
    }
    int len = 12 - binary.size();
    string pref = "";
    for(int i = 0; i < len; i++) pref += "0";
    string numBin = binary.empty() ? pref : pref + binary;
    if(neg){
        for(int i = 0; i < numBin.size(); i++) numBin[i] ^= 1;
        int ptr = numBin.size() -1;
        while(ptr > 0 and numBin[ptr] == '1'){
            numBin[ptr] = '0';
            ptr--;
        }
        numBin[ptr] = '1';
    }
    return numBin;
}

int I_type :: setValues(string &ins, int &ptr, string &rs1Bin, int &imm, string &rdBin){
    removeSpace(ins,ptr);
    string rd = extractString(ins,ptr);
    removeSpace(ins,ptr);
    string rs1 = extractString(ins,ptr);
    removeSpace(ins,ptr);
    try{
        imm = stoi(extractString(ins,ptr));
    }
    catch(invalid_argument){
        cout << "Error in immediate\n";
        return 1;
    }
    catch(out_of_range){
        cout << "Immediate out of range\n";
        return 1;
    }
    if(extraCode(ins,ptr)){
        return 1;
    }
    if(getRegister(rs1) == "NULL" or getRegister(rd) == "NULL"){
        cout << "Wrong Register Used\n";
        return 1;
    }
    if(imm < -2048 or imm > 2047){
        cout << "Immediate out of range\n";
        return 1;
    }
    rdBin = getRegister(rd);
    rs1Bin = getRegister(rs1);
    return 0;
}

string I_type :: getBinary(string &rs1, int &immediate, string &rd, string &function){
    string encoded = intToImm(immediate) + rs1 + func3[function] + rd + opcode;
    return encoded;
}

I_type2 :: I_type2(){
    opcode = "0010011";
    func3 = {
        {"SLLI","001"},
        {"SRLI","101"},
        {"SRAI","101"}
    };
    func7 = {
        {"SLLI","0000000"},
        {"SRLI","0000000"},
        {"SRAI","0100000"}
    };
}

string I_type2 :: intToImm(int &num){
    string binary;
    bool neg = false;
    if(num < 0){
        neg = true;
        num *= -1;
    }
    while(num > 0){
        binary = (num % 2 == 0 ? "0" : "1") + binary;
        num /= 2;
    }
    int len = 5 - binary.size();
    string pref = "";
    for(int i = 0; i < len; i++) pref += "0";
    string numBin = binary.empty() ? pref : pref + binary;
    if(neg){
        for(int i = 0; i < numBin.size(); i++) numBin[i] ^= 1;
        int ptr = numBin.size() -1;
        while(ptr > 0 and numBin[ptr] == '1'){
            numBin[ptr] = '0';
            ptr--;
        }
        numBin[ptr] = '1';
    }
    return numBin;
}

int I_type2 :: setValues(string &ins, int &ptr, string &rs1Bin, int &imm, string &rdBin){
    removeSpace(ins,ptr);
    string rd = extractString(ins,ptr);
    removeSpace(ins,ptr);
    string rs1 = extractString(ins,ptr);
    removeSpace(ins,ptr);
    try{
        imm = stoi(extractString(ins,ptr));
    }
    catch(invalid_argument){
        cout << "Error in immediate\n";
        return 1;
    }
    catch(out_of_range){
        cout << "Immediate out of range\n";
        return 1;
    }
    if(extraCode(ins,ptr)){
        return 1;
    }
    if(getRegister(rs1) == "NULL" or getRegister(rd) == "NULL"){
        cout << "Wrong Register Used\n";
        return 1;
    }
    if(imm < 0 or imm > 31){
        cout << "Immediate out of range\n";
        return 1;
    }
    rdBin = getRegister(rd);
    rs1Bin = getRegister(rs1);
    return 0;
}

string I_type2 :: getBinary(string &rs1, int &immediate, string &rd, string &function){
    string encoded = func7[function] + intToImm(immediate) + rs1 + func3[function] + rd + opcode;
    return encoded;
}

I_type3 :: I_type3(){
    opcode = "1100111";
    func3 = {
        {"JALR","000"}
    };
}

string I_type3 :: intToImm(int &num){
    string binary;
    bool neg = false;
    if(num < 0){
        neg = true;
        num *= -1;
    }
    while(num > 0){
        binary = (num % 2 == 0 ? "0" : "1") + binary;
        num /= 2;
    }
    int len = 12 - binary.size();
    string pref = "";
    for(int i = 0; i < len; i++) pref += "0";
    string numBin = binary.empty() ? pref : pref + binary;
    if(neg){
        for(int i = 0; i < numBin.size(); i++) numBin[i] ^= 1;
        int ptr = numBin.size() -1;
        while(ptr > 0 and numBin[ptr] == '1'){
            numBin[ptr] = '0';
            ptr--;
        }
        numBin[ptr] = '1';
    }
    return numBin;
}

int I_type3 :: setValues(string &ins, int &ptr, string &rs1Bin, int &imm, string &rdBin){
    removeSpace(ins,ptr);
    string rd = extractString(ins,ptr);
    removeSpace(ins,ptr);
    try{
        imm = stoi(extractString(ins,ptr));
    }
    catch(invalid_argument){
        cout << "Error in immediate\n";
        return 1;
    }
    catch(out_of_range){
        cout << "Immediate out of range\n";
        return 1;
    }
    removeSpace(ins,ptr);
    string rs1 = extractString(ins,ptr);
    if(extraCode(ins,ptr)){
        return 1;
    }
    if(getRegister(rs1) == "NULL" or getRegister(rd) == "NULL"){
        cout << "Wrong Register Used\n";
        return 1;
    }
    if(imm < -2048 or imm > 2047){
        cout << "Immediate out of range\n";
        return 1;
    }
    rdBin = getRegister(rd);
    rs1Bin = getRegister(rs1);
    return 0;
}

string I_type3 :: getBinary(string &rs1, int &immediate, string &rd, string &function){
    string encoded = intToImm(immediate) + rs1 + func3[function] + rd + opcode;
    return encoded;
}

L_type :: L_type(){
    opcode = "0000011";
    func3 = {
        {"LW","010"},
        {"LD","011"},
        {"LH","001"},
        {"LB","000"},
        {"LWU","110"},
        {"LHU","101"},
        {"LBU","100"}
    };
}

string L_type :: intToImm(int &num){
    string binary;
    bool neg = false;
    if(num < 0){
        neg = true;
        num *= -1;
    }
    while(num > 0){
        binary = (num % 2 == 0 ? "0" : "1") + binary;
        num /= 2;
    }
    int len = 12 - binary.size();
    string pref = "";
    for(int i = 0; i < len; i++) pref += "0";
    string numBin = binary.empty() ? pref : pref + binary;
    if(neg){
        for(int i = 0; i < numBin.size(); i++) numBin[i] ^= 1;
        int ptr = numBin.size() -1;
        while(ptr > 0 and numBin[ptr] == '1'){
            numBin[ptr] = '0';
            ptr--;
        }
        numBin[ptr] = '1';
    }
    return numBin;
}

int L_type :: setValues(string &ins, int &ptr, string &rs1Bin, int &imm, string &rdBin){
    removeSpace(ins,ptr);
    string rd = extractString(ins,ptr);
    removeSpace(ins,ptr);
    try{
        imm = stoi(extractString(ins,ptr));
    }
    catch(invalid_argument){
        cout << "Error in immediate\n";
        return 1;
    }
    catch(out_of_range){
        cout << "Immediate out of range\n";
        return 1;
    }
    removeSpace(ins,ptr);
    string rs1 = extractString(ins,ptr);
    if(extraCode(ins,ptr)){
        return 1;
    }
    if(getRegister(rs1) == "NULL" or getRegister(rd) == "NULL"){
        cout << "Wrong Register Used\n";
        return 1;
    }
    if(imm < -2048 or imm > 2047){
        cout << "Immediate out of range\n";
        return 1;
    }
    rdBin = getRegister(rd);
    rs1Bin = getRegister(rs1);
    return 0;
}

string L_type :: getBinary(string &rs1, int &immediate, string &rd, string &function){
    string encoded = intToImm(immediate) + rs1 + func3[function] + rd + opcode;
    return encoded;
}

S_type :: S_type(){
    opcode = "0100011";
    func3 = {
        {"SW","010"},
        {"SB","000"},
        {"SH","001"},
        {"SD","011"}
    };
}

string S_type :: intToImm(int &num){
    string binary;
    bool neg = false;
    if(num < 0){
        neg = true;
        num *= -1;
    }
    while(num > 0){
        binary = (num % 2 == 0 ? "0" : "1") + binary;
        num /= 2;
    }
    int len = 12 - binary.size();
    string pref = "";
    for(int i = 0; i < len; i++) pref += "0";
    string numBin = binary.empty() ? pref : pref + binary;
    if(neg){
        for(int i = 0; i < numBin.size(); i++) numBin[i] ^= 1;
        int ptr = numBin.size() -1;
        while(ptr > 0 and numBin[ptr] == '1'){
            numBin[ptr] = '0';
            ptr--;
        }
        numBin[ptr] = '1';
    }
    return numBin;
}

int S_type :: setValues(string &ins, int &ptr, string &rs1Bin, int &imm, string &rs2Bin){
    removeSpace(ins,ptr);
    string rs2 = extractString(ins,ptr);
    removeSpace(ins,ptr);
    try{
        imm = stoi(extractString(ins,ptr));
    }
    catch(invalid_argument){
        cout << "Error in immediate\n";
        return 1;
    }
    catch(out_of_range){
        cout << "Immediate out of range\n";
        return 1;
    }
    removeSpace(ins,ptr);
    string rs1 = extractString(ins,ptr);
    if(extraCode(ins,ptr)){
        return 1;
    }
    if(getRegister(rs1) == "NULL" or getRegister(rs2) == "NULL"){
        cout << "Wrong Register Used\n";
        return 1;
    }
    if(imm < -2048 or imm > 2047){
        cout << "Immediate out of range\n";
        return 1;
    }
    rs2Bin = getRegister(rs2);
    rs1Bin = getRegister(rs1);
    return 0;
}

string S_type :: getBinary(string &rs1, string &rs2, int &immediate, string &function){
    string imm = intToImm(immediate);
    string encoded = "";
    for(int i = 0; i < 7; i++) encoded.push_back(imm[i]);
    encoded += rs2 + rs1 + func3[function];
    for(int i = 7; i < 12; i++) encoded.push_back(imm[i]);
    encoded += opcode;
    return encoded;
}

B_type :: B_type(){
    opcode = "1100011";
    func3 = {
        {"BEQ","000"},
        {"BNE","001"},
        {"BLT","100"},
        {"BGE","101"},
        {"BLTU","110"},
        {"BGEU","111"}
    };
}

string B_type :: intToImm(int &num){
    string binary;
    bool neg = false;
    if(num < 0){
        neg = true;
        num *= -1;
    }
    while(num > 0){
        binary = (num % 2 == 0 ? "0" : "1") + binary;
        num /= 2;
    }
    int len = 12 - binary.size();
    string pref = "";
    for(int i = 0; i < len; i++) pref += "0";
    string numBin = binary.empty() ? pref : pref + binary;
    if(neg){
        for(int i = 0; i < numBin.size(); i++) numBin[i] ^= 1;
        int ptr = numBin.size() -1;
        while(ptr > 0 and numBin[ptr] == '1'){
            numBin[ptr] = '0';
            ptr--;
        }
        numBin[ptr] = '1';
    }
    return numBin;
}

int B_type :: setValues(string &ins, int &ptr, string &rs1Bin, int &imm, string &rs2Bin){
    removeSpace(ins,ptr);
    string rs1 = extractString(ins,ptr);
    removeSpace(ins,ptr);
    string rs2 = extractString(ins,ptr);
    removeSpace(ins,ptr);
    try{
        imm = stoi(extractString(ins,ptr));
    }
    catch(invalid_argument){
        cout << "Error in immediate\n";
        return 1;
    }
    catch(out_of_range){
        cout << "Immediate out of range\n";
        return 1;
    }
    if(extraCode(ins,ptr)){
        return 1;
    }
    if(getRegister(rs1) == "NULL" or getRegister(rs2) == "NULL"){
        cout << "Wrong Register Used\n";
        return 1;
    }
    if(imm < -2048 or imm > 2047){
        cout << "Immediate out of range\n";
        return 1;
    }
    rs2Bin = getRegister(rs2);
    rs1Bin = getRegister(rs1);
    return 0;
}

string B_type :: getBinary(string &rs1, string &rs2, int &immediate, string &function){
    string encoded = "";
    if(immediate >= 0) encoded += '0';
    else encoded += '1';
    string imm = intToImm(immediate);
    for(int i = 1; i < 7; i++) encoded.push_back(imm[i]);
    encoded += rs2 + rs1 + func3[function];
    for(int i = 7; i < 11; i++) encoded.push_back(imm[i]);
    encoded.push_back(imm[11]);
    encoded += opcode;
    return encoded;
}

J_type :: J_type(){
    opcode = "1101111";
}

string J_type :: intToImm(int &num){
    string binary;
    bool neg = false;
    if(num < 0){
        neg = true;
        num *= -1;
    }
    while(num > 0){
        binary = (num % 2 == 0 ? "0" : "1") + binary;
        num /= 2;
    }
    int len = 21 - binary.size();
    string pref = "";
    for(int i = 0; i < len; i++) pref += "0";
    string numBin = binary.empty() ? pref : pref + binary;
    if(neg){
        for(int i = 0; i < numBin.size(); i++) numBin[i] ^= 1;
        int ptr = numBin.size() -1;
        while(ptr > 0 and numBin[ptr] == '1'){
            numBin[ptr] = '0';
            ptr--;
        }
        numBin[ptr] = '1';
    }
    return numBin;
}

int J_type :: setValues(string &ins, int &ptr, string &rdBin, int &imm){
    removeSpace(ins,ptr);
    string rd = extractString(ins,ptr);
    removeSpace(ins,ptr);
    try{
        imm = stoi(extractString(ins,ptr));
    }
    catch(invalid_argument){
        cout << "Error in immediate\n";
        return 1;
    }
    catch(out_of_range){
        cout << "Immediate out of range\n";
        return 1;
    }
    if(extraCode(ins,ptr)){
        return 1;
    }
    if(getRegister(rd) == "NULL"){
        cout << "Wrong Register Used\n";
        return 1;
    }
    if(imm < -1048576 or imm > 1048574){
        cout << "Immediate out of range\n";
        return 1;
    }
    rdBin = getRegister(rd);
    return 0;
}


string J_type :: getBinary(string &rd, int &immediate){
    string encoded = "";
    string imm = intToImm(immediate);
    encoded.push_back(imm[0]);
    for(int i = 10; i <= 19; i++) encoded.push_back(imm[i]);
    encoded.push_back(imm[9]);
    for(int i = 1; i <= 8; i++) encoded.push_back(imm[i]);
    encoded += rd + opcode;
    return encoded;
}


U_type :: U_type(){
    opcode = "0110111";
}

string U_type :: intToImm(int &num){
    string binary;
    bool neg = false;
    if(num < 0){
        neg = true;
        num *= -1;
    }
    while(num > 0){
        binary = (num % 2 == 0 ? "0" : "1") + binary;
        num /= 2;
    }
    int len = 32 - binary.size();
    string pref = "";
    for(int i = 0; i < len; i++) pref += "0";
    string numBin = binary.empty() ? pref : pref + binary;
    if(neg){
        for(int i = 0; i < numBin.size(); i++) numBin[i] ^= 1;
        int ptr = numBin.size() -1;
        while(ptr > 0 and numBin[ptr] == '1'){
            numBin[ptr] = '0';
            ptr--;
        }
        numBin[ptr] = '1';
    }
    return numBin;
}

int U_type :: setValues(string &ins, int &ptr, string &rdBin, int &imm){
    removeSpace(ins,ptr);
    string rd = extractString(ins,ptr);
    removeSpace(ins,ptr);
    try{
        imm = stoi(extractString(ins,ptr));
    }
    catch(invalid_argument){
        cout << "Error in immediate\n";
        return 1;
    }
    catch(out_of_range){
        cout << "Immediate out of range\n";
        return 1;
    }
    if(extraCode(ins,ptr)){
        return 1;
    }
    if(getRegister(rd) == "NULL"){
        cout << "Wrong Register Used\n";
        return 1;
    }
    if(imm < -1048576 or imm > 1048574){
        cout << "Immediate out of range\n";
        return 1;
    }
    rdBin = getRegister(rd);
    return 0;
}

string U_type :: getBinary(string &rd, int &immediate){
    string encoded = "";
    string imm = intToImm(immediate);
    for(int i = 12; i < 32; i++) encoded.push_back(imm[i]);
    encoded += rd + opcode;
    return encoded;
}

class _PC{
public:
    int pc;
    bool complete;
    bool halt;
    _PC(){
        pc = 0;
        complete = false;
        halt = false;
    }
};

class _IFID{
public:
    int DPC;
    int NPC;
    string IR;
    bool complete;
    _IFID(){
        DPC = 0, NPC = 0;
        IR = "";
        complete = false;
    }
};

class _IDEX{
public:
    int JPC;
    int DPC;
    int NPC;
    int rs1;
    int rs2;
    int SDValue;
    string rdl;
    string fun3;
    string fun7;
    string imm;
    string op;
    bool complete;
    map<string,int> CW;
    _IDEX(){
        JPC = 0, DPC = 0, NPC = 0;
        rs1 = 0, rs2 = 0, SDValue = 0;
        rdl = "", fun3 = "", fun7 = "", imm = "", op = "";
        complete = false;
        CW = {
            {"RegRead",0},
            {"RegWrite",0},
            {"MemRead",0},
            {"MemWrite",0},
            {"Mem2Reg",0},
            {"ALUSrc",0},
            {"ALUOp",0},
            {"Branch",0},
            {"Jump",0}
        };
    }
};

class _EXMO{
public:
    int ALUOUT;
    int SDValue;
    string rdl;
    bool complete;
    map<string,int> CW;
    _EXMO(){
        ALUOUT = 0, SDValue = 0;
        rdl = "";
        complete = false;
        CW = {
            {"RegRead",0},
            {"RegWrite",0},
            {"MemRead",0},
            {"MemWrite",0},
            {"Mem2Reg",0},
            {"ALUSrc",0},
            {"ALUOp",0},
            {"Branch",0},
            {"Jump",0}
        };
    }
};

class _MOWB{
public:
    int LDOUT;
    int ALUOUT;
    string rdl;
    bool complete;
    map<string,int> CW;
    _MOWB(){
        LDOUT = 0, ALUOUT = 0;
        rdl = "";
        complete = false;
        CW = {
            {"RegRead",0},
            {"RegWrite",0},
            {"MemRead",0},
            {"MemWrite",0},
            {"Mem2Reg",0},
            {"ALUSrc",0},
            {"ALUOp",0},
            {"Branch",0},
            {"Jump",0}
        };
    }
};

class Pipeline{
private:
    int instructions;
    vector<string> IM;
    map<string,int> GPR;
    map<int,int> DM;
    map<string,int> stall;
public:
    Pipeline(vector<string> binary){
        instructions = 0;
        IM = binary;
        GPR = {
            {"00000",0},
            {"00001",0},
            {"00010",0},
            {"00011",0},
            {"00100",0},
            {"00101",0},
            {"00110",0},
            {"00111",0},
            {"01000",0},
            {"01001",0},
            {"01010",0},
            {"01011",0},
            {"01100",0},
            {"01101",0},
            {"01110",0},
            {"01111",0},
            {"10000",0},
            {"10001",0},
            {"10010",0},
            {"10011",0},
            {"10100",0},
            {"10101",0},
            {"10110",0},
            {"10111",0},
            {"11000",0},
            {"11001",0},
            {"11010",0},
            {"11011",0},
            {"11100",0},
            {"11101",0},
            {"11110",0},
            {"11111",0}
        };
        
        stall = {
            {"00000",0},
            {"00001",0},
            {"00010",0},
            {"00011",0},
            {"00100",0},
            {"00101",0},
            {"00110",0},
            {"00111",0},
            {"01000",0},
            {"01001",0},
            {"01010",0},
            {"01011",0},
            {"01100",0},
            {"01101",0},
            {"01110",0},
            {"01111",0},
            {"10000",0},
            {"10001",0},
            {"10010",0},
            {"10011",0},
            {"10100",0},
            {"10101",0},
            {"10110",0},
            {"10111",0},
            {"11000",0},
            {"11001",0},
            {"11010",0},
            {"11011",0},
            {"11100",0},
            {"11101",0},
            {"11110",0},
            {"11111",0}
        };
        
        for(int i = 0; i <= 20; i++) DM[i] = 0;
    }
    
    string extract(string str, int end, int start){
        if(str == "") return str;
        int s = 31 - end;
        int e = 31 - start;
        string newStr = "";
        for(int i = s; i <= e; i++) newStr.push_back(str[i]);
        return newStr;
    }
    
    string extractB(string str, int end1, int start1, int end2, int start2){
        if(str == "") return str;
        string str1 = "";
        int s1 = 31 - end1, e1 = 31 - start1;
        for(int i = s1; i <= e1; i++) str1.push_back(str[i]);
        string str2 = "";
        int s2 = 31 - end2, e2 = 31 - start2;
        for(int i = s2; i <= e2; i++) str2.push_back(str[i]);
        
        string real = "";
        real += str1[0];
        real += str2[str2.size()-1];
        for(int i = 1; i < str1.size(); i++) real.push_back(str1[i]);
        for(int i = 0; i < str2.size()-1; i++) real.push_back(str2[i]);
        for(int i = 0; i < real.size()-1; i++) real[i] = real[i+1];
        real[real.size()-1] = '0';
        
        return real;
    }
    
    int immediate(string str){
        if(str == "") return 0;
        int inc = 1;
        int num = 0;
        for(int i = str.size()-1; i >= 1; i--){
            num += (str[i]-'0') * inc;
            inc *= 2;
        }
        if(str[0] == '1') num -= inc;
        return num;
    }
    
    int signExtended(string str){
        if(str == "") return 0;
        string num = "";
        num.push_back(str[0]);
        for(int i = 12; i <= 19; i++) num.push_back(str[i]);
        num.push_back(str[11]);
        for(int i = 1; i <= 10; i++) num.push_back(str[i]);
        for(int i = 0; i < num.size()-1; i++) num[i] = num[i+1];
        num[num.size()-1] = '0';
        return immediate(num);
    }
    
    map<string,int> controller(string str){
        map<string,int> cw = {
            {"RegRead",0},
            {"RegWrite",0},
            {"MemRead",0},
            {"MemWrite",0},
            {"Mem2Reg",0},
            {"ALUSrc",0},
            {"ALUOp",0},
            {"Branch",0},
            {"Jump",0}
        };
        
        if(str == "") return cw;
        
        if(str == "0110011"){
            cw["RegRead"] = 1;
            cw["RegWrite"] = 1;
        }
        else if(str == "0010011"){
            cw["RegRead"] = 1;
            cw["RegWrite"] = 1;
            cw["ALUSrc"] = 1;
        }
        else if(str == "0000011"){
            cw["RegRead"] = 1;
            cw["RegWrite"] = 1;
            cw["ALUSrc"] = 1;
            cw["MemRead"] = 1;
            cw["Mem2Reg"] = 1;
        }
        else if(str == "0100011"){
            cw["RegRead"] = 1;
            cw["ALUSrc"] = 1;
            cw["MemWrite"] = 1;
        }
        else if(str == "1100011"){
            cw["RegRead"] = 1;
            cw["Branch"] = 1;
        }
        else if(str == "1101111"){
            cw["RegRead"] = 1;
            cw["RegWrite"] = 1;
            cw["Jump"] = 1;
        }
        else if(str == "1100111"){
            cw["RegRead"] = 1;
            cw["RegWrite"] = 1;
            cw["ALUSrc"] = 1;
            cw["Jump"] = 1;
        }
        
        return cw;
    }
    
    int ALU(string op, string fun3, string fun7, int rs1, int rs2, int pc, bool &ALUFlag){
        int result = 0;
        if(op == "") return result;
        
        if(op == "0110011"){
            if(fun7 == "0000000"){
                if(fun3 == "000") result = rs1 + rs2;
                else if(fun3 == "111") result = rs1 & rs2;
                else if(fun3 == "110") result = rs1 | rs2;
                else if(fun3 == "100") result = rs1 ^ rs2;
                else if(fun3 == "001") result = rs1 << rs2;
                else if(fun3 == "101") result = rs1 >> rs2;
                else if(fun3 == "010") result = rs1 > rs2;
            }
            else if(fun7 == "0100000"){
                if(fun3 == "000") result = rs1 - rs2;
            }
            else if(fun7 == "0000001"){
                if(fun3 == "000") result = rs1 * rs2;
                else if(fun3 == "100") result = rs1 / rs2;
                else if(fun3 == "110") result = rs1 % rs2;
            }
        }
        else if(op == "0010011"){
            if(fun3 == "000") result = rs1 + rs2;
            else if(fun3 == "100") return rs1 ^ rs2;
            else if(fun3 == "110") return rs1 | rs2;
            else if(fun3 == "111") return rs1 & rs2;
            else if(fun3 == "010") return rs1 > rs2;
        }
        else if(op == "0000011"){
            result =  rs1 + rs2;                                // -----------------------------------------
        }
        else if(op == "0100011"){
            result = rs1 + rs2;                                 // -----------------------------------------
        }
        else if(op == "1100011"){
            if(fun3 == "000") ALUFlag = (rs1 == rs2);
            else if(fun3 == "001") ALUFlag = (rs1 != rs2);
            else if(fun3 == "100") ALUFlag = (rs1 < rs2);
            else if(fun3 == "101") ALUFlag = (rs1 >= rs2);
        }
        else if(op == "1101111"){
            return pc;
        }
        else if(op == "1100111"){
           return pc;
        }
        
        return result;
    }
    
    bool hold(string rs1, string rs2, string op){
        if(op == "0110011"){
            return stall[rs2] or stall[rs1];
        }
        else if(op == "0010011"){
            return stall[rs1];
        }
        else if(op == "0000011"){
            return stall[rs1];
        }
        else if(op == "0100011"){
            return stall[rs2] or stall[rs1];
        }
        else if(op == "1100011"){
            return stall[rs2] or stall[rs1];
        }
        else if(op == "1100111"){
           return stall[rs1];
        }
        else return false;
    }
    
    void writeReg(string rdl, string op){
        if(op == "0110011"){
            stall[rdl]++;
        }
        else if(op == "0010011"){
            stall[rdl]++;
        }
        else if(op == "0000011"){
            stall[rdl]++;
        }
        else if(op == "1100111"){
            stall[rdl]++;
        }
    }
    
    void flush1(_IFID* IFID){
        IFID->DPC = 0, IFID->NPC = 0;
        IFID->IR = "";
        IFID->complete = false;
    }
    
    void flush2(_IDEX* IDEX){
        IDEX->JPC = 0, IDEX->DPC = 0, IDEX->NPC = 0;
        IDEX->rs1 = 0, IDEX->rs2 = 0, IDEX->SDValue = 0;
        IDEX->rdl = "", IDEX->fun3 = "", IDEX->fun7 = "", IDEX->imm = "", IDEX->op = "";
        IDEX->complete = false;
        IDEX->CW = {
            {"RegRead",0},
            {"RegWrite",0},
            {"MemRead",0},
            {"MemWrite",0},
            {"Mem2Reg",0},
            {"ALUSrc",0},
            {"ALUOp",0},
            {"Branch",0},
            {"Jump",0}
        };
    }
    
    void instFetch(_PC* PC, _IFID* IFID){
        if(PC->complete) return;
        if(PC->halt){
            flush1(IFID);
            return;
        }
        if((PC->pc)/4 >= IM.size()){                  // -----------------------------
            PC->complete = true;
            return;
        }
        IFID->IR = IM[(PC->pc)/4];
        IFID->DPC = PC->pc;
        IFID->NPC = PC->pc + 4;
        string op = extract(IFID->IR,6,0);
        if(op == "1100011" or op == "1100111" or op == "1101111") PC->halt = true;
        else PC->pc = PC-> pc + 4;                       // -----------------------
        if((PC->pc)/4 >= IM.size()) PC->complete = true; // ----------------------
    }
    
    int instDecode(_IFID* IFID, _IDEX* IDEX, _PC* PC){
        if(IFID->complete) return 0;
        if(hold(extract(IFID->IR,19,15),extract(IFID->IR,24,20),extract(IFID->IR,6,0))){
            flush2(IDEX);
            return 1;
        }
        if(IFID->IR != "") instructions++; 
        writeReg(extract(IFID->IR,11,7),extract(IFID->IR,6,0));
        IDEX->JPC = IFID->DPC + signExtended(extract(IFID->IR,31,12));      // --------------------------------------
        IDEX->DPC = IFID->DPC;
        IDEX->NPC = IFID->NPC;
        IDEX->imm = extractB(IFID->IR,31,25,11,7);
        IDEX->fun3 = extract(IFID->IR,14,12);
        IDEX->fun7 = extract(IFID->IR,31,25);
        IDEX->rdl = extract(IFID->IR,11,7);
        IDEX->SDValue = (IFID->IR != "") ? GPR[extract(IFID->IR,24,20)] : 0;
        IDEX->op = extract(IFID->IR,6,0);
        IDEX->CW = controller(extract(IFID->IR,6,0));
        if(IDEX->CW["RegRead"]) IDEX->rs1 = GPR[extract(IFID->IR,19,15)];
        if(IDEX->CW["ALUSrc"]){
            if(IDEX->CW["RegRead"]){
                if(IDEX->op == "0100011") IDEX->rs2 = immediate(extractB(IFID->IR,31,25,11,7));
                else IDEX->rs2 = immediate(extract(IFID->IR,31,20));
            }
        }
        else{
            if(IDEX->CW["RegRead"]) IDEX->rs2 = GPR[extract(IFID->IR,24,20)];
        }
        if(PC->complete) IFID->complete = true;
        return 0;
    }
    
    void instExecution(_IDEX* IDEX, _EXMO* EXMO, _PC *PC, _IFID* IFID){
        if(IDEX->complete) return;
        bool ALUFlag = true;
        EXMO->ALUOUT = ALU(IDEX->op,IDEX->fun3,IDEX->fun7,IDEX->rs1,IDEX->rs2,IDEX->NPC,ALUFlag);
        EXMO->CW = IDEX->CW;
        EXMO->SDValue = IDEX->SDValue;
        EXMO->rdl = IDEX->rdl;
        if(IDEX->op == "1100011" or IDEX->op == "1100111" or IDEX->op == "1101111"){
            PC->halt = false;
            if(IDEX->CW["Branch"] and ALUFlag) PC->pc = IDEX->DPC + immediate(IDEX->imm);
            else if(IDEX->CW["Jump"]){                                                        // -----------------------------
                if(IDEX->op == "1100111") PC->pc =  IDEX->rs1 + IDEX->rs2;                    // --------------------------------
                else PC->pc = IDEX->JPC;
            }
            else PC->pc = IDEX->DPC + 4;                                                      // -------------------------------
        }
        if(IFID->complete) IDEX->complete = true;
    }
    
    void memoryAccess(_EXMO* EXMO, _MOWB* MOWB, _IDEX* IDEX){
        if(EXMO->complete) return;
        if(EXMO->CW["MemWrite"]) DM[(EXMO->ALUOUT)/4] = EXMO->SDValue;
        if(EXMO->CW["MemRead"]) MOWB->LDOUT = DM[(EXMO->ALUOUT)/4];
        MOWB->ALUOUT = EXMO->ALUOUT;
        MOWB->CW = EXMO->CW;
        MOWB->rdl = EXMO->rdl;
        if(IDEX->complete) EXMO->complete = true;
    }
    
    int registerWrite(_MOWB* MOWB, _EXMO* EXMO){
        if(MOWB->complete) return 1;
        if(MOWB->CW["RegWrite"]){
            if(stall[MOWB->rdl]) stall[MOWB->rdl]--;
            if(MOWB->CW["Mem2Reg"]) GPR[MOWB->rdl] = MOWB->LDOUT;
            else GPR[MOWB->rdl] = MOWB->ALUOUT;
        }
        if(EXMO->complete) MOWB->complete = true;
        return 0;
    }
    
    void printValues(){
        
        cout << "Number of Instructions -> " << instructions << "\n";

        cout << "-------------------- Register Values --------------------\n";
        for(auto gpr : GPR){
            cout << gpr.first << "     " << gpr.second << "\n";
        }
        cout << "\n\n\n";
        
        cout << "----------------------- Memory ---------------------------\n";
        for(auto dm : DM){
            cout << dm.first << "      " << dm.second << "\n";
        }
    }
};

int main(){
    File fl;
    vector<string> instruction = fl.readFile();
    vector<string> binary;
    Instruction ins;
    for(int i = 0; i < instruction.size(); i++){
        if(ins.setIns(instruction[i])) return -1;
        string bin = ins.getBin();
        cout << bin << "\n";
        if(bin == "NULL") return -1;
        else binary.push_back(bin);
    }
    cout << "\nCode Assembled\n";
    
    _PC* PC = new _PC();
    _IFID* IFID = new _IFID();
    _IDEX* IDEX = new _IDEX();
    _EXMO* EXMO = new _EXMO();
    _MOWB* MOWB = new _MOWB();

    int cycles = 0;
    
    Pipeline P(binary);
    while(true){
        cycles++;
        if(P.registerWrite(MOWB,EXMO)) break;
        P.memoryAccess(EXMO,MOWB,IDEX);
        P.instExecution(IDEX,EXMO,PC,IFID);
        if(P.instDecode(IFID,IDEX,PC)) continue;
        P.instFetch(PC,IFID);
    }

    cout << "Number of cycles -> " << cycles << "\n";
    P.printValues();

    return 0;
}
