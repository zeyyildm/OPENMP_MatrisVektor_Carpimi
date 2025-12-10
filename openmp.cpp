// y = A . x
//A: M * N boyutlu rastgele sayılardan oluşan matris
// x: N boyutlu rastgele sayılardan oluşan vektör
// y: M boyutlu çıktı vektörü
#include <iostream> //kullanıcıdan veri almak ve ekrana yazı yazdırmak için
#include <vector> //matris ve vektörler için
#include <cstdlib> //rand() için
#include <ctime>
#include <omp.h> //seri bile olsa bununla zaman ölçebiliriz
#include <cmath> //fabs kullanabilmek için

int main(int ac, char *av[]) //thread sayılarını argüman olarak alacağız
{
    if(ac < 2)
    {
        std::cerr << "Programı adı zaten 1 argüman. Thread sayısını doğru girmediniz"  ;
        return (1);
    }

    int num_threads = std:: atoi(av[1]); //atoi string to integer
    if(num_threads <= 0)
    {
        std::cerr << "Gecerli bir thread sayisi verin" ;
        return (1);
    }
    std::cout << "Kullanilan thread sayisi: " << num_threads << "\n";
    //kullanıcıdan matris boyutlarını almalıyız
    int M, N;
    std::cout << "Matris boyutlarını giriniz: " ;
    std::cin >> M >> N;

    if(M <= 0 || N <= 0){ //negatif matris değeri girildiğinde
        std::cerr << "Pozitif degerler giriniz\n" ; //cerr = hata mesajları
        return (1); //programı bitirmek için return
    }

// M * N matris oluşturma
std::vector<std::vector<double>> A(M, std::vector<double>(N)); //M tane satır oluşturulur. Her satırda N tane double değer oluşturulurç
std::vector<double> x(N); //N boyutlu vektör oluşturma
std::vector<double> y_serial(M); //M boyutlu çıkış vektörü oluşturma
std::vector<double> y_parallel(M); //M boyutlu çıkış vektörü oluşturma

//matrisi rastgele sayılarla doldurma
std::srand(std::time(nullptr)); //her çalıştırmada farklı random sayılar gelmesi için

for(int i = 0; i < M; i++) //matris doldurma döngüsü
    for(int j = 0; j < N; j++)
        A[i][j] = std::rand() % 10; //rand çok büyük sayı üretir %10 ile 0-9 arasında rakam gelmesini sağlıyoruz
for(int j = 0; j < N; j++) //vektör doldurma döngüsü
    x[j] = std::rand() % 10;

//SERİ KISIM
double start_serial = omp_get_wtime();

for (int i = 0; i < M; i++){ //her satır için (M) çarpım yapılıp yeni bir y üretilecek
    y_serial[i] = 0.0; //başlangıç değeri atandı
    for(int j = 0; j < N; j++){
        y_serial[i] += A[i][j] * x[j]; //çarpım
    }
}
double end_serial = omp_get_wtime();
double T_serial = end_serial - start_serial;
std::cout << "Seri çarpım için carpim süresi: " << end_serial - start_serial << " saniyedir\n";

//PARALEL KISIM

omp_set_num_threads(num_threads); //bu kadar işçi thread oluşturulur

for(int i = 0; i < M; i++)
    y_parallel[i] = 0.0;

double start_parallel = omp_get_wtime();

#pragma omp parallel for //sayesinde i threadler arasında bölüştürülür
for(int i = 0; i < M; i++){
    double sum = 0.0; //sum döngü içinde olduğundan her threadin kendi local sumı var race condition yok
    for(int j = 0; j < N ; j++)
        sum += A[i][j] * x[j]; //her thread kendi i'leri için sum hesaplar.
    y_parallel[i] = sum; //her thread kendi sumını genel toplama ekler
}
double end_parallel = omp_get_wtime();

//paralel ve seri sonuçları aynı çıkıyor mu?
bool same = true; //başlangıçta doğru sayıyoruz
for(int i = 0; i < M; i++){
    if(std::fabs(y_parallel[i] - y_serial[i]) > 0.000001){ //fabs mutlak değer için kullanılır
        same = false;
        break; //döngüyü kırmak için
    }
}

if(same == true)
    std::cout << "Paralel ve seri sonuç aynı.\n"; 

double T_parallel = end_parallel - start_parallel;
std::cout << "Paralel carpim suresi: " <<   T_parallel << " saniye\n";
std::cout <<  "Basic paralelleştirme için speedup: " << T_serial / T_parallel << "\n";
return (0);

}