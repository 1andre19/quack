programa prueba;

vars
    x, y, z : entero;
    f : flotante;

nulo saluda(){
    {
        escribe("hola");
    }
};

entero duplica(n : entero) {
    {
        retorna n * 2;
    }
};

inicio
{
    x = 15;
    f = 14.507;
    escribe("hola mundo", 15, 20, 30, 800);
    escribe(15);
    escribe(x + f);
    saluda();

    y = 2;
    escribe(duplica(duplica(y)));
}
fin
