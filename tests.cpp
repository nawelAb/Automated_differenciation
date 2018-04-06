#include <iostream>
#include <math.h>
#include <mpi.h>
#include "libs.h"


int main(void)
{
int rk, jeton, tag1;
    MPI_Status sta;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rk);

    tag1 = 1000;
    if (rk == 0)
    {
        jeton = 10;
        MPI_Send(&jeton, 1, MPI_INT, 1, tag1, MPI_COMM_WORLD);
    }
    else if (rk == 1)
    {
        MPI_Recv(&jeton, 1, MPI_INT, 0, tag1, MPI_COMM_WORLD, &sta);

        printf("Je suis P%d et j'ai recu la valeur %d\n", rk, jeton);
    }

    MPI_Finalize();

// creation de deux vecteurs a et b

  ad::ad_value a =ad::ad_value( /* v */ 3.14, 3,1 ); // v est la valeur de a et dv c'est la valeur de la dérivé par rapport aux autres var
  ad::ad_value b =ad::ad_value( /* v */ 1., 3,2 ); // mm chose !

// tests avec plusieurs fonctions complexes

  auto expr11 = ad::puis(ad::exp(ad::sin(a)),0.5);
  auto expr12 = 3.0*ad::puis(a,2.)-b;
  auto expr13 = 2.0*b-a;
  auto expr14 = ad::puis(ad::sin(a),6.);
  auto expr15 = (ad::sin(a)+3.)/ad::exp((ad::puis(a,2.))+5.);
  auto expr16 = ad::exp(a);
  auto expr17 = ad::sin(a);
  auto expr18 = ad::puis(a,14.);
  auto expr19 = a / 1.;
  auto expr20 = a*b*a*b*3.0;
  auto expr21 = a+a+a;
  auto expr22 = a-b-a-b;
  auto expr23 = a/b; 
 
// tests d'implémentation

  auto exprt1 = a / b;
  auto exprt2 = a + b;
  auto exprt3 = a - b;
  auto exprt4 = a * b;
  auto exprt5 =   - a;
  auto exprt6 = 1. - a;
  auto exprt7 = a - 1.;
  auto exprt8 = 1. + a;
  auto exprt9 = a + 1.;
  auto exprt10 = 1. * a;
  auto exprt11 = a * 1.;
  auto exprt12 = 1. / a;
  auto exprt13 = a / 1.;

