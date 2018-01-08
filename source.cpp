#include <iostream>

 

struct vector

{

  auto value() { return v; }

  const auto value() const { return v; }

 

  auto gradient(int i) { return dv[i]; }

  const auto gradient(int i) const { return dv[i]; }

 

  double v;

  double dv[3];

};

 

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

template< class E2>

binop<double, E2, sub>  operator-( const E2 right)

{

  return binop<double, E2, sub>(0., right); 

}



int main(void)

{

  vector a { /* v */ 1., /* dv */ 1., 0., 0. }; // v est la valeur de a et dv c'est la valeur de la dérivé par rapport aux autres var
                                                //
  vector b { /* v */ 2., /* dv */ 0., 1., 0. };// mm chose !

 
// je teste
  //auto expr = a*b*a*b*3.0;
  //auto expr2 = a+a+a+a;
  //auto expr3 = a-b-a-b;
  //auto expr4 = a/b; //probleme > compile mais n'affiche pas 
  auto expr11 = - b;

  auto expr12 = 1. - a;

  auto expr13 = a - 1.;

  auto expr14 = 1. + a;

  auto expr15 = a + 1.;

  auto expr16 = 1. * a;

  auto expr17 = a * 1.;

  auto expr18 = 1. / a;

  auto expr19 = a / 1.;
/*

  std::cout << expr.value() << std::endl;

  std::cout << expr.gradient(0) << std::endl; // derivé de expr /a

  std::cout << expr.gradient(1) << std::endl; // derivé de expr /b

  std::cout << expr.gradient(2) << std::endl; // derivé de expr /c
//*/
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

/*
  std::cout << expr2.value() << std::endl;

  std::cout << expr2.gradient(0) << std::endl; // derivé de expr /a

  std::cout << expr2.gradient(1) << std::endl; // derivé de expr /b

  std::cout << expr2.gradient(2) << std::endl; // derivé de expr /c


  std::cout << expr3.value() << std::endl;

  std::cout << expr3.gradient(0) << std::endl; // derivé de expr /a

  std::cout << expr3.gradient(1) << std::endl; // derivé de expr /b

  std::cout << expr3.gradient(2) << std::endl; // derivé de expr /c


//  std::cout << expr4.value() << std::endl;

//  std::cout << expr4.gradient(0) << std::endl; // derivé de expr /a

//  std::cout << expr4.gradient(1) << std::endl; // derivé de expr /b

//  std::cout << expr4.gradient(2) << std::endl; // derivé de expr /c
*/
}

