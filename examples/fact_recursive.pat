programa factorial_recursivo;
vars
  x : entero;

entero factorial(n : entero) {
    {
        si (n < 2)
        {
            retorna 1;
        };

        retorna n * factorial(n - 1);
    }
};

inicio
{
    x = 5;
    escribe("factorial recursivo:");
    escribe(factorial(x));
}
fin