//impression des rédultats

  std::cout << "puis(exp(sin(a)),0.5)" << std::endl;
  std::cout << expr11.value() << std::endl;
  std::cout << expr11.gradient(0) << std::endl; // derivé de expr /a
  std::cout << expr11.gradient(1) << std::endl; // derivé de expr /b
  std::cout << expr11.gradient(2) << std::endl<< std::endl; // derivé de expr /c

  std::cout << "3.0*puis(a,2.)-b" << std::endl;
  std::cout << expr12.value() << std::endl;
  std::cout << expr12.gradient(0) << std::endl; // derivé de expr /a
  std::cout << expr12.gradient(1) << std::endl; // derivé de expr /b
  std::cout << expr12.gradient(2) << std::endl<< std::endl; // derivé de expr /c

  std::cout << "2.0*b-a" << std::endl;
  std::cout << expr13.value() << std::endl;
  std::cout << expr13.gradient(0) << std::endl; // derivé de expr /a
  std::cout << expr13.gradient(1) << std::endl; // derivé de expr /b
  std::cout << expr13.gradient(2) << std::endl<< std::endl; // derivé de expr /c

  std::cout << "puis(sin(a),6.)" << std::endl;
  std::cout << expr14.value() << std::endl;
  std::cout << expr14.gradient(0) << std::endl; // derivé de expr /a
  std::cout << expr14.gradient(1) << std::endl; // derivé de expr /b
  std::cout << expr14.gradient(2) << std::endl<< std::endl; // derivé de expr /c

  std::cout << "(sin(a)+3.)/exp((puis(a,2.))+5.)" << std::endl;
  std::cout << expr15.value() << std::endl;
  std::cout << expr15.gradient(0) << std::endl; // derivé de expr /a
  std::cout << expr15.gradient(1) << std::endl; // derivé de expr /b
  std::cout << expr15.gradient(2) << std::endl<< std::endl; // derivé de expr /c

  std::cout << "ad::exp(a)" << std::endl;
  std::cout << expr16.value() << std::endl;
  std::cout << expr16.gradient(0) << std::endl; // derivé de expr /a
  std::cout << expr16.gradient(1) << std::endl; // derivé de expr /b
  std::cout << expr16.gradient(2) << std::endl<< std::endl; // derivé de expr /c

  std::cout << "sin(a)" << std::endl;
  std::cout << expr17.value() << std::endl;
  std::cout << expr17.gradient(0) << std::endl; // derivé de expr /a
  std::cout << expr17.gradient(1) << std::endl; // derivé de expr /b
  std::cout << expr17.gradient(2) << std::endl<< std::endl; // derivé de expr /c

  std::cout << "puis(a,14.)" << std::endl;
  std::cout << expr18.value() << std::endl;
  std::cout << expr18.gradient(0) << std::endl; // derivé de expr /a
  std::cout << expr18.gradient(1) << std::endl; // derivé de expr /b
  std::cout << expr18.gradient(2) << std::endl<< std::endl; // derivé de expr /c

  std::cout << "a/1." << std::endl;
  std::cout << expr19.value() << std::endl;
  std::cout << expr19.gradient(0) << std::endl; // derivé de expr /a
  std::cout << expr19.gradient(1) << std::endl; // derivé de expr /b
  std::cout << expr19.gradient(2) << std::endl<< std::endl; // derivé de expr /c

  std::cout << "a*b*a*b*3.0" << std::endl;
  std::cout << expr20.value() << std::endl;
  std::cout << expr20.gradient(0) << std::endl; // derivé de expr /a
  std::cout << expr20.gradient(1) << std::endl; // derivé de expr /b
  std::cout << expr20.gradient(2) << std::endl<< std::endl; // derivé de expr /c

  std::cout << "a+a+a" << std::endl;
  std::cout << expr21.value() << std::endl;
  std::cout << expr21.gradient(0) << std::endl; // derivé de expr /a
  std::cout << expr21.gradient(1) << std::endl; // derivé de expr /b
  std::cout << expr21.gradient(2) << std::endl<< std::endl; // derivé de expr /c

  std::cout << "a-b-a-b" << std::endl;
  std::cout << expr22.value() << std::endl;
  std::cout << expr22.gradient(0) << std::endl; // derivé de expr /a
  std::cout << expr22.gradient(1) << std::endl; // derivé de expr /b
  std::cout << expr22.gradient(2) << std::endl<< std::endl; // derivé de expr /c

  std::cout << "a/b" << std::endl;
  std::cout << expr23.value() << std::endl;
  std::cout << expr23.gradient(0) << std::endl; // derivé de expr /a
  std::cout << expr23.gradient(1) << std::endl; // derivé de expr /b
  std::cout << expr23.gradient(2) << std::endl<< std::endl; // derivé de expr /c

