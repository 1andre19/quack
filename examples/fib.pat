programa fib;
vars
  f : flotante;
  a : entero;
  n : entero;
  x : entero;

entero fib(n: entero) {
    {
        si (n < 2)
        {
            retorna n;
        };
        retorna fib(n - 1) + fib(n - 2);
    }

};

inicio
{
    x = 0;
    escribe("primeros 10 fibonacci");
    mientras (x < 20)
    haz
    {
        escribe(fib(x));
        x = x + 1; 
    };
}
fin
