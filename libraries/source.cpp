#include <iostream>

 

struct vector

{

  auto& value() { return v; }

  const auto& value() const { return v; }

 

  auto& gradient(int i) { return dv[i]; }

  const auto& gradient(int i) const { return dv[i]; }

 

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

    return left / right;

  }

 

  static auto gradient(double left, double dleft, double right, double dright)

  {

    return (dleft * right - left * dright)/(right*right);

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

  const E1& left;

  const E2& right;

 

  binop(const E1& left, const E2& right)

    : left(left)

    , right(right) {}

 

  double value() const { return op::value(left.value(), right.value()); }

 

  double gradient(int i) const

  {

    return op::gradient(left.value(), left.gradient(i),

                        right.value(), right.gradient(i));

  }

};

 

template<class E1, class E2>

binop<E1, E2, mult>  operator*(const E1& left, const E2& right)

{

  return binop<E1, E2, mult>(left, right);

}

// je fais meme chose pour /
template<class E1, class E2>

binop<E1, E2, divs>  operator/(const E1& left, const E2& right)

{

  return binop<E1, E2, divs>(left, right);

}

// je fais meme chose pour +
template<class E1, class E2>

binop<E1, E2, add>  operator+(const E1& left, const E2& right)

{

  return binop<E1, E2, add>(left, right); 

}

// je fais la meme chose pour -
 template<class E1, class E2>

binop<E1, E2, sub>  operator-(const E1& left, const E2& right)

{

  return binop<E1, E2, sub>(left, right); 

}



int main(void)

{

  vector a { /* v */ 1., /* dv */ 1., 0., 0. }; // v est la valeur de a et dv c'est la valeur de la dérivé par rapport aux autres var

  vector b { /* v */ 2., /* dv */ 0., 1., 0. };// mm chose !

 
// je teste
  auto expr = a*b*a*b;
  auto expr2 = a+b+a+b;
  auto expr3 = a-b-a-b;
//  auto expr4 = a/b; probleme > compile mais n'affiche pas 

 

  std::cout << expr.value() << std::endl;

  std::cout << expr.gradient(0) << std::endl; // derivé de expr /a

  std::cout << expr.gradient(1) << std::endl; // derivé de expr /b

  std::cout << expr.gradient(2) << std::endl; // derivé de expr /c


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

}

