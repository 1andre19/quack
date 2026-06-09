programa test6;
vars
  n : entero;
  f : flotante;
  a : entero;

flotante promedio(a : entero, b : flotante) {
    vars
        res : flotante;
    {
        res = a + b;
        n = 1;
        retorna res;
    }
};

inicio
{
  a = 20;
  f = promedio(3, 4.5);
  a = 20 + 40;
  escribe(f);
  n = 50;
  escribe("hola");
}
fin


