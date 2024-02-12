#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <string>
using namespace std;
using namespace std::chrono;

/*------CYBERPUNK 2077 BREACH PROTOCOL-----*/

// Matriks boolean visited
struct StatusVisit{
    bool **visited;
};

// Struct koordinat pada matriks
struct Point{
    int x;
    int y;
};

/*Variabel Global :
    Integer:
    1. maxPoin  : nilai reward maksimal sementara
    2. maxBuffer: nilai maksimal isi buffer
    3. nReward  : banyak sekuens sebagai reward
    4. listPoin : array berisi reward-reward dari sekuens
    5. mtrxWidth: lebar matriks permainan (kolom)
    6. mtrxHeight: tinggi matriks permainan (baris)
    7. curMaxLength: panjang sekuens maksimal sementara
    8. exeTime  : waktu eksekusi program

    String:
    1. maxSequence  : sekuens maksimal sementara / isi buffer maksimal sementara
    2. rewardSeq    : array berisi sekuens-sekuens reward
    3. matrix       : matrix permainan

    vector:
    1. maxPoint     : vector (array dinamis) untuk menyimpan tahap-tahapan koordinat maksimal

*/
int maxPoin = -9999, maxBuffer, nReward, *listPoin, mtrxWidth, mtrxHeight,curMaxLength=0, exeTime;
string maxSequence, *rewardSeq, **matrix;
vector<Point> maxPoint;

/* ------------PEMBACAAN INFORMASI PERMAINAN----------------- */

// Pembacaan dari File
void readMatrixFile(ifstream& inFile){
    matrix = new string*[mtrxHeight];
    for(int i=0;i<mtrxHeight;i++){
        matrix[i] = new string[mtrxWidth];
        for(int j=0;j<mtrxWidth-1;j++){
            getline(inFile,matrix[i][j],' ');
        }
        getline(inFile,matrix[i][mtrxWidth-1]);
    }
}

void readFile(string fileName){
    ifstream inFile;
    string line;
    inFile.open(fileName);
    getline(inFile,line);
    maxBuffer = stoi(line);
    getline(inFile,line,' ');
    mtrxWidth = stoi(line);
    getline(inFile,line);
    mtrxHeight = stoi(line);

    readMatrixFile(inFile);
    getline(inFile,line);
    nReward = stoi(line);
    rewardSeq = new string[nReward];
    listPoin = new int[nReward];
    for(int i=0;i<nReward;i++){
        getline(inFile,line);
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        rewardSeq[i] = line;
        getline(inFile,line);
        listPoin[i] = stoi(line);
    }
}

// Randomize informasi Permainan
void randomizeMatrix(int jmlhToken,string token[]){
    srand((unsigned)time(NULL));
    matrix = new string*[mtrxHeight];
    for(int i=0;i<mtrxHeight;i++){
        matrix[i] = new string[mtrxWidth];
        for(int j=0;j<mtrxWidth;j++){
            int idx = rand()%jmlhToken;
            matrix[i][j] = token[idx];
        }
    }
}

void randomizeSequence(int jmlhToken,string token[],int maxSizeSeq){
    srand((unsigned)time(NULL));
    rewardSeq = new string[nReward];
    listPoin = new int[nReward];
    for(int i=0;i<nReward;i++){
        listPoin[i] = 10 + rand()%91;
        rewardSeq[i]=token[rand()%jmlhToken];
        int sizeSeq = 2 + (rand()%(maxSizeSeq-1));
        for(int j=1;j<sizeSeq;j++){
            rewardSeq[i]+=token[rand()%jmlhToken];
        }
    }
}

void readRandom(){
    int jmlhToken,maxSizeSeq;
    cout<<"Masukkan jumlah token unik: ";
    cin>>jmlhToken;
    string token[jmlhToken];
    cout<<"Masukkan token-token permainan: ";
    for(int i=0;i<jmlhToken;i++){
        cin>>token[i];
    }

    cout<<"Masukkan ukuran buffer: ";
    cin>>maxBuffer;
    cout<<"Masukkan ukuran matrix (baris dan kolom): ";
    cin>>mtrxHeight>>mtrxWidth;
    cout<<"Masukkan jumlah sekuens: ";
    cin>>nReward;
    cout<<"Masukkan ukuran maksimal sekuens: ";
    cin>>maxSizeSeq;

    randomizeMatrix(jmlhToken,token);
    randomizeSequence(jmlhToken,token,maxSizeSeq);
}

/* -----------ALGORITMA BRUTE FORCE--------------- */

// Algoritma string matching, mencari apakah target ada pada seq
bool findSeq(string seq, string target){
    if(seq.length()<target.length()) return false;
    int targetLength = target.length(),endLim = seq.length()-targetLength,i=0;
    bool found = false;
    while(!found && i<=endLim){
        int j=0;
        bool match = true;
        while(match && j<targetLength){
            if(seq[i+j]!=target[j]){
                match = false;
            }
            j++;
        }
        if(match) found = true;
        i++;
    }
    return found;
}

// Menghitung total reward dari isi buffer seq
int countSeq(string seq){
    int bonus = 0;
    bool foundMatch = false;
    for(int i=0;i<nReward;i++){
        if(findSeq(seq,rewardSeq[i])){
            foundMatch = true;
            bonus += listPoin[i];
        }
    }
    if(!foundMatch) return -9999;
    return bonus;
}

