#include <iostream>
#include <math.h>
//#include "libs.h"
#include "libs2.h"
//#include <emmintrin.h>
#include <ctime>
/*
void normal(float* a, int N)                                                                                                                                                                                     
{                                                                                                                                                                                                                
  for (int i = 0; i < N; ++i)                                                                                                                                                                                    
    a[i] = sqrt(a[i]);                                                                                                                                                                                           
}                                                                                                                                                                                                                
 
void sse(float* a, int N)                                                                                                                                                                                        
{                      
  // We assume N % 4 == 0.                                                                                                                                                                                        
  int nb_iters = N / 4;                                                                                                                                                                                         
  __m128* ptr = (__m128*)a;                                                                                                                                                                                      
 
  for (int i = 0; i < nb_iters; ++i, ++ptr, a += 4)                                                                                                                                                              
    _mm_store_ps(a, _mm_sqrt_ps(*ptr));                                                                                                                                                                          
}
*/
int main(void)
{

// creation de deux vecteurs a et b
    
    
  //ad::ad_value a =ad::ad_value( /* v */ 3.14, 3,1 ); // v est la valeur de a et dv c'est la valeur de la dérivé par rapport aux autres var
  //ad::ad_value b =ad::ad_value( /* v */ 1., 3,2 ); // mm chose !

// tests avec plusieurs fonctions complexes
/*
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

//impression des résultats
    /*
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
    //*/
//resultats tests d'implémentation

  /*      
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
    
    
//*/

  // Vous pouvez remplacer par une fonction plus compliquée
  // avec des cos, exp, etc. Attention de bien connaitre le
  //minimum toutefois :)
    
    int nb_values=1000;
    ad2::ad_value vals[nb_values];
    for(int i=0;i<nb_values;i++){
        vals[i]=ad2::ad_value( /* v */ 3.14, nb_values,i );
    }
    
    auto expr=vals[0]*vals[1]*vals[2]*vals[3]*vals[4]*vals[5]*vals[6]*vals[7]*vals[8]*vals[9]*vals[10]*vals[11]*vals[12]*vals[13]*vals[14]*vals[15]*vals[16]*vals[17]*vals[18]*vals[19]*vals[20]*vals[21]*vals[22]*vals[23]*vals[24]*vals[25]*vals[26]*vals[27]*vals[28]*vals[29]*vals[30]*vals[31]*vals[32]*vals[33]*vals[34]*vals[35]*vals[36]*vals[37]*vals[38]*vals[39]*vals[40]*vals[41]*vals[42]*vals[43]*vals[44]*vals[45]*vals[46]*vals[47]*vals[48]*vals[49];
    double duration2;
    std::clock_t start2;
    duration2=0;
    start2 = std::clock();
    for(int i =0;i<10000;i++){
	
        expr.gradient();
    }
    duration2 += ( std::clock() - start2 ) ;


    //std::cout<<"printf: "<< duration2 / (double) CLOCKS_PER_SEC <<'\n';
     /*                  
 
  float* a;                        
  posix_memalign((void**)&a, 16,  N * sizeof(float));
 
  for (int i = 0; i < N; ++i)
    a[i] = 3141592.65358;
  {
    std::clock_t topstart;
    double duration;
    topstart = std::clock();

    normal(a, N);
                             

duration = ( std::clock() - topstart ) / (double) CLOCKS_PER_SEC;

    std::cout<<"printf: "<< duration <<'\n';
                                                                                                                                                                                  
 }
 for(int j=0;i<100){
	 for (int i = 0; i < N; ++i)
    	{
        	a[i] = 3141592.65358;
        std::clock_t start1;ui
        double duration1;
        start1 = std::clock();
        sse(a, N);
        duration1 = ( std::clock() - start1 ) / (double) CLOCKS_PER_SEC;

        std::cout<<"printf: "<< duration1 <<'\n';
    }
}
    //*/
    return 0;

}

