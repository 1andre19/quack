programa test_general;
vars
  x : entero;
  y : entero;
  z : entero;

entero suma_n(n : entero) {
  vars
    acc : entero;
    k   : entero;
  {
    acc = 0;
    k   = 1;
    mientras (k < n + 1)
    haz
    {
      acc = acc * 1 + k;
      k   = k + 1;
    };
    retorna acc;
  }
};

nulo tabla(n : entero) {
  vars
    k : entero;
  {
    escribe("-- Tabla del ", n, " --");
    k = 1;
    mientras (k < 11)
    haz
    {
      escribe(n, " x ", k, " = ", n * k);
      k = k + 1;
    };
  }
};

entero maximo(a : entero, b : entero) {
  {
    si (a > b)
    {
      retorna a;
    }
    sino
    {
      retorna b;
    };
  }
};

entero abs_val(v : entero) {
  {
    si (v < 0)
    {
      retorna -v;
    }
    sino
    {
      retorna v;
    };
  }
};

entero num_digitos(n : entero) {
  vars
    cnt : entero;
    tmp : entero;
  {
    cnt = 0;
    tmp = abs_val(n);
    si (tmp == 0)
    {
      retorna 1;
    }
    sino {};
    mientras (tmp > 0)
    haz
    {
      tmp = tmp / 10;
      cnt = cnt + 1;
    };
    retorna cnt;
  }
};

inicio
{
  escribe("== Tablas de multiplicar ==");
  tabla(3);
  tabla(7);


  escribe("== Suma 1..N ==");
  x = 1;
  mientras (x < 6)
  haz
  {
    y = suma_n(x);
    escribe("suma(1..", x, ") = ", y);
    x = x + 1;
  };


  escribe("== Maximos ==");
  x = 1;
  mientras (x < 5)
  haz
  {
    y = x + 2;
    z = maximo(x, y);
    escribe("max(", x, ",", y, ") = ", z);
    x = x + 1;
  };


  escribe("== Variables globales ==");
  x = 100;
  y = 200;
  escribe("x = ", x, "  y = ", y);
  z = x + y;
  escribe("x + y = ", z);
  x = z - y;
  escribe("x restaurado = ", x);


  escribe("== Digitos de numeros ==");
  escribe("digitos(0)    = ", num_digitos(0));
  escribe("digitos(7)    = ", num_digitos(7));
  escribe("digitos(42)   = ", num_digitos(42));
  escribe("digitos(999)  = ", num_digitos(999));
  escribe("digitos(1234) = ", num_digitos(1234));


  escribe("== Composicion ==");
  z = maximo(suma_n(4), suma_n(5));
  escribe("max(suma_n(4), suma_n(5)) = max(10, 15) = ", z);


  escribe("== Tabla de adicion (1..4 x 1..4) ==");
  x = 1;
  mientras (x < 5)
  haz
  {
    y = 1;
    mientras (y < 5)
    haz
    {
      z = x + y;
      escribe(x, " + ", y, " = ", z);
      y = y + 1;
    };
    x = x + 1;
  };
}
fin
