programa test_AB;
vars
  a : entero;
  b : entero;
  c : flotante;
  d : flotante;
  res : entero;
inicio
{
  a = 10;
  b = 3;
  c = 4.5;
  d = 2.0;


  escribe("== Aritmetica Entera ==");
  escribe("a = ", a);
  escribe("b = ", b);
  escribe("a + b = ", a + b);
  escribe("a - b = ", a - b);
  escribe("a * b = ", a * b);
  escribe("a / b = ", a / b);


  escribe("== Aritmetica Flotante ==");
  escribe("c = ", c);
  escribe("d = ", d);
  escribe("c + d = ", c + d);
  escribe("c - d = ", c - d);
  escribe("c * d = ", c * d);
  escribe("c / d = ", c / d);


  escribe("== Precedencia y Parentesis ==");
  escribe("a + b * 2 = ", a + b * 2);
  escribe("(a + b) * 2 = ", (a + b) * 2);
  escribe("a * b + c * d = ", a * b + c * d);


  escribe("== Unarios ==");
  escribe("-a = ", -a);
  escribe("- -a = ", - -a);


  escribe("== Relacionales ==");
  escribe("a > b  : ", a > b);
  escribe("a < b  : ", a < b);
  escribe("a == 10: ", a == 10);
  escribe("a != b : ", a != b);
  escribe("b == 3 : ", b == 3);
}
fin
