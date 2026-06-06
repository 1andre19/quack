programa foo;
vars
  x : entero;

nulo saluda(nombre : entero) {
    vars
        i : entero;
    {
        escribe("hola", nombre);
    }
};

inicio
{
  mientras (x < 10)
  haz
  {
    x = x + 1;
  };
  saluda();
}
fin
