programa foo;
vars
  x, y, z : entero; a, b: flotante;

flotante area_circulo(r : flotante) {
    vars
        resultado : flotante;
    {
        resultado = r * r;
    }
};

inicio
{
  y = 15 * 30 + 20 * 5 * (1 + 2) * 3;
  a = 15.0;
  z = x > z;
  z = x < z;
  z = x == z;
  z = x != z;
  b = 234.20;
  escribe("hola gente");
}
fin
