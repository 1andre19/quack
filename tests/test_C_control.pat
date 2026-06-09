programa test_C_control;
vars
  i     : entero;
  n     : entero;
  par   : entero;
  fizz  : entero;
  buzz  : entero;
inicio
{

  escribe("== Cuenta del 1 al 5 ==");
  i = 1;
  mientras (i < 6)
  haz
  {
    escribe(i);
    i = i + 1;
  };


  escribe("== Clasificacion de n = 7 ==");
  n = 7;
  si (n > 0)
  {
    escribe("positivo");
  }
  sino
  {
    escribe("no positivo");
  };


  escribe("== Signo de n = -3 ==");
  n = -3;
  si (n > 0)
  {
    escribe("positivo");
  }
  sino
  {
    si (n < 0)
    {
      escribe("negativo");
    }
    sino
    {
      escribe("cero");
    };
  };


  escribe("== Pares e Impares del 1 al 10 ==");
  i = 1;
  mientras (i < 11)
  haz
  {
    par = i / 2;
    par = par * 2;
    si (par == i)
    {
      escribe(i, " es par");
    }
    sino
    {
      escribe(i, " es impar");
    };
    i = i + 1;
  };


  escribe("== FizzBuzz 1-15 ==");
  i = 1;
  mientras (i < 16)
  haz
  {
    fizz = i / 3;
    fizz = fizz * 3;
    buzz = i / 5;
    buzz = buzz * 5;
    si (fizz == i)
    {
      si (buzz == i)
      {
        escribe("FizzBuzz");
      }
      sino
      {
        escribe("Fizz");
      };
    }
    sino
    {
      si (buzz == i)
      {
        escribe("Buzz");
      }
      sino
      {
        escribe(i);
      };
    };
    i = i + 1;
  };
}
fin
