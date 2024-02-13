# Cyberpunk 2077 Breach Protocol dengan Brute Force
IF 2211 - Tugas Kecil 01 Strategi Algoritma

## Table of Contents

- [General Info](#general-information)
- [Game Concepts](#game-concepts)
- [Prerequisites](#prerequisites)
- [Installation](#insatllation)
- [Programming Language Used](#languages)
- [Links](#links)

## General Information <a name="general-information"></a>
Cyberpunk 2077 Breach Protocol adalah minigame meretas pada permainan video Cyberpunk 2077. Minigame ini merupakan simulasi peretasan jaringan local dari ICE (Intrusion Counter-Measures Electronics) pada permainan Cyberpunk 2077. Diberikan suatu matriks dengan token-token unik, dan sekuens-sekuens berhadiah dengan hadiah poin masing-masing, serta ukuran maksimal buffer, kita diminta untuk mencari kombinasi isi buffer yang memberikan poin total maksimal. Pada repositori ini, akan diselesaikan permainan Breach Protocol ini dengan menggunakan pendekatan algoritma Brute Force.

## Prerequisites
Untuk menjalankan projek ini, diperlukan penginstalan: 
- `GNU GCC` dimana berupa compiler C++. Tahapan penginstalannya adalah sebagai berikut.
1. Linux
   - Jalankan beberapa command ini pada terminal anda
```
sudo apt-get update
sudo apt-get install gcc
sudo apt-get install g++
sudo apt-get install build-essential
```

2. Windows
   - Download executable file di [sini](https://www.msys2.org/)
   - Setelah download selesai, double klik executable file. Kemudian klik next
   - Selesaikan proses instalasi
   - Buka terminal MSYS2 MSYS, dan apply command `pacman -Syu` untuk mengupdate package database
   - Kemudian buka kembali terminalnya dan update sisa paket dengan command `pacman -Su`
   - Jalankan command `pacman -S mingw-w64-x86_64-gcc`

## Installation
1. Clone repository :
```shell
git clone https://github.com/chankiel/Tucil1_13522029.git
```

2. Masuk pada path:
```shell
cd  src
```

3. Pada terminal anda, jalankan command berikut untuk mengkompilasi program
```
g++ -o main main.cpp
```

4. Jika ingin melakukan pembacaan dari file,s iapkan file .txt terlebih dahulu sebagai tempat info permainan. Simpan file dengan format sebagai berikut.
```
buffer_size
matrix_width matrix_height
matrix
number_of_sequences
sequences_1
sequences_1_reward
sequences_2
sequences_2_reward
…
sequences_n
sequences_n_reward
```

4. Kemudian jalankan executable filenya
```
./main
```

## Programming Languages Used <a name="languages"></a>
- C++

## Links
- Repository : https://github.com/chankiel/Tucil1_13522029
- Issue tracker :
   - If you encounter any issues with the program, come across any disruptive bugs, or have any suggestions for improvement, please don't hesitate to reach out by sending messages to our contributors social media. Your feedback is greatly appreciated.
- Github main contributor : 
  Ignatius Jhon Hezkiel Chan 
  13522029 
  https://github.com/chankiel