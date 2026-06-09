programa factorial;
vars
  x : entero;

entero factorial(n : entero) {
    vars
        i : entero;
        resultado : entero;
    {
        resultado = 1;
        i = 1;

        mientras (i < n + 1)
        haz
        {
            resultado = resultado * i;
            i = i + 1;
        };

        retorna resultado;
    }
};

inicio
{
    x = 5;
    escribe("factorial:");
    escribe(factorial(x));
}
fin
