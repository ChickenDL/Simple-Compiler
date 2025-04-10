<!--
 * @Descripttion: 
 * @version: 1.0
 * @Author: ZXL
 * @Date: 2025-04-06 11:25:11
 * @LastEditors: ZXL
 * @LastEditTime: 2025-04-10 17:00:34
-->
# Simple-Compiler

[![GitHub](https://img.shields.io/badge/GitHub-ChikenDL-181717?logo=github)](https://github.com/ChickenDL)
![Email](https://img.shields.io/badge/Email-torchimport_at_gmail_dot_com-D14836?logo=gmail)

A compiler implementation that performs **lexical and syntax analysis** for any given SLR(1) grammar.

## **Key Features**  
- ✅ **Lexical Analysis**: Tokenizes input source code.  
- ✅ **Syntax Analysis**: SLR(1) parsing with error reporting.  
- 📝 **Grammar Flexibility**: Supports custom SLR(1) grammars.  

## **Usage**
1. Define Grammar:
Edit the grammar rules in Grammar.txt
2. Construct Test Cases:
Edit the test cases in Test.txt 
3. Run Analysis:
Compile main.cpp
4. Output:
- FIRST Set and FOLLOW Set
- Itemset and SLR Analysis Table
- Syntax Analysis Process

## **Project Structure**  
```
dada/
├── Finalchar.txt               # Terminal
├── Grammar.txt                 # Production 
├── NotFinalchar.txt            # Non-terminal
result/
├── SLR Analysis Table.xlsx     # SLR analysis table for the given grammar
├── Test1.txt                   # The running result of test case 1
├── Test2.txt                   # The running result of test case 2
├── Test3.txt                   # The running result of test case 3
src/
├── main.cpp                    # Lexical and Syntax analyzer
test/
├── Test.txt                    # Test cases
├── Test1.txt                   # Test Case 1
├── Test2.txt                   # Test Case 2
├── Test3.txt                   # Test Case 3
```

## **Example**
Grammar Rule
```
S' -> S
S -> AB
A -> #n<h>A
A -> uptJ
B -> CD(){E}
C -> k
D -> m
E -> FE
E -> GE
E -> R
E -> f(M){N}e{N}E
E -> w(M){N}E
N -> F
N -> G
M -> M||O
M -> O
O -> O&&P
O -> P
P -> P==Q
P -> P!=Q
P -> Q
Q -> K<K
Q -> K<=K
Q -> K>=K
Q -> K>K
Q -> K
F -> b=KJ
J -> ;
K -> K+T
K -> K-T
K -> T
T -> T*L
T -> T/L
T -> L
L -> (K)
L -> b
L -> s
G -> HIJ
H -> k
I -> b
I -> b,I
R -> rsJ
```

Source Program
```
/*This is the test sample*/
# include<iostream>
# include<string>
using namespace std;
int main()
{
    int x,y,z;
    return 0;
}
```

Output
```
Lexical analysis result:
1: /*This is the test sample*/
    Note, content = This is the test sample
2: # include<iostream>
    Symbol: #
    INCLUDE: include
    Symbol: <
    Headfile: iostream
    Symbol: >
3: # include<string>
    Symbol: #
    INCLUDE: include
    Symbol: <
    Headfile: string
    Symbol: >
4: using namespace std;
    USING: using
    NAMESPACE: namespace
    STD: std
    Symbol: ;
5: int main()
    Keyword: int
    MAIN: main
    Symbol: (
    Symbol: )
6: {
    Symbol: {
7:     int x,y,z;
    Keyword: int
    ID, name = x
    Symbol: ,
    ID, name = y
    Symbol: ,
    ID, name = z
    Symbol: ;
8:     return 0;
    RETURN: return
    NUM-I, value = 0
    Symbol: ;
9: }
    Symbol: }

Sequence of lexical units:
#n<h>#n<h>upt;km(){kb,b,b;rs;}

Analysis process:
    stack                                                       symbol                                  input                                                                 action
1   0                                                                                                   #n<h>#n<h>upt;km(){kb,b,b;rs;}$                                       Move In
2   03                                                          #                                       n<h>#n<h>upt;km(){kb,b,b;rs;}$                                        Move In
3   038                                                         #n                                      <h>#n<h>upt;km(){kb,b,b;rs;}$                                         Move In
4   03812                                                       #n<                                     h>#n<h>upt;km(){kb,b,b;rs;}$                                          Move In
5   0381215                                                     #n<h                                    >#n<h>upt;km(){kb,b,b;rs;}$                                           Move In
6   038121519                                                   #n<h>                                   #n<h>upt;km(){kb,b,b;rs;}$                                            Move In
7   0381215193                                                  #n<h>#                                  n<h>upt;km(){kb,b,b;rs;}$                                             Move In
8   03812151938                                                 #n<h>#n                                 <h>upt;km(){kb,b,b;rs;}$                                              Move In
9   0381215193812                                               #n<h>#n<                                h>upt;km(){kb,b,b;rs;}$                                               Move In
10  038121519381215                                             #n<h>#n<h                               >upt;km(){kb,b,b;rs;}$                                                Move In
11  03812151938121519                                           #n<h>#n<h>                              upt;km(){kb,b,b;rs;}$                                                 Move In
12  038121519381215194                                          #n<h>#n<h>u                             pt;km(){kb,b,b;rs;}$                                                  Move In
13  0381215193812151949                                         #n<h>#n<h>up                            t;km(){kb,b,b;rs;}$                                                   Move In
14  038121519381215194913                                       #n<h>#n<h>upt                           ;km(){kb,b,b;rs;}$                                                    Move In
15  03812151938121519491317                                     #n<h>#n<h>upt;                          km(){kb,b,b;rs;}$                                                     According to J->; Reduction
16  03812151938121519491316                                     #n<h>#n<h>uptJ                          km(){kb,b,b;rs;}$                                                     According to A->uptJ Reduction
17  0381215193812151921                                         #n<h>#n<h>A                             km(){kb,b,b;rs;}$                                                     According to A->#n<h>A Reduction
18  03812151921                                                 #n<h>A                                  km(){kb,b,b;rs;}$                                                     According to A->#n<h>A Reduction
19  02                                                          A                                       km(){kb,b,b;rs;}$                                                     Move In
20  027                                                         Ak                                      m(){kb,b,b;rs;}$                                                      According to C->k Reduction
21  026                                                         AC                                      m(){kb,b,b;rs;}$                                                      Move In
22  02611                                                       ACm                                     (){kb,b,b;rs;}$                                                       According to D->m Reduction
23  02610                                                       ACD                                     (){kb,b,b;rs;}$                                                       Move In
24  0261014                                                     ACD(                                    ){kb,b,b;rs;}$                                                        Move In
25  026101418                                                   ACD()                                   {kb,b,b;rs;}$                                                         Move In
26  02610141820                                                 ACD(){                                  kb,b,b;rs;}$                                                          Move In
27  0261014182027                                               ACD(){k                                 b,b,b;rs;}$                                                           According to H->k Reduction
28  0261014182026                                               ACD(){H                                 b,b,b;rs;}$                                                           Move In
29  026101418202637                                             ACD(){Hb                                ,b,b;rs;}$                                                            Move In
30  02610141820263748                                           ACD(){Hb,                               b,b;rs;}$                                                             Move In
31  0261014182026374837                                         ACD(){Hb,b                              ,b;rs;}$                                                              Move In
32  026101418202637483748                                       ACD(){Hb,b,                             b;rs;}$                                                               Move In
33  02610141820263748374837                                     ACD(){Hb,b,b                            ;rs;}$                                                                According to I->b Reduction
34  02610141820263748374862                                     ACD(){Hb,b,I                            ;rs;}$                                                                According to I->b,I Reduction
35  0261014182026374862                                         ACD(){Hb,I                              ;rs;}$                                                                According to I->b,I Reduction
36  026101418202636                                             ACD(){HI                                ;rs;}$                                                                Move In
37  02610141820263617                                           ACD(){HI;                               rs;}$                                                                 According to J->; Reduction
38  02610141820263647                                           ACD(){HIJ                               rs;}$                                                                 According to G->HIJ Reduction
39  0261014182025                                               ACD(){G                                 rs;}$                                                                 Move In
40  026101418202529                                             ACD(){Gr                                s;}$                                                                  Move In
41  02610141820252938                                           ACD(){Grs                               ;}$                                                                   Move In
42  0261014182025293817                                         ACD(){Grs;                              }$                                                                    According to J->; Reduction
43  0261014182025293849                                         ACD(){GrsJ                              }$                                                                    According to R->rsJ Reduction
44  026101418202528                                             ACD(){GR                                }$                                                                    According to E->R Reduction
45  026101418202535                                             ACD(){GE                                }$                                                                    According to E->GE Reduction
46  0261014182022                                               ACD(){E                                 }$                                                                    Move In
47  026101418202232                                             ACD(){E}                                $                                                                     According to B->CD(){E} Reduction
48  025                                                         AB                                      $                                                                     According to S->AB Reduction
49  01                                                          S                                       $                                                                     Accept

The grammar of the source language can generate!
```