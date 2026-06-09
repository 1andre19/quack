programa test6;
vars
  f : flotante;
  a : entero;
  n : entero;

flotante promedio(a : entero, b : flotante) {
    vars
        res : flotante;
    {
        res = a + b;
        retorna res;
    }
};

entero entero_doble(x : entero) {
    vars
        res : entero;
    {
        res = x * 2;
        retorna 10;
    }
};

entero fib(n: entero) {
    {
        si (n < 2)
        {
            n = 10;
            retorna n;
        };
        retorna fib(n - 1) + fib(n - 2);
    }

};

inicio
{
  a = 20;
  n = entero_doble(7 + 10 * 50 + a);
  n = entero_doble(entero_doble(entero_doble(20)));
  escribe(n, entero_doble(19), "hola");
  f = promedio(3, 4.5);
  escribe(f);
  n = fib(5);
}
fin
