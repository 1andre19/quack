programa fib_iterativo;
vars
  x : entero;

entero fib(n : entero) {
    vars
        i : entero;
        anterior : entero;
        actual : entero;
        siguiente : entero;
    {
        si (n < 2)
        {
            retorna n;
        };

        anterior = 0;
        actual = 1;
        i = 2;

        mientras (i < n + 1)
        haz
        {
            siguiente = anterior + actual;
            anterior = actual;
            actual = siguiente;
            i = i + 1;
        };

        retorna actual;
    }
};

inicio
{
    x = 10;
    escribe("primeros 10 fibonacci");

    mientras (x > 0)
    haz
    {
        escribe(fib(x));
        x = x - 1;
    };
}
fin
