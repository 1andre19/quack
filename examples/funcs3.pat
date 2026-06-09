programa test_simple;
vars
  r1 : entero;
  r2 : entero;
  a  : flotante;

entero doble(x : entero) {
    vars
        res : entero;
    {
        res = x * 2;
        retorna res;
    }
};

inicio
{
  r1 = doble(5);
  r2 = doble(10);
  a = 20.74;
  a = 12.74;
  a = 90.821283123;
  escribe(r1);
  escribe(r2);
  escribe("hola");
  escribe("adios");
  r1 = 20 + 30;
}
fin
