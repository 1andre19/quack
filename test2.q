programa prueba;

vars
    x, y, z : entero;
    pi, radio : flotante;

nulo saluda(nombre : entero) {
    vars
        i : entero;
    {
        escribe("hola", nombre);
    }
};

entero suma(a : entero, b : entero) {
    vars
        resultado : entero;
    {
    }
};

flotante area_circulo(r : flotante) {
    vars
        resultado : flotante;
    {
        resultado = r * r;
    }
};

entero factorial(n : entero) {
    vars
        resultado : entero;
    {
        resultado = 1;
        mientras (n > 0) haz {
            resultado = resultado * n;
            n = n - 1;
        };
    }
};

nulo clasifica(n : entero) {
    {
        si (n > 0) {
            escribe("positivo");
        } sino {
            escribe("no positivo");
        };
    }
};

inicio
{
    x = 10;
    y = 20;
    z = x + y;

    escribe("suma de x y y:", z);

    pi = 3;
    radio = 5;

    escribe("x por y:", x * y);
    escribe("z menos x:", z - x);

    mientras (x > 0) haz {
        escribe("x:", x);
        x = x - 1;
    };

    si (y > x) {
        escribe("y es mayor");
    } sino {
        escribe("x es mayor o igual");
    };

    si (z != 0) {
        escribe("z no es cero");
    };

    saluda(42);

    z = suma(x, y);
    escribe("resultado suma:", z);

    clasifica(z);
}
fin