//resultats tests d'implémentation

  std::cout << "a/b" << std::endl;
  std::cout << exprt1.value() << std::endl;
  std::cout << exprt1.gradient(0) << std::endl; // derivé de expr /a
  std::cout << exprt1.gradient(1) << std::endl; // derivé de expr /b
  std::cout << exprt1.gradient(2) << std::endl<< std::endl; // derivé de expr /c

  std::cout << "a+b" << std::endl;
  std::cout << exprt2.value() << std::endl;
  std::cout << exprt2.gradient(0) << std::endl; // derivé de expr /a
  std::cout << exprt2.gradient(1) << std::endl; // derivé de expr /b
  std::cout << exprt2.gradient(2) << std::endl<< std::endl; // derivé de expr /c

  std::cout << "a-b" << std::endl;
  std::cout << exprt3.value() << std::endl;
  std::cout << exprt3.gradient(0) << std::endl; // derivé de expr /a
  std::cout << exprt3.gradient(1) << std::endl; // derivé de expr /b
  std::cout << exprt3.gradient(2) << std::endl<< std::endl; // derivé de expr /c
  
  std::cout << "a*b" << std::endl;
  std::cout << exprt4.value() << std::endl;
  std::cout << exprt4.gradient(0) << std::endl; // derivé de expr /a
  std::cout << exprt4.gradient(1) << std::endl; // derivé de expr /b
  std::cout << exprt4.gradient(2) << std::endl<< std::endl; // derivé de expr /c

  std::cout << "-a" << std::endl;
  std::cout << exprt5.value() << std::endl;
  std::cout << exprt5.gradient(0) << std::endl; // derivé de expr /a
  std::cout << exprt5.gradient(1) << std::endl; // derivé de expr /b
  std::cout << exprt5.gradient(2) << std::endl<< std::endl; // derivé de expr /c

  std::cout << "1-a" << std::endl;
  std::cout << exprt6.value() << std::endl;
  std::cout << exprt6.gradient(0) << std::endl; // derivé de expr /a
  std::cout << exprt6.gradient(1) << std::endl; // derivé de expr /b
  std::cout << exprt6.gradient(2) << std::endl<< std::endl; // derivé de expr /c

  std::cout << "a-1" << std::endl;
  std::cout << exprt7.value() << std::endl;
  std::cout << exprt7.gradient(0) << std::endl; // derivé de expr /a
  std::cout << exprt7.gradient(1) << std::endl; // derivé de expr /b
  std::cout << exprt7.gradient(2) << std::endl<< std::endl; // derivé de expr /c

  std::cout << "1+a" << std::endl;
  std::cout << exprt8.value() << std::endl;
  std::cout << exprt8.gradient(0) << std::endl; // derivé de expr /a
  std::cout << exprt8.gradient(1) << std::endl; // derivé de expr /b
  std::cout << exprt8.gradient(2) << std::endl<< std::endl; // derivé de expr /c

  std::cout << "a+1" << std::endl;
  std::cout << exprt9.value() << std::endl;
  std::cout << exprt9.gradient(0) << std::endl; // derivé de expr /a
  std::cout << exprt9.gradient(1) << std::endl; // derivé de expr /b
  std::cout << exprt9.gradient(2) << std::endl<< std::endl; // derivé de expr /c

  std::cout << "1*a" << std::endl;
  std::cout << exprt10.value() << std::endl;
  std::cout << exprt10.gradient(0) << std::endl; // derivé de expr /a
  std::cout << exprt10.gradient(1) << std::endl; // derivé de expr /b
  std::cout << exprt10.gradient(2) << std::endl<< std::endl; // derivé de expr /c

  std::cout << "a*1" << std::endl;
  std::cout << exprt11.value() << std::endl;
  std::cout << exprt11.gradient(0) << std::endl; // derivé de expr /a
  std::cout << exprt11.gradient(1) << std::endl; // derivé de expr /b
  std::cout << exprt11.gradient(2) << std::endl<< std::endl; // derivé de expr /c
  
  std::cout << "1/a" << std::endl;
  std::cout << exprt12.value() << std::endl;
  std::cout << exprt12.gradient(0) << std::endl; // derivé de expr /a
  std::cout << exprt12.gradient(1) << std::endl; // derivé de expr /b
  std::cout << exprt12.gradient(2) << std::endl<< std::endl; // derivé de expr /c

  std::cout << "a/1" << std::endl;
  std::cout << exprt13.value() << std::endl;
  std::cout << exprt13.gradient(0) << std::endl; // derivé de expr /a
  std::cout << exprt13.gradient(1) << std::endl; // derivé de expr /b
  std::cout << exprt13.gradient(2) << std::endl<< std::endl; // derivé de expr /c
}
