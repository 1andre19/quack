programa test_DE_funciones;
vars
  n      : entero;
  result : entero;
  a      : entero;
  b      : entero;
  temp   : entero;
  i      : entero;

entero factorial(n : entero) {
  vars
    acc : entero;
    k   : entero;
  {
    acc = 1;
    k   = 1;
    mientras (k < n + 1)
    haz
    {
      acc = acc * k;
      k   = k + 1;
    };
    retorna acc;
  }
};

entero fibonacci(n : entero) {
  vars
    prev : entero;
    curr : entero;
    next : entero;
    k    : entero;
  {
    prev = 0;
    curr = 1;
    k    = 1;
    si (n == 0)
    {
      retorna 0;
    }
    sino {};
    mientras (k < n)
    haz
    {
      next = prev + curr;
      prev = curr;
      curr = next;
      k    = k + 1;
    };
    retorna curr;
  }
};

entero potencia(base : entero, exp : entero) {
  vars
    res : entero;
    k   : entero;
  {
    res = 1;
    k   = 0;
    mientras (k < exp)
    haz
    {
      res = res * base;
      k   = k + 1;
    };
    retorna res;
  }
};

nulo imprime_linea() {
  {
    escribe("--------------------");
  }
};

inicio
{

  escribe("== Factorial en el main (0! al 7!) ==");
  n = 0;
  mientras (n < 8)
  haz
  {
    result = 1;
    i      = 1;
    mientras (i < n + 1)
    haz
    {
      result = result * i;
      i      = i + 1;
    };
    escribe(n, "! = ", result);
    n = n + 1;
  };

  imprime_linea();


  escribe("== Factorial con funcion (0! al 7!) ==");
  n = 0;
  mientras (n < 8)
  haz
  {
    result = factorial(n);
    escribe(n, "! = ", result);
    n = n + 1;
  };

  imprime_linea();


  escribe("== Fibonacci en el main (F0 al F10) ==");
  a = 0;
  b = 1;
  i = 0;
  escribe("F(", i, ") = ", a);
  i = 1;
  mientras (i < 11)
  haz
  {
    escribe("F(", i, ") = ", b);
    temp = a + b;
    a    = b;
    b    = temp;
    i    = i + 1;
  };

  imprime_linea();


  escribe("== Fibonacci con funcion (F0 al F10) ==");
  i = 0;
  mientras (i < 11)
  haz
  {
    result = fibonacci(i);
    escribe("F(", i, ") = ", result);
    i = i + 1;
  };

  imprime_linea();


  escribe("== Potencias: 2^0 al 2^10 ==");
  i = 0;
  mientras (i < 11)
  haz
  {
    result = potencia(2, i);
    escribe("2^", i, " = ", result);
    i = i + 1;
  };

  imprime_linea();


  escribe("== Expresion como argumento ==");
  n = 3;
  result = factorial(n + 1);
  escribe("factorial(3 + 1) = factorial(4) = ", result);


  result = factorial(3) + fibonacci(5);
  escribe("factorial(3) + fibonacci(5) = 6 + 5 = ", result);
}
fin
