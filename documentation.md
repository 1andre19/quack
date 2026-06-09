# Quack — Documentación Patito

#### DISCLAIMER: 
Esta documentación fue generada con Claude Code usando el model Sonnet 4.6. Se utilizó
este modelo para ayudar en el desarrollo de este proyecto, se utilizó principalmente para
idear conceptos de arquitectura y diseños de la aplicación, la mayoría del código fue escrito
por mi.

## Índice

1. [Descripción del Lenguaje](#1-descripción-del-lenguaje)
2. [Gramática](#2-gramática)
3. [Árbol de Sintaxis Abstracta (AST)](#3-árbol-de-sintaxis-abstracta-ast)
4. [Análisis Semántico](#4-análisis-semántico)
5. [Generación de Cuádruplos](#5-generación-de-cuádruplos)
6. [Memoria de Ejecución](#6-memoria-de-ejecución)
7. [Direcciones Virtuales](#7-direcciones-virtuales)
8. [Casos de Prueba](#8-casos-de-prueba)

---

## 1. Descripción del Lenguaje

**Patito** es un lenguaje de programación imperativo con tipado estático, diseñado con palabras clave en español. El compilador traduce código fuente `.pat` a cuádruplos que son ejecutados por una máquina virtual (VM) integrada.

### Características principales

- Tipos de dato: `entero` (entero largo), `flotante` (doble precisión), cadenas literales.
- Funciones con parámetros tipados y valor de retorno.
- Estructuras de control: `si`/`sino` y `mientras`/`haz`.
- Instrucción de salida: `escribe`.
- Alcance léxico: variables globales y locales por función.
- Verificación de tipos en tiempo de compilación (cubo semántico).

### Palabras reservadas

| Token     | Significado                  |
|-----------|------------------------------|
| `programa` | Inicio de un programa       |
| `inicio`  | Inicio del bloque principal  |
| `fin`     | Fin del programa             |
| `vars`    | Declaración de variables     |
| `entero`  | Tipo entero                  |
| `flotante`| Tipo flotante                |
| `nulo`    | Tipo de retorno vacío        |
| `si`      | Condicional if               |
| `sino`    | Rama else                    |
| `mientras`| Ciclo while                  |
| `haz`     | Do (cierra condición while)  |
| `escribe` | Imprime valores              |
| `retorna` | Retorna un valor             |

---

## 2. Gramática

La gramática es LALR(1), generada con **Bison 3.8+**. El analizador léxico es generado con **Flex**.

```
programa:
    'programa' ID ';' vars.opt funcs.opt 'inicio' cuerpo 'fin'
    ;

funcs.opt:
    funcs funcs.opt
  | ε
  ;

cuerpo:
    '{' adentro '}'
  ;

adentro:
    estatuto adentro
  | ε
  ;

estatuto:
    asigna
  | condicion
  | ciclo
  | llamada ';'
  | imprime ';'
  | retorna ';'
  ;

retorna:
    'retorna' expresion
    ;

imprime:
    'escribe' '(' imprime_args imprime_mas ')'
    ;

imprime_args:
    expresion
  | LETRERO
  ;

imprime_mas:
    ',' imprime_args imprime_mas
  | ε
  ;

ciclo:
    'mientras' '(' expresion ')' 'haz' cuerpo ';'
    ;

condicion:
    'si' '(' expresion ')' cuerpo sino ';'
    ;

sino:
    'sino' cuerpo
  | ε
  ;

vars:
    'vars' list_vars
    ;

vars.opt:
    vars
  | ε
  ;

list_vars:
    ID list_id ':' tipo ';' list_vars
  | ε
  ;

list_id:
    ',' ID list_id
  | ε
  ;

tipo:
    'entero'
  | 'flotante'
  ;

cte:
    CTE_FLOT
  | CTE_ENT
  ;

asigna:
    ID '=' expresion ';'
    ;

expresion:
    exp
  | exp comp exp
  ;

exp:
    termino
  | exp '+' termino
  | exp '-' termino
  ;

comp:
    '>'
  | '<'
  | '!='
  | '=='
  ;

termino:
    factor
  | termino '*' factor
  | termino '/' factor
  ;

factor:
    '+' factor
  | '-' factor
  | '(' expresion ')'
  | ID
  | cte
  | llamada
  ;

llamada:
    ID '(' args ')'
    ;

args:
    expresion list_expr
  | ε
  ;

list_expr:
    ',' expresion list_expr
  | ε
  ;

funcs:
    tipo_func ID '(' parametros ')' '{' vars.opt cuerpo '}' ';'
    ;

parametros:
    param list_param
  | ε
  ;

param:
    ID ':' tipo
    ;

list_param:
    ',' param list_param
  | ε
  ;

tipo_func:
    'nulo'
  | tipo
  ;
```

### Tokens terminales

| Token      | Expresión regular                    | Descripción                        |
|------------|--------------------------------------|------------------------------------|
| `ID`       | `[A-Za-z][A-Za-z0-9_]*`             | Identificador                      |
| `CTE_ENT`  | `[0-9]+`                             | Constante entera                   |
| `CTE_FLOT` | `[0-9]+"."[0-9]+`                    | Constante flotante                 |
| `LETRERO`  | `\"[^\"]*\"`                         | Cadena de texto                    |

---

## 3. Árbol de Sintaxis Abstracta (AST)

El compilador construye un AST durante el parseo. Se usa el patrón **Visitor** para recorrerlo en la fase de generación de cuádruplos sin acoplar la lógica de cada nodo a su estructura.

### Jerarquía de nodos

```
NodeAST
├── ExprAST
│   ├── IntegerLiteral
│   ├── FloatingLiteral
│   ├── StringLiteral
│   ├── ReferenceExpr
│   ├── BinaryOpExpr
│   ├── UnaryOpExpr
│   └── CallExpr
└── StmntAST
    ├── AssignmentStmnt
    ├── VarDeclStmt
    ├── ParamVarDecl
    ├── FuncDeclStmt
    ├── PrintStmnt
    ├── WhileStmnt
    ├── IfStmnt
    ├── CallStmt
    └── ReturnStmnt

ProgramAST (raíz del árbol)
```

### Nodos principales

#### `ProgramAST`
Raíz del árbol. Contiene el nombre del programa, las variables globales, las declaraciones de funciones y el cuerpo principal (`inicio ... fin`).

```
ProgramAST
  name: string
  Globals: VarDeclStmt[]
  Functions: FuncDeclStmt[]
  Body: StmntAST[]
```

#### `FuncDeclStmt`
Representa la declaración completa de una función: nombre, parámetros, variables locales, tipo de retorno y cuerpo.

```
FuncDeclStmt
  Name: string
  Params: ParamVarDecl[]
  Locals: VarDeclStmt[]
  ReturnType: Type
  Body: StmntAST[]
```

**Pseudocódigo de visita:**
```
visit(FuncDeclStmt):
    resetear contadores de memoria local y temporal
    asignar direcciones virtuales a cada parámetro
    registrar la función en FunctionDirectory con start_quad = quads.size()
    si ReturnType != VOID:
        agregar variable global con el nombre de la función (para guardar el retorno)
    cambiar scope actual al nombre de la función
    visitar Locals  →  genera entradas en la tabla de símbolos local
    visitar Body    →  genera cuádruplos
    emitir ENDFUNC
    guardar en FunctionDirectory los recursos (conteos de locales y temporales)
    restaurar scope a "global"
```

#### `BinaryOpExpr`
Expresión con operador binario (`+`, `-`, `*`, `/`, `>`, `<`, `==`, `!=`). Al visitarse, consulta el cubo semántico para verificar compatibilidad de tipos y emite un cuádruplo con un temporal como resultado.

```
BinaryOpExpr
  Op: Operator
  lhs: ExprAST
  rhs: ExprAST
```

**Pseudocódigo de visita:**
```
visit(BinaryOpExpr):
    visitar lhs  →  empuja tipo y dirección de lhs en sus pilas
    visitar rhs  →  empuja tipo y dirección de rhs en sus pilas
    tipo_arg2 = type_stack.pop()
    tipo_arg1 = type_stack.pop()
    tipo_res  = cubo.CheckType(Op, tipo_arg1, tipo_arg2)
    si tipo_res == ERR → error semántico
    addr_arg2 = argument_stack.pop()
    addr_arg1 = argument_stack.pop()
    temp      = nueva dirección temporal del tipo tipo_res
    emitir (instruccion(Op), addr_arg1, addr_arg2, temp)
    argument_stack.push(temp)
    type_stack.push(tipo_res)
```

#### `IfStmnt`
Estructura condicional con rama `Then` y rama opcional `Else`. Usa backpatching para resolver los saltos al momento en que se conoce el cuádruplo destino.

```
IfStmnt
  Condition: ExprAST
  Then: StmntAST[]
  Else: StmntAST[]    (puede estar vacío)
```

**Pseudocódigo de visita:**
```
visit(IfStmnt):
    visitar Condition
    emitir JZ(condition, _, _)    // salto si falso, destino pendiente
    jump_stack.push(índice de ese JZ)
    visitar sentencias de Then
    si Else está vacío:
        backpatch(jump_stack.pop(), quads.size())
        return
    emitir JMP(_, _, _)           // salto al final del else, pendiente
    backpatch(jump_stack.pop(), quads.size())   // parchea el JZ al inicio del else
    jump_stack.push(índice del JMP)
    visitar sentencias de Else
    backpatch(jump_stack.pop(), quads.size())   // parchea el JMP al final
```

#### `WhileStmnt`
Ciclo `mientras`/`haz`. Guarda el cuádruplo de inicio del ciclo para generar el salto de regreso.

```
WhileStmnt
  Condition: ExprAST
  Body: StmntAST[]
```

**Pseudocódigo de visita:**
```
visit(WhileStmnt):
    visitar Condition
    jump_stack.push(índice del último cuádruplo)  // posición de re-evaluación
    emitir JZ(condition, _, _)                    // salir si falso
    jump_stack.push(índice de ese JZ)
    visitar sentencias de Body
    idx_jz    = jump_stack.pop()
    backpatch(idx_jz, quads.size() + 1)           // JZ apunta después del JMP
    idx_start = jump_stack.pop()
    emitir JMP(_, _, idx_start)                   // volver al inicio
```

#### `CallExpr`
Llamada a función como expresión (puede producir un valor). Genera el protocolo completo: evaluar argumentos, `ERA`, `PARAM`s, `CALL`, y si no es `nulo`, recuperar el valor de retorno en un temporal.

```
CallExpr
  Callee: string
  Args: ExprAST[]
```

**Pseudocódigo de visita:**
```
visit(CallExpr):
    buscar la función en FunctionDirectory (error si no existe)
    verificar que |Args| == |params| (error semántico si no coincide)
    visitar cada argumento  →  evalúa en el frame actual
    emitir ERA(_, _, nombre_función)
    para cada argumento (de derecha a izquierda):
        verificar que tipo coincide con el parámetro correspondiente
        emitir PARAM(dir_argumento, _, número_parámetro)
    emitir CALL(_, _, nombre_función)
    si ReturnType != VOID:
        temp = nueva dirección temporal
        emitir MOV(dir_global_retorno, _, temp)
        argument_stack.push(temp)
        type_stack.push(ReturnType)
```

#### `AssignmentStmnt`
Asignación simple. Verifica que la variable esté declarada y que los tipos coincidan.

```
AssignmentStmnt
  Name: string
  rhs: ExprAST
```

**Pseudocódigo de visita:**
```
visit(AssignmentStmnt):
    sym = lookup_symbol(Name)   // busca en scope local y luego en global
    si sym == null → error: variable no declarada
    visitar rhs
    addr_rhs = argument_stack.pop()
    tipo_rhs = type_stack.pop()
    si sym.type != tipo_rhs → error: tipo incompatible
    emitir MOV(addr_rhs, _, sym.virt_addr)
```

---

## 4. Análisis Semántico

### Directorio de Funciones (`FunctionDirectory`)

Estructura central del compilador en tiempo de compilación. Mapea nombres de función a sus entradas correspondientes.

```cpp
class FunctionDirectory {
    unordered_map<string, FunctionDirectoryEntry> directory;
};

class FunctionDirectoryEntry {
    string name;
    vector<FuncParam> params;   // nombre, tipo, dirección virtual
    func_resources resources;   // conteo de locales y temporales
    Type return_type;
    int start_quad;
    unordered_map<string, SymbolEntry> symbol_table;
};
```

El scope global se registra como la entrada `"global"` en el directorio, y sus variables comparten la tabla de símbolos con el bloque `inicio`.

### Tabla de Símbolos (`SymbolEntry`)

Cada variable declarada se registra con:

```cpp
struct SymbolEntry {
    string name;
    Type type;
    bool hasBeenUsed;
    Address virt_addr;   // dirección virtual asignada en tiempo de compilación
};
```

La búsqueda de símbolos sigue el orden: scope actual → scope global.

### Cubo Semántico (`SemanticCube`)

Valida la compatibilidad de tipos para cada operador. Retorna `Type::ERR` si la combinación es inválida.

```
cube[operador][tipo_izquierdo][tipo_derecho] → tipo_resultado
```

Reglas principales:
- Operadores aritméticos (`+`, `-`, `*`, `/`): `INT op INT → INT`, cualquier combinación con `FLOAT → FLOAT`.
- Operadores relacionales (`>`, `<`, `==`, `!=`): siempre retornan `INT` (0 ó 1).
- Operaciones con `STR`: no permitidas en expresiones aritméticas o relacionales.

---

## 5. Generación de Cuádruplos

Los cuádruplos son la representación intermedia del programa. Cada cuádruplo tiene la forma:

```
( instrucción,  arg1,  arg2,  resultado )
```

Donde los argumentos son **direcciones virtuales** (enteros) o cadenas para nombres de función.

### Conjunto de instrucciones

| Instrucción | Descripción                                                     |
|-------------|-----------------------------------------------------------------|
| `ADD`       | `resultado = arg1 + arg2`                                       |
| `SUB`       | `resultado = arg1 - arg2`                                       |
| `MUL`       | `resultado = arg1 * arg2`                                       |
| `DIV`       | `resultado = arg1 / arg2`                                       |
| `GT`        | `resultado = (arg1 > arg2) ? 1 : 0`                             |
| `LT`        | `resultado = (arg1 < arg2) ? 1 : 0`                             |
| `EQ`        | `resultado = (arg1 == arg2) ? 1 : 0`                            |
| `NEQ`       | `resultado = (arg1 != arg2) ? 1 : 0`                            |
| `MOV`       | `resultado = arg1`  (copia de valor)                            |
| `JMP`       | Salto incondicional al cuádruplo `resultado`                    |
| `JZ`        | Salto a `resultado` si `arg1 <= 0`                              |
| `JG`        | Salto a `resultado` si `arg1 > 0`                               |
| `ERA`       | Reserva espacio para la llamada a la función `resultado`        |
| `PARAM`     | Asigna `arg1` como parámetro número `resultado`                 |
| `CALL`      | Llama a la función `resultado`                                  |
| `RET`       | Guarda el valor de retorno en `arg1`, retorna al llamador       |
| `ENDFUNC`   | Fin de función sin valor de retorno                             |
| `WRITE`     | Imprime el valor en `resultado`                                 |
| `END`       | Termina la ejecución del programa                               |

### Backpatching

Los saltos condicionales (`JZ`) e incondicionales (`JMP`) se emiten con destino `-1` cuando aún no se conoce el cuádruplo destino. Al finalizar el bloque correspondiente, se llama a `backpatch(índice, destino)` para rellenar el campo `resultado` con el cuádruplo correcto.

---

## 6. Memoria de Ejecución

La memoria de ejecución de la VM está dividida en cuatro segmentos lógicos, cada uno con subsecciones por tipo. La estructura está compuesta por tres clases principales: `MemoryManager` / `MemorySegment` (tiempo de compilación) y `Memory` / `DataSegment` / `StackFrame` (tiempo de ejecución).

### 6.1 `MemoryManager` y `MemorySegment` (tiempo de compilación)

`MemoryManager` es la clase que asigna direcciones virtuales durante la compilación. Contiene cuatro instancias de `MemorySegment`:

```cpp
struct MemorySegment {
    int base_int;    // dirección base para enteros
    int base_float;  // dirección base para flotantes
    int base_str;    // dirección base para cadenas

    int count_int   = 0;
    int count_float = 0;
    int count_str   = 0;

    int new_addr(Type type);  // retorna siguiente dirección disponible para ese tipo
    void reset_mem();         // reinicia contadores (al entrar a nueva función)
    int int_size();
    int float_size();
    int str_size();
};

class MemoryManager {
    MemorySegment global_memory  { 1000,  2500,  5000 };
    MemorySegment local_memory   { 7500, 10000, 12500 };
    MemorySegment temp_memory    {15000, 17500, 20000 };
    MemorySegment constant_memory{22500, 25000, 27500 };
};
```

### 6.2 `DataSegment` y `StackFrame` (tiempo de ejecución)

En la VM, la memoria se materializa en dos estructuras:

```cpp
class DataSegment {         // datos que viven todo el programa
    vector<long>   globals_int;
    vector<double> globals_float;
    vector<string> globals_str;

    vector<long>   const_int;
    vector<double> const_float;
    vector<string> const_str;
};

class StackFrame {          // datos de una invocación de función
    vector<long>   locals_int;
    vector<double> locals_float;
    vector<string> locals_str;

    vector<long>   temp_int;
    vector<double> temp_float;
    vector<string> temp_str;

    int return_quad;        // cuádruplo al que retornar al salir de la función
};
```

La clase `Memory` integra ambas:

```cpp
class Memory {
    stack<StackFrame> stack_segment;  // pila de frames activos
    DataSegment       data_segment;   // globales y constantes
    StackFrame        to_push;        // frame preparado antes del CALL
};
```

### 6.3 Versión gráfica de la memoria

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                         MAPA DE MEMORIA VIRTUAL                             │
├──────────────┬──────────────┬──────────────┬──────────────┬─────────────────┤
│   GLOBAL     │   LOCAL      │   TEMPORAL   │  CONSTANTE   │   Segmento      │
├──────────────┼──────────────┼──────────────┼──────────────┤                 │
│ 1000 – 2499  │ 7500 – 9999  │15000 – 17499 │22500 – 24999 │  entero (INT)   │
│ 2500 – 4999  │10000 – 12499 │17500 – 19999 │25000 – 27499 │  flotante(FLOAT)│
│ 5000 – 7499  │12500 – 14999 │20000 – 22499 │27500 –  ...  │  cadena (STR)   │
└──────────────┴──────────────┴──────────────┴──────────────┴─────────────────┘

  DataSegment (estático)          stack<StackFrame> (dinámico)
  ┌─────────────────────┐         ┌──────────────────────────┐  ← top (función activa)
  │  globals_int[]      │         │  locals_int[]            │
  │  globals_float[]    │         │  locals_float[]          │
  │  globals_str[]      │         │  locals_str[]            │
  │─────────────────────│         │  temp_int[]              │
  │  const_int[]        │         │  temp_float[]            │
  │  const_float[]      │         │  temp_str[]              │
  │  const_str[]        │         │  return_quad             │
  └─────────────────────┘         ├──────────────────────────┤
                                  │  frame anterior ...      │
                                  └──────────────────────────┘
```

### 6.4 Métodos principales de acceso

| Método | Descripción |
|--------|-------------|
| `Memory::push_stack(func_resources&)` | Empuja un nuevo `StackFrame` dimensionado según los recursos de la función |
| `Memory::prepare_frame(func_resources&)` | Construye el frame en `to_push` sin pushearlo (se completa con `PARAM`) |
| `Memory::push_call()` | Empuja `to_push` al stack y registra el `return_quad` |
| `Memory::store_num(Address, double)` | Escribe un valor numérico en la dirección virtual indicada (resuelve segmento por rango) |
| `Memory::get_num(Address)` | Lee un valor numérico de la dirección virtual indicada |
| `Memory::store_num_call_stack(Address, double)` | Escribe un argumento en el frame pendiente `to_push` (para `PARAM`) |
| `Memory::get_str(Address)` | Lee una cadena de la dirección virtual indicada |
| `Memory::is_int_address(int)` | Determina si una dirección corresponde a un entero |
| `MemorySegment::new_addr(Type)` | Asigna y retorna la siguiente dirección disponible para el tipo dado |
| `MemorySegment::reset_mem()` | Reinicia los contadores (al comenzar la compilación de una nueva función) |

---

## 7. Direcciones Virtuales

Una **dirección virtual** es un entero que identifica de forma única a cualquier variable, temporal o constante en el programa. El tipo `Address` es un `std::variant<int, std::string>` — entero para valores, cadena para nombres de función en instrucciones como `ERA` y `CALL`.

### Asignación en tiempo de compilación

Cuando el `QuadGenerator` visita una declaración de variable o una expresión que requiere un temporal, llama a `MemorySegment::new_addr(tipo)`:

```
nueva_dirección = base_tipo + contador_tipo++
```

Por ejemplo, si se declara la primera variable entera global:
```
addr = global_memory.base_int + global_memory.count_int++
     = 1000 + 0 = 1000
```
La segunda variable entera global recibe `1001`, y así sucesivamente.

### Indexación en tiempo de ejecución

En la VM, cada método de acceso (`get_num`, `store_num`, `get_str`) recibe una `Address` entera y determina a qué vector interno acceder restando la base del segmento:

```
si addr >= CONST_FLOAT_BASE (25000):
    vector = data_segment.const_float
    índice = addr - 25000

si addr >= CONST_INT_BASE (22500):
    vector = data_segment.const_int
    índice = addr - 22500

si addr >= TMP_FLOAT_BASE (17500):
    vector = stack.top().temp_float
    índice = addr - 17500

si addr >= TMP_INT_BASE (15000):
    vector = stack.top().temp_int
    índice = addr - 15000

si addr >= LOCAL_FLOAT_BASE (10000):
    vector = stack.top().locals_float
    índice = addr - 10000

si addr >= LOCAL_INT_BASE (7500):
    vector = stack.top().locals_int
    índice = addr - 7500

si addr >= GLOBAL_FLOAT_BASE (2500):
    vector = data_segment.globals_float
    índice = addr - 2500

si addr >= GLOBAL_INT_BASE (1000):
    vector = data_segment.globals_int
    índice = addr - 1000
```

Esto convierte cada dirección virtual en un índice directo de vector en O(1), sin necesidad de tablas hash en tiempo de ejecución. Las constantes se precalculan al construir el `DataSegment` a partir de la `const_table`.

### Ejemplo concreto

Dado el programa:
```
vars
  x : entero;
  y : flotante;
```

En compilación:
- `x` → dirección `1000` (global_int[0])
- `y` → dirección `2500` (global_float[0])

En ejecución, `store_num(1000, 42)` escribe `42` en `data_segment.globals_int[1000 - 1000]` = `globals_int[0]`.

---

## 8. Casos de Prueba

### Test 1: Hola Mundo

```
programa foo;
inicio
{
    escribe("hola mundo");
}
fin
```

**Salida esperada:**
```
hola mundo
```

---

### Test 2: Condicional con rama else

```
programa foo;
vars
  x : entero;
inicio
{
  x = -10;
  si (x > 0)
  {
      escribe("x es positivo");
  }
  sino
  {
      escribe("x es negativo");
  };
}
fin
```

**Salida esperada:**
```
x es negativo
```

---

### Test 3: Ciclo `mientras`

```
programa suma;
vars
  i      : entero;
  total  : entero;
inicio
{
    i     = 1;
    total = 0;
    mientras (i < 6)
    haz
    {
        total = total + i;
        i     = i + 1;
    };
    escribe(total);
}
fin
```

**Salida esperada:**
```
15
```

---

### Test 4: Función con retorno (factorial iterativo)

```
programa factorial;
vars
  x : entero;

entero factorial(n : entero) {
    vars
        i         : entero;
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
```

**Salida esperada:**
```
factorial:
120
```

---

### Test 5: Recursión (Fibonacci)

```
programa fib;
vars
  x : entero;

entero fib(n: entero) {
    {
        si (n < 2)
        {
            retorna n;
        };
        retorna fib(n - 1) + fib(n - 2);
    }
};

inicio
{
    x = 0;
    escribe("primeros 10 fibonacci");
    mientras (x < 10)
    haz
    {
        escribe(fib(x));
        x = x + 1;
    };
}
fin
```

**Salida esperada:**
```
primeros 10 fibonacci
0
1
1
2
3
5
8
13
21
34
```

---

### Test 6: Tipos mixtos y función flotante

```
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
        retorna res;
    }
};

inicio
{
    a = 3;
    f = promedio(3, 4.5);
    escribe(f);
}
fin
```

**Salida esperada:**
```
7.5
```

---

### Test 7: Múltiples argumentos en `escribe`

```
programa multi_print;
vars
  x : entero;
  y : entero;
inicio
{
    x = 10;
    y = 20;
    escribe("x =", x, "y =", y, "suma =", x + y);
}
fin
```

**Salida esperada:**
```
x =
10
y =
20
suma =
30
```

---

### Test 8: Error semántico — tipo incompatible

```
programa err;
vars
  x : entero;
  y : flotante;
inicio
{
    x = 3.14;
}
fin
```

**Comportamiento esperado:** error en tiempo de compilación indicando incompatibilidad de tipos en la asignación a `x`.

---

### Test 9: Error semántico — variable no declarada

```
programa err2;
inicio
{
    escribe(z);
}
fin
```

**Comportamiento esperado:** error semántico: `z is undeclared`.

---

### Test 10: Factorial recursivo

```
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
    x = 6;
    escribe("factorial recursivo:");
    escribe(factorial(x));
}
fin
```

**Salida esperada:**
```
factorial recursivo:
720
```
