#include <iostream>
#include <math.h>
 

struct vector

{

  auto value() { return v; }

  const auto value() const { return v; }

 

  auto gradient(int i) { return dv[i]; }

  const auto gradient(int i) const { return dv[i]; }

 

  double v;

  double dv[3];

};

 
//structure multiplication
struct mult

{

  static auto value(double left, double right)

  {

    return left * right;

  }

 

  static auto gradient(double left, double dleft, double right, double dright)

  {

    return dleft * right + left * dright;

  }

};

//structure division
struct divs

{

  static auto value(double left, double right)

  {
    if(right!=0.)
      return left / right;

  }

 

  static auto gradient(double left, double dleft, double right, double dright)

  {
    if(right!=0.)
      return (dleft * right - left * dright)/(right*right);
    else
      return 0.;
    
  }

};

//structure addition 
struct add

{

  static auto value(double left, double right)

  {

    return left + right;

  }

 

  static auto gradient(double left, double dleft, double right, double dright)

  {

    return dleft + dright;

  }

};

//structure substraction 
struct sub

{

  static auto value(double left, double right)

  {

    return left - right;

  }

 

  static auto gradient(double left, double dleft, double right, double dright)

  {

    return dleft - dright;

  }

};

//structure puissance 
struct pui

{

  static auto value(double left, double power)

  {

    return pow(left,power);

  }

 

  static auto gradient(double left, double dleft, double power, double dright)

  {

    return power * pow(left,power-1.)*dleft;

  }

};

//structure cos 
struct cosi

{

  static auto value(double left, double power)

  {

    return cos(left);

  }

 

  static auto gradient(double left, double dleft, double power, double dright)

  {

    return dleft*sin(left);

  }

};

//structure sin 
struct sinu

{

  static auto value(double left, double power)

  {

    return sin(left);

  }

 

  static auto gradient(double left, double dleft, double power, double dright)

  {

    return -dleft*cos(left);

  }

};

//structure expo 
struct expo

{

  static auto value(double left, double power)

  {

    return exp(left);

  }

 

  static auto gradient(double left, double dleft, double power, double dright)

  {

    return dleft*exp(left);

  }

};

template<class E1, class E2, class op>

struct binop

{

  const E1 left;

  const E2 right;

 

  binop(const E1 left, const E2 right)

    : left(left)

    , right(right) {}

 

  double value() const { return op::value(left.value(), right.value()); }

 

  double gradient(int i) const

  {

    return op::gradient(left.value(), left.gradient(i),

                        right.value(), right.gradient(i));

  }

};

template<class E2, class op>

struct binop<double , E2 , op>

{

  const double left;

  const E2 right;

 

  binop(const double left, const E2 right)

    : left(left)

    , right(right) {}

 

  double value() const { return op::value(left, right.value()); }

 

  double gradient(int i) const

  {

    return op::gradient(left, 0.,

                        right.value(), right.gradient(i));

  }

};

template<class E1, class op>

struct binop<E1 , double , op>

{

  const E1 left;

  const double right;

 

  binop(const E1 left, const double right)

    : left(left)

    , right(right) {}

 

  double value() const { return op::value(left.value(), right); }

 

  double gradient(int i) const

  {

    return op::gradient(left.value(), left.gradient(i),

                        right, 0.);

  }

};

template<class E1, class E2>

binop<E1, E2, mult>  operator*(const E1 left, const E2 right)

{

  return binop<E1, E2, mult>(left, right);

}

// je fais meme chose pour /
template<class E1, class E2>

binop<E1, E2, divs>  operator/(const E1 left, const E2 right)

{

  return binop<E1, E2, divs>(left, right);

}

// je fais meme chose pour +
template<class E1, class E2>

binop<E1, E2, add>  operator+(const E1 left, const E2 right)

{

  return binop<E1, E2, add>(left, right); 

}

// je fais la meme chose pour -
 template<class E1, class E2>

binop<E1, E2, sub>  operator-(const E1 left, const E2 right)

{

  return binop<E1, E2, sub>(left, right); 

}

// je fais la meme chose pour - unitaire
template< class E2>

binop<double, E2, sub>  operator-( const E2 right)

{

  return binop<double, E2, sub>(0., right); 

}

// je fais la meme chose pour puissance
template< class E1>

binop<E1, double, pui>  puis( const E1 left,double power)

{

  return binop<E1, double, pui>(left, power); 

}

// je fais la meme chose pour cos
template< class E1>

binop<E1, double, cosi>  cos( const E1 left)

{

  return binop<E1, double, cosi>(left, 0.); 

}