// Inisialisasi Matrix visited
void initVisited(StatusVisit *stat){
    stat->visited = new bool*[mtrxHeight];
    for(int i = 0; i < mtrxHeight; i++) {
        stat->visited[i] = new bool[mtrxWidth];
        for(int j = 0; j < mtrxWidth; j++) {
            stat->visited[i][j] = false;
        }
    }
}

// Brute Force rekursif untuk mencari semua kemungkinan solusi
void searchSol(string seq,int x,int y,int buffer,StatusVisit mat,bool horizontal,vector<Point> points){
    points.push_back({x+1,y+1});
    int curBonus = countSeq(seq);
    if(curBonus>maxPoin || (curBonus==maxPoin && seq.length()<curMaxLength)){
        maxPoin = curBonus;
        maxSequence = seq;
        maxPoint = points;
        curMaxLength = seq.length();
    }
    if(buffer==maxBuffer) return;
    if(horizontal){
        for(int i=0;i<mtrxWidth;i++){
            if(!mat.visited[y][i]){
                string temp = seq+matrix[y][i];
                mat.visited[y][i]=true;
                searchSol(temp,i,y,buffer+1,mat,false,points);
                mat.visited[y][i]=false;
            }
        }
    }else{
        for(int i=0;i<mtrxHeight;i++){
            if(!mat.visited[i][x]){
                string temp = seq+matrix[i][x];
                mat.visited[i][x]=true;
                searchSol(temp,x,i,buffer+1,mat,true,points);
                mat.visited[i][x]=false;
            }
        }
    }
}

// Initiate rekursif bruteforce
void bruteForceAlgo(){
    StatusVisit stat;
    vector<Point> points;
    initVisited(&stat);
    auto start = high_resolution_clock::now();
    // Memulai eksplorasi dari seluruh tile pada matriks baris pertama
    for(int i=0;i<mtrxWidth;i++){
        stat.visited[0][i] = true;
        searchSol(matrix[0][i],i,0,1,stat,false,points);
        stat.visited[0][i] = false;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop-start);
    exeTime = duration.count();
}

// Tampilan main menu dan input
void mainMenu(){
    cout<<"Selamat datang pada Cyberpunk 2077 Breach Protocol"<<endl;
    cout<<"Tentukan tipe permainan :"<<endl;
    cout<<"1. Pembacaan informasi permainan dari file txt"<<endl;
    cout<<"2. Informasi permainan otomatis dengan masukan via CLI"<<endl;
    string tipe;
    do{
        cout<<">> ";
        cin>>tipe;
    }while(tipe!="1" && tipe!="2");

    if(tipe=="1"){
        string filename;
        cout<<"Masukkan nama file permainan: ";
        cin>>filename;
        readFile(filename);
    }else{
        readRandom();
        cout<<endl<<"Berikut matriks permainan: "<<endl;
        for(int i=0;i<mtrxHeight;i++){
            for(int j=0;j<mtrxWidth;j++){
                cout<<matrix[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<"Berikut sequens beserta bobotnya masing-masing: "<<endl;
        for(int i=0;i<nReward;i++){
            for(int j=0;j<rewardSeq[i].length();j++){
                cout<<rewardSeq[i][j];
                if(j%2==1)cout<<" ";
            }
            cout<<endl<<listPoin[i]<<endl;
        }
    }
}

// Save solusi ke file
void saveToFile(){
    string temp;
    cout<<"Apakah ingin menyimpan solusi? (y/n): ";
    do{
        cin>>temp;
    }while(temp!="y" && temp!="n");
    if(temp=="y"){
        cout<<"Masukkan nama file: ";
        cin>>temp;
        temp+=".txt";
        ofstream outFile(temp);
        if(maxPoin<0){
            outFile<<'0';
        }else{
            outFile<<maxPoin<<endl;
            outFile<<maxSequence<<endl;
            for (auto it = maxPoint.begin(); it < maxPoint.end(); it++) {
                outFile<<it->x<< " "<<it->y;
                if(it+1 != maxPoint.end()){
                    outFile<<endl;
                }
            }
        }  
    }
}

// Tampilan output result solusi
void outputResult(){
    if(maxPoin != -9999){
        for(int i=1;2*i<curMaxLength-1;i++){
            maxSequence.insert((2*i)+i-1," ");
        }
    }

    if(maxPoin == -9999){
        cout<<"Tidak ada sekuens yang berhasil didapatkan"<<endl;
        cout<<"Reward yang diterima adalah : 0"<<endl;
    }else if(maxPoin < 0){
        cout<<"Buffer yang didapat memiliki nilai terbesar: "<<maxPoin<<endl;
        cout<<"Isi buffer: "<<maxSequence<<endl;
        cout<<"Agar optimum, kita memilih opsi bahwa tidak ada sekuens yang berhasil didapatkan,"<<endl;
        cout<<"dengan nilai hadiah sebesar 0"<<endl;
    }else{
        cout<<endl<<"Reward maksimal yang didapatkan: "<<maxPoin<<endl;
        cout<<"Isi buffer: "<<maxSequence<<endl;
        cout<<"Tahapan-tahapan pemilihan kotak dalam koordinat: "<<endl;
        for (auto it = maxPoint.begin(); it != maxPoint.end(); ++it) {
            cout <<it->x<< " "<<it->y<<endl;
        }
    }
    cout<<"Waktu eksekusi program: "<<exeTime<<" ms"<<endl;
}

int main(){
    mainMenu();
    bruteForceAlgo();
    outputResult();
    saveToFile();
    cout<<"Terima kasih telah menggunakan program kami!"<<endl;
}