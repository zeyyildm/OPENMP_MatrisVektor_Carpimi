// y = A . x
//A: M * N boyutlu rastgele sayılardan oluşan matris
// x: N boyutlu rastgele sayılardan oluşan vektör
// y: M boyutlu çıktı vektörü
#include <iostream> //kullanıcıdan veri almak ve ekrana yazı yazdırmak için
#include <vector> //matris ve vektörler için
#include <cstdlib> //rand() için
#include <ctime>
#include <omp.h> //seri bile olsa bununla zaman ölçebiliriz

int main()
{
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
std::vector<double> y(M); //M boyutlu çıkış vektörü oluşturma

//matrisi rastgele sayılarla doldurma
std::srand(std::time(nullptr)); //her çalıştırmada farklı random sayılar gelmesi için

for(int i = 0; i < M; i++) //matris doldurma döngüsü
    for(int j = 0; j < N; j++)
        A[i][j] = std::rand() % 10; //rand çok büyük sayı üretir %10 ile 0-9 arasında rakam gelmesini sağlıyoruz
for(int j = 0; j < N; j++) //vektör doldurma döngüsü
    x[j] = std::rand() % 10;


double start = omp_get_wtime();

for (int i = 0; i < M; i++){ //her satır için (M) çarpım yapılıp yeni bir y üretilecek
    y[i] = 0.0; //başlangıç değeri atandı
    for(int j = 0; j < N; j++){
        y[i] += A[i][j] * x[j]; //çarpım
    }
}
double end = omp_get_wtime();
std::cout << "Seri çarpım için carpim süresi: " << end - start << " saniyedir\n";

return (0);

}