// je fais la meme chose pour sin
template< class E1>

binop<E1, double, sinu>  sin( const E1 left)

{

  return binop<E1, double, sinu>(left, 0.); 

}

// je fais la meme chose pour expo
template< class E1>

binop<E1, double, expo>  exp( const E1 left)

{

  return binop<E1, double, expo>(left,0.); 

}

int main(void)

{
// creation de deux vecteurs a et b
  vector a { /* v */ 1, /* dv */ 1., 0., 0. }; // v est la valeur de a et dv c'est la valeur de la dérivé par rapport aux autres var
  vector b { /* v */ 2., /* dv */ 0., 1., 0. };// mm chose !

 
// je teste

  auto expr11 = puis(a,3.)+(puis(b,2.)-a)*b;

  auto expr12 = 3.0*puis(a,2.)-b;

  auto expr13 = 2.0*b-a;

  auto expr14 = puis(sin(a),6.);

  auto expr15 = cos(a);

  auto expr16 = exp(a);

  auto expr17 = a * 1.;

  auto expr18 = 1. / a;

  auto expr19 = a / 1.;

  auto expr20 = a*b*a*b*3.0;

  auto expr21 = a+a+a+a;

  auto expr22 = a-b-a-b;

  auto expr23 = a/b; 
 

 // test prof
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

  std::cout << expr11.value() << std::endl;
  std::cout << expr11.gradient(0) << std::endl; // derivé de expr /a
  std::cout << expr11.gradient(1) << std::endl; // derivé de expr /b
  std::cout << expr11.gradient(2) << std::endl<< std::endl; // derivé de expr /c

  std::cout << expr12.value() << std::endl;
  std::cout << expr12.gradient(0) << std::endl; // derivé de expr /a
  std::cout << expr12.gradient(1) << std::endl; // derivé de expr /b
  std::cout << expr12.gradient(2) << std::endl<< std::endl; // derivé de expr /c

  std::cout << expr13.value() << std::endl;
  std::cout << expr13.gradient(0) << std::endl; // derivé de expr /a
  std::cout << expr13.gradient(1) << std::endl; // derivé de expr /b
  std::cout << expr13.gradient(2) << std::endl<< std::endl; // derivé de expr /c

  std::cout << expr14.value() << std::endl;
  std::cout << expr14.gradient(0) << std::endl; // derivé de expr /a
  std::cout << expr14.gradient(1) << std::endl; // derivé de expr /b
  std::cout << expr14.gradient(2) << std::endl<< std::endl; // derivé de expr /c

  std::cout << expr15.value() << std::endl;
  std::cout << expr15.gradient(0) << std::endl; // derivé de expr /a
  std::cout << expr15.gradient(1) << std::endl; // derivé de expr /b
  std::cout << expr15.gradient(2) << std::endl<< std::endl; // derivé de expr /c

  std::cout << expr16.value() << std::endl;
  std::cout << expr16.gradient(0) << std::endl; // derivé de expr /a
  std::cout << expr16.gradient(1) << std::endl; // derivé de expr /b
  std::cout << expr16.gradient(2) << std::endl<< std::endl; // derivé de expr /c

  std::cout << expr17.value() << std::endl;
  std::cout << expr17.gradient(0) << std::endl; // derivé de expr /a
  std::cout << expr17.gradient(1) << std::endl; // derivé de expr /b
  std::cout << expr17.gradient(2) << std::endl<< std::endl; // derivé de expr /c

  std::cout << expr18.value() << std::endl;
  std::cout << expr18.gradient(0) << std::endl; // derivé de expr /a
  std::cout << expr18.gradient(1) << std::endl; // derivé de expr /b
  std::cout << expr18.gradient(2) << std::endl<< std::endl; // derivé de expr /c

  std::cout << expr19.value() << std::endl;
  std::cout << expr19.gradient(0) << std::endl; // derivé de expr /a
  std::cout << expr19.gradient(1) << std::endl; // derivé de expr /b
  std::cout << expr19.gradient(2) << std::endl; // derivé de expr /c

  std::cout << expr20.value() << std::endl;
  std::cout << expr20.gradient(0) << std::endl; // derivé de expr /a
  std::cout << expr20.gradient(1) << std::endl; // derivé de expr /b
  std::cout << expr20.gradient(2) << std::endl; // derivé de expr /c

  std::cout << expr21.value() << std::endl;
  std::cout << expr21.gradient(0) << std::endl; // derivé de expr /a
  std::cout << expr21.gradient(1) << std::endl; // derivé de expr /b
  std::cout << expr21.gradient(2) << std::endl; // derivé de expr /c

  std::cout << expr22.value() << std::endl;
  std::cout << expr22.gradient(0) << std::endl; // derivé de expr /a
  std::cout << expr22.gradient(1) << std::endl; // derivé de expr /b
  std::cout << expr22.gradient(2) << std::endl; // derivé de expr /c

  std::cout << expr23.value() << std::endl;
  std::cout << expr23.gradient(0) << std::endl; // derivé de expr /a
  std::cout << expr23.gradient(1) << std::endl; // derivé de expr /b
  std::cout << expr23.gradient(2) << std::endl; // derivé de expr /c

  std::cout << exprt1.value() << std::endl;
  std::cout << exprt1.gradient(0) << std::endl; // derivé de expr /a
  std::cout << exprt1.gradient(1) << std::endl; // derivé de expr /b
  std::cout << exprt1.gradient(2) << std::endl; // derivé de expr /c

  std::cout << exprt2.value() << std::endl;
  std::cout << exprt2.gradient(0) << std::endl; // derivé de expr /a
  std::cout << exprt2.gradient(1) << std::endl; // derivé de expr /b
  std::cout << exprt2.gradient(2) << std::endl; // derivé de expr /c

  std::cout << exprt3.value() << std::endl;
  std::cout << exprt3.gradient(0) << std::endl; // derivé de expr /a
  std::cout << exprt3.gradient(1) << std::endl; // derivé de expr /b
  std::cout << exprt3.gradient(2) << std::endl; // derivé de expr /c
  
  std::cout << exprt4.value() << std::endl;
  std::cout << exprt4.gradient(0) << std::endl; // derivé de expr /a
  std::cout << exprt4.gradient(1) << std::endl; // derivé de expr /b
  std::cout << exprt4.gradient(2) << std::endl; // derivé de expr /c

  std::cout << exprt5.value() << std::endl;
  std::cout << exprt5.gradient(0) << std::endl; // derivé de expr /a
  std::cout << exprt5.gradient(1) << std::endl; // derivé de expr /b
  std::cout << exprt5.gradient(2) << std::endl; // derivé de expr /c

  std::cout << exprt6.value() << std::endl;
  std::cout << exprt6.gradient(0) << std::endl; // derivé de expr /a
  std::cout << exprt6.gradient(1) << std::endl; // derivé de expr /b
  std::cout << exprt6.gradient(2) << std::endl; // derivé de expr /c

  std::cout << exprt7.value() << std::endl;
  std::cout << exprt7.gradient(0) << std::endl; // derivé de expr /a
  std::cout << exprt7.gradient(1) << std::endl; // derivé de expr /b
  std::cout << exprt7.gradient(2) << std::endl; // derivé de expr /c

  std::cout << exprt8.value() << std::endl;
  std::cout << exprt8.gradient(0) << std::endl; // derivé de expr /a
  std::cout << exprt8.gradient(1) << std::endl; // derivé de expr /b
  std::cout << exprt8.gradient(2) << std::endl; // derivé de expr /c

  std::cout << exprt9.value() << std::endl;
  std::cout << exprt9.gradient(0) << std::endl; // derivé de expr /a
  std::cout << exprt9.gradient(1) << std::endl; // derivé de expr /b
  std::cout << exprt9.gradient(2) << std::endl; // derivé de expr /c

  std::cout << exprt10.value() << std::endl;
  std::cout << exprt10.gradient(0) << std::endl; // derivé de expr /a
  std::cout << exprt10.gradient(1) << std::endl; // derivé de expr /b
  std::cout << exprt10.gradient(2) << std::endl; // derivé de expr /c

  std::cout << exprt11.value() << std::endl;
  std::cout << exprt11.gradient(0) << std::endl; // derivé de expr /a
  std::cout << exprt11.gradient(1) << std::endl; // derivé de expr /b
  std::cout << exprt11.gradient(2) << std::endl; // derivé de expr /c
  
  std::cout << exprt12.value() << std::endl;
  std::cout << exprt12.gradient(0) << std::endl; // derivé de expr /a
  std::cout << exprt12.gradient(1) << std::endl; // derivé de expr /b
  std::cout << exprt12.gradient(2) << std::endl; // derivé de expr /c

  std::cout << exprt13.value() << std::endl;
  std::cout << exprt13.gradient(0) << std::endl; // derivé de expr /a
  std::cout << exprt13.gradient(1) << std::endl; // derivé de expr /b
  std::cout << exprt13.gradient(2) << std::endl; // derivé de expr /c

}