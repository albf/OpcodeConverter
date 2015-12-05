src/log.c: In function ‘vmessage’:
src/log.c:47:14: warning: implicit declaration of function ‘fileno’ [-Wimplicit-function-declaration]
   if (isatty(fileno(f)))
              ^
src/vm3.c:18:3: error: expected specifier-qualifier-list before ‘static’
   static void * code;
   ^
src/vm3.c: In function ‘vm_cpu_super’:
src/vm3.c:53:10: error: ‘struct pointer’ has no member named ‘code’
   test[0].code = NULL;
          ^
src/vm3.c:56:40: warning: excess elements in struct initializer
 struct pointer arrayswl[T_SIZE] = {  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                        ^
src/vm3.c:56:40: note: (near initialization for ‘arrayswl[0]’)
src/vm3.c:56:60: warning: excess elements in struct initializer
 struct pointer arrayswl[T_SIZE] = {  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                            ^
src/vm3.c:56:60: note: (near initialization for ‘arrayswl[1]’)
src/vm3.c:56:80: warning: excess elements in struct initializer
 struct pointer arrayswl[T_SIZE] = {  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                ^
src/vm3.c:56:80: note: (near initialization for ‘arrayswl[2]’)
src/vm3.c:56:100: warning: excess elements in struct initializer
 struct pointer arrayswl[T_SIZE] = {  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                    ^
src/vm3.c:56:100: note: (near initialization for ‘arrayswl[3]’)
src/vm3.c:56:120: warning: excess elements in struct initializer
 struct pointer arrayswl[T_SIZE] = {  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                                        ^
src/vm3.c:56:120: note: (near initialization for ‘arrayswl[4]’)
src/vm3.c:56:140: warning: excess elements in struct initializer
 struct pointer arrayswl[T_SIZE] = {  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                                                            ^
src/vm3.c:56:140: note: (near initialization for ‘arrayswl[5]’)
src/vm3.c:56:160: warning: excess elements in struct initializer
 struct pointer arrayswl[T_SIZE] = {  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                                                                                ^
src/vm3.c:56:160: note: (near initialization for ‘arrayswl[6]’)
src/vm3.c:56:180: warning: excess elements in struct initializer
 struct pointer arrayswl[T_SIZE] = {  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                                                                                                    ^
src/vm3.c:56:180: note: (near initialization for ‘arrayswl[7]’)
src/vm3.c:56:200: warning: excess elements in struct initializer
 struct pointer arrayswl[T_SIZE] = {  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                                                                                                                        ^
src/vm3.c:56:200: note: (near initialization for ‘arrayswl[8]’)
src/vm3.c:56:220: warning: excess elements in struct initializer
 struct pointer arrayswl[T_SIZE] = {  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                                                                                                                                            ^
src/vm3.c:56:220: note: (near initialization for ‘arrayswl[9]’)
src/vm3.c:57:7: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
       ^
src/vm3.c:57:7: note: (near initialization for ‘arrayswl[10]’)
src/vm3.c:57:27: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                           ^
src/vm3.c:57:27: note: (near initialization for ‘arrayswl[11]’)
src/vm3.c:57:47: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                               ^
src/vm3.c:57:47: note: (near initialization for ‘arrayswl[12]’)
src/vm3.c:57:67: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                   ^
src/vm3.c:57:67: note: (near initialization for ‘arrayswl[13]’)
src/vm3.c:57:87: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                       ^
src/vm3.c:57:87: note: (near initialization for ‘arrayswl[14]’)
src/vm3.c:57:107: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                           ^
src/vm3.c:57:107: note: (near initialization for ‘arrayswl[15]’)
src/vm3.c:57:127: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                                               ^
src/vm3.c:57:127: note: (near initialization for ‘arrayswl[16]’)
src/vm3.c:57:147: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                                                                   ^
src/vm3.c:57:147: note: (near initialization for ‘arrayswl[17]’)
src/vm3.c:57:167: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                                                                                       ^
src/vm3.c:57:167: note: (near initialization for ‘arrayswl[18]’)
src/vm3.c:57:187: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                                                                                                           ^
src/vm3.c:57:187: note: (near initialization for ‘arrayswl[19]’)
src/vm3.c:58:7: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
       ^
src/vm3.c:58:7: note: (near initialization for ‘arrayswl[20]’)
src/vm3.c:58:27: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                           ^
src/vm3.c:58:27: note: (near initialization for ‘arrayswl[21]’)
src/vm3.c:58:47: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                               ^
src/vm3.c:58:47: note: (near initialization for ‘arrayswl[22]’)
src/vm3.c:58:67: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                   ^
src/vm3.c:58:67: note: (near initialization for ‘arrayswl[23]’)
src/vm3.c:58:87: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                       ^
src/vm3.c:58:87: note: (near initialization for ‘arrayswl[24]’)
src/vm3.c:58:107: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                           ^
src/vm3.c:58:107: note: (near initialization for ‘arrayswl[25]’)
src/vm3.c:58:127: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                                               ^
src/vm3.c:58:127: note: (near initialization for ‘arrayswl[26]’)
src/vm3.c:58:147: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                                                                   ^
src/vm3.c:58:147: note: (near initialization for ‘arrayswl[27]’)
src/vm3.c:58:167: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                                                                                       ^
src/vm3.c:58:167: note: (near initialization for ‘arrayswl[28]’)
src/vm3.c:58:187: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                                                                                                           ^
src/vm3.c:58:187: note: (near initialization for ‘arrayswl[29]’)
src/vm3.c:59:7: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
       ^
src/vm3.c:59:7: note: (near initialization for ‘arrayswl[30]’)
src/vm3.c:59:27: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                           ^
src/vm3.c:59:27: note: (near initialization for ‘arrayswl[31]’)
src/vm3.c:59:47: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                               ^
src/vm3.c:59:47: note: (near initialization for ‘arrayswl[32]’)
src/vm3.c:59:67: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                   ^
src/vm3.c:59:67: note: (near initialization for ‘arrayswl[33]’)
src/vm3.c:59:87: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                       ^
src/vm3.c:59:87: note: (near initialization for ‘arrayswl[34]’)
src/vm3.c:59:107: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                           ^
src/vm3.c:59:107: note: (near initialization for ‘arrayswl[35]’)
src/vm3.c:59:127: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                                               ^
src/vm3.c:59:127: note: (near initialization for ‘arrayswl[36]’)
src/vm3.c:59:147: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                                                                   ^
src/vm3.c:59:147: note: (near initialization for ‘arrayswl[37]’)
src/vm3.c:59:167: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                                                                                       ^
src/vm3.c:59:167: note: (near initialization for ‘arrayswl[38]’)
src/vm3.c:59:187: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                                                                                                           ^
src/vm3.c:59:187: note: (near initialization for ‘arrayswl[39]’)
src/vm3.c:60:7: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
       ^
src/vm3.c:60:7: note: (near initialization for ‘arrayswl[40]’)
src/vm3.c:60:27: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                           ^
src/vm3.c:60:27: note: (near initialization for ‘arrayswl[41]’)
src/vm3.c:60:47: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                               ^
src/vm3.c:60:47: note: (near initialization for ‘arrayswl[42]’)
src/vm3.c:60:67: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                   ^
src/vm3.c:60:67: note: (near initialization for ‘arrayswl[43]’)
src/vm3.c:60:87: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                       ^
src/vm3.c:60:87: note: (near initialization for ‘arrayswl[44]’)
src/vm3.c:60:107: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                           ^
src/vm3.c:60:107: note: (near initialization for ‘arrayswl[45]’)
src/vm3.c:60:127: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                                               ^
src/vm3.c:60:127: note: (near initialization for ‘arrayswl[46]’)
src/vm3.c:60:147: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                                                                   ^
src/vm3.c:60:147: note: (near initialization for ‘arrayswl[47]’)
src/vm3.c:60:167: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                                                                                       ^
src/vm3.c:60:167: note: (near initialization for ‘arrayswl[48]’)
src/vm3.c:60:187: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                                                                                                           ^
src/vm3.c:60:187: note: (near initialization for ‘arrayswl[49]’)
src/vm3.c:61:7: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
       ^
src/vm3.c:61:7: note: (near initialization for ‘arrayswl[50]’)
src/vm3.c:61:27: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                           ^
src/vm3.c:61:27: note: (near initialization for ‘arrayswl[51]’)
src/vm3.c:61:47: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                               ^
src/vm3.c:61:47: note: (near initialization for ‘arrayswl[52]’)
src/vm3.c:61:67: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                   ^
src/vm3.c:61:67: note: (near initialization for ‘arrayswl[53]’)
src/vm3.c:61:87: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                       ^
src/vm3.c:61:87: note: (near initialization for ‘arrayswl[54]’)
src/vm3.c:61:107: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                           ^
src/vm3.c:61:107: note: (near initialization for ‘arrayswl[55]’)
src/vm3.c:61:127: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                                               ^
src/vm3.c:61:127: note: (near initialization for ‘arrayswl[56]’)
src/vm3.c:61:147: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                                                                   ^
src/vm3.c:61:147: note: (near initialization for ‘arrayswl[57]’)
src/vm3.c:61:167: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                                                                                       ^
src/vm3.c:61:167: note: (near initialization for ‘arrayswl[58]’)
src/vm3.c:61:187: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                                                                                                           ^
src/vm3.c:61:187: note: (near initialization for ‘arrayswl[59]’)
src/vm3.c:62:7: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
       ^
src/vm3.c:62:7: note: (near initialization for ‘arrayswl[60]’)
src/vm3.c:62:27: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                           ^
src/vm3.c:62:27: note: (near initialization for ‘arrayswl[61]’)
src/vm3.c:62:47: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                               ^
src/vm3.c:62:47: note: (near initialization for ‘arrayswl[62]’)
src/vm3.c:62:67: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                   ^
src/vm3.c:62:67: note: (near initialization for ‘arrayswl[63]’)
src/vm3.c:62:87: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                       ^
src/vm3.c:62:87: note: (near initialization for ‘arrayswl[64]’)
src/vm3.c:62:107: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                           ^
src/vm3.c:62:107: note: (near initialization for ‘arrayswl[65]’)
src/vm3.c:62:127: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                                               ^
src/vm3.c:62:127: note: (near initialization for ‘arrayswl[66]’)
src/vm3.c:62:147: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                                                                   ^
src/vm3.c:62:147: note: (near initialization for ‘arrayswl[67]’)
src/vm3.c:62:167: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                                                                                       ^
src/vm3.c:62:167: note: (near initialization for ‘arrayswl[68]’)
src/vm3.c:62:187: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                                                                                                           ^
src/vm3.c:62:187: note: (near initialization for ‘arrayswl[69]’)
src/vm3.c:63:7: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
       ^
src/vm3.c:63:7: note: (near initialization for ‘arrayswl[70]’)
src/vm3.c:63:27: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                           ^
src/vm3.c:63:27: note: (near initialization for ‘arrayswl[71]’)
src/vm3.c:63:47: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                               ^
src/vm3.c:63:47: note: (near initialization for ‘arrayswl[72]’)
src/vm3.c:63:67: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                   ^
src/vm3.c:63:67: note: (near initialization for ‘arrayswl[73]’)
src/vm3.c:63:87: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                       ^
src/vm3.c:63:87: note: (near initialization for ‘arrayswl[74]’)
src/vm3.c:63:107: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                           ^
src/vm3.c:63:107: note: (near initialization for ‘arrayswl[75]’)
src/vm3.c:63:127: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                                               ^
src/vm3.c:63:127: note: (near initialization for ‘arrayswl[76]’)
src/vm3.c:63:147: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                                                                   ^
src/vm3.c:63:147: note: (near initialization for ‘arrayswl[77]’)
src/vm3.c:63:167: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                                                                                       ^
src/vm3.c:63:167: note: (near initialization for ‘arrayswl[78]’)
src/vm3.c:63:187: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                                                                                                           ^
src/vm3.c:63:187: note: (near initialization for ‘arrayswl[79]’)
src/vm3.c:64:7: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swlPLUSswl, NULL }  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
       ^
src/vm3.c:64:7: note: (near initialization for ‘arrayswl[80]’)
src/vm3.c:64:27: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swlPLUSswl, NULL }  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                           ^
src/vm3.c:64:27: note: (near initialization for ‘arrayswl[81]’)
src/vm3.c:64:47: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swlPLUSswl, NULL }  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                               ^
src/vm3.c:64:47: note: (near initialization for ‘arrayswl[82]’)
src/vm3.c:64:67: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swlPLUSswl, NULL }  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                   ^
src/vm3.c:64:67: note: (near initialization for ‘arrayswl[83]’)
src/vm3.c:64:87: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swlPLUSswl, NULL }  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                       ^
src/vm3.c:64:87: note: (near initialization for ‘arrayswl[84]’)
src/vm3.c:64:107: warning: excess elements in struct initializer
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swlPLUSswl, NULL }  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                           ^
src/vm3.c:64:107: note: (near initialization for ‘arrayswl[85]’)
src/vm3.c:64:129: error: expected ‘}’ before ‘{’ token
  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swlPLUSswl, NULL }  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL }  ,  { &&swl, NULL } 
                                                                                                                                 ^
src/vm3.c:69:37: warning: excess elements in struct initializer
 struct pointer array[T_SIZE] = {  { &&sll, NULL }  ,  { &&error, NULL }  ,  { &&srl, NULL }  ,  { &&sra, NULL }  ,  { &&sllv, NULL }  ,  { &&error, NULL }  ,  { &&srlv, NULL }  ,  { &&srav, NULL }  ,  { &&jr, NULL }  ,  { &&jalr, NULL } 
                                     ^
src/vm3.c:69:37: note: (near initialization for ‘array[0]’)
src/vm3.c:69:57: warning: excess elements in struct initializer
 struct pointer array[T_SIZE] = {  { &&sll, NULL }  ,  { &&error, NULL }  ,  { &&srl, NULL }  ,  { &&sra, NULL }  ,  { &&sllv, NULL }  ,  { &&error, NULL }  ,  { &&srlv, NULL }  ,  { &&srav, NULL }  ,  { &&jr, NULL }  ,  { &&jalr, NULL } 
                                                         ^
src/vm3.c:69:57: note: (near initialization for ‘array[1]’)
src/vm3.c:69:79: warning: excess elements in struct initializer
 struct pointer array[T_SIZE] = {  { &&sll, NULL }  ,  { &&error, NULL }  ,  { &&srl, NULL }  ,  { &&sra, NULL }  ,  { &&sllv, NULL }  ,  { &&error, NULL }  ,  { &&srlv, NULL }  ,  { &&srav, NULL }  ,  { &&jr, NULL }  ,  { &&jalr, NULL } 
                                                                               ^
src/vm3.c:69:79: note: (near initialization for ‘array[2]’)
src/vm3.c:69:99: warning: excess elements in struct initializer
 struct pointer array[T_SIZE] = {  { &&sll, NULL }  ,  { &&error, NULL }  ,  { &&srl, NULL }  ,  { &&sra, NULL }  ,  { &&sllv, NULL }  ,  { &&error, NULL }  ,  { &&srlv, NULL }  ,  { &&srav, NULL }  ,  { &&jr, NULL }  ,  { &&jalr, NULL } 
                                                                                                   ^
src/vm3.c:69:99: note: (near initialization for ‘array[3]’)
src/vm3.c:69:119: warning: excess elements in struct initializer
 struct pointer array[T_SIZE] = {  { &&sll, NULL }  ,  { &&error, NULL }  ,  { &&srl, NULL }  ,  { &&sra, NULL }  ,  { &&sllv, NULL }  ,  { &&error, NULL }  ,  { &&srlv, NULL }  ,  { &&srav, NULL }  ,  { &&jr, NULL }  ,  { &&jalr, NULL } 
                                                                                                                       ^
src/vm3.c:69:119: note: (near initialization for ‘array[4]’)
src/vm3.c:69:140: warning: excess elements in struct initializer
 struct pointer array[T_SIZE] = {  { &&sll, NULL }  ,  { &&error, NULL }  ,  { &&srl, NULL }  ,  { &&sra, NULL }  ,  { &&sllv, NULL }  ,  { &&error, NULL }  ,  { &&srlv, NULL }  ,  { &&srav, NULL }  ,  { &&jr, NULL }  ,  { &&jalr, NULL } 
                                                                                                                                            ^
src/vm3.c:69:140: note: (near initialization for ‘array[5]’)
src/vm3.c:69:162: warning: excess elements in struct initializer
 struct pointer array[T_SIZE] = {  { &&sll, NULL }  ,  { &&error, NULL }  ,  { &&srl, NULL }  ,  { &&sra, NULL }  ,  { &&sllv, NULL }  ,  { &&error, NULL }  ,  { &&srlv, NULL }  ,  { &&srav, NULL }  ,  { &&jr, NULL }  ,  { &&jalr, NULL } 
                                                                                                                                                                  ^
src/vm3.c:69:162: note: (near initialization for ‘array[6]’)
src/vm3.c:69:183: warning: excess elements in struct initializer
 struct pointer array[T_SIZE] = {  { &&sll, NULL }  ,  { &&error, NULL }  ,  { &&srl, NULL }  ,  { &&sra, NULL }  ,  { &&sllv, NULL }  ,  { &&error, NULL }  ,  { &&srlv, NULL }  ,  { &&srav, NULL }  ,  { &&jr, NULL }  ,  { &&jalr, NULL } 
                                                                                                                                                                                       ^
src/vm3.c:69:183: note: (near initialization for ‘array[7]’)
src/vm3.c:69:204: warning: excess elements in struct initializer
 struct pointer array[T_SIZE] = {  { &&sll, NULL }  ,  { &&error, NULL }  ,  { &&srl, NULL }  ,  { &&sra, NULL }  ,  { &&sllv, NULL }  ,  { &&error, NULL }  ,  { &&srlv, NULL }  ,  { &&srav, NULL }  ,  { &&jr, NULL }  ,  { &&jalr, NULL } 
                                                                                                                                                                                                            ^
src/vm3.c:69:204: note: (near initialization for ‘array[8]’)
src/vm3.c:69:223: warning: excess elements in struct initializer
 struct pointer array[T_SIZE] = {  { &&sll, NULL }  ,  { &&error, NULL }  ,  { &&srl, NULL }  ,  { &&sra, NULL }  ,  { &&sllv, NULL }  ,  { &&error, NULL }  ,  { &&srlv, NULL }  ,  { &&srav, NULL }  ,  { &&jr, NULL }  ,  { &&jalr, NULL } 
                                                                                                                                                                                                                               ^
src/vm3.c:69:223: note: (near initialization for ‘array[9]’)
src/vm3.c:70:7: warning: excess elements in struct initializer
  ,  { &&movz, NULL }  ,  { &&movn, NULL }  ,  { &&sysc, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&mfhi, NULL }  ,  { &&mthi, NULL }  ,  { &&mflo, NULL }  ,  { &&mtlo, NULL } 
       ^
src/vm3.c:70:7: note: (near initialization for ‘array[10]’)
src/vm3.c:70:28: warning: excess elements in struct initializer
  ,  { &&movz, NULL }  ,  { &&movn, NULL }  ,  { &&sysc, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&mfhi, NULL }  ,  { &&mthi, NULL }  ,  { &&mflo, NULL }  ,  { &&mtlo, NULL } 
                            ^
src/vm3.c:70:28: note: (near initialization for ‘array[11]’)
src/vm3.c:70:49: warning: excess elements in struct initializer
  ,  { &&movz, NULL }  ,  { &&movn, NULL }  ,  { &&sysc, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&mfhi, NULL }  ,  { &&mthi, NULL }  ,  { &&mflo, NULL }  ,  { &&mtlo, NULL } 
                                                 ^
src/vm3.c:70:49: note: (near initialization for ‘array[12]’)
src/vm3.c:70:70: warning: excess elements in struct initializer
  ,  { &&movz, NULL }  ,  { &&movn, NULL }  ,  { &&sysc, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&mfhi, NULL }  ,  { &&mthi, NULL }  ,  { &&mflo, NULL }  ,  { &&mtlo, NULL } 
                                                                      ^
src/vm3.c:70:70: note: (near initialization for ‘array[13]’)
src/vm3.c:70:92: warning: excess elements in struct initializer
  ,  { &&movz, NULL }  ,  { &&movn, NULL }  ,  { &&sysc, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&mfhi, NULL }  ,  { &&mthi, NULL }  ,  { &&mflo, NULL }  ,  { &&mtlo, NULL } 
                                                                                            ^
src/vm3.c:70:92: note: (near initialization for ‘array[14]’)
src/vm3.c:70:114: warning: excess elements in struct initializer
  ,  { &&movz, NULL }  ,  { &&movn, NULL }  ,  { &&sysc, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&mfhi, NULL }  ,  { &&mthi, NULL }  ,  { &&mflo, NULL }  ,  { &&mtlo, NULL } 
                                                                                                                  ^
src/vm3.c:70:114: note: (near initialization for ‘array[15]’)
src/vm3.c:70:136: warning: excess elements in struct initializer
  ,  { &&movz, NULL }  ,  { &&movn, NULL }  ,  { &&sysc, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&mfhi, NULL }  ,  { &&mthi, NULL }  ,  { &&mflo, NULL }  ,  { &&mtlo, NULL } 
                                                                                                                                        ^
src/vm3.c:70:136: note: (near initialization for ‘array[16]’)
src/vm3.c:70:157: warning: excess elements in struct initializer
  ,  { &&movz, NULL }  ,  { &&movn, NULL }  ,  { &&sysc, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&mfhi, NULL }  ,  { &&mthi, NULL }  ,  { &&mflo, NULL }  ,  { &&mtlo, NULL } 
                                                                                                                                                             ^
src/vm3.c:70:157: note: (near initialization for ‘array[17]’)
src/vm3.c:70:178: warning: excess elements in struct initializer
  ,  { &&movz, NULL }  ,  { &&movn, NULL }  ,  { &&sysc, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&mfhi, NULL }  ,  { &&mthi, NULL }  ,  { &&mflo, NULL }  ,  { &&mtlo, NULL } 
                                                                                                                                                                                  ^
src/vm3.c:70:178: note: (near initialization for ‘array[18]’)
src/vm3.c:70:199: warning: excess elements in struct initializer
  ,  { &&movz, NULL }  ,  { &&movn, NULL }  ,  { &&sysc, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&mfhi, NULL }  ,  { &&mthi, NULL }  ,  { &&mflo, NULL }  ,  { &&mtlo, NULL } 
                                                                                                                                                                                                       ^
src/vm3.c:70:199: note: (near initialization for ‘array[19]’)
src/vm3.c:71:7: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&mult, NULL }  ,  { &&multu, NULL }  ,  { &&div, NULL }  ,  { &&divu, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL } 
       ^
src/vm3.c:71:7: note: (near initialization for ‘array[20]’)
src/vm3.c:71:29: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&mult, NULL }  ,  { &&multu, NULL }  ,  { &&div, NULL }  ,  { &&divu, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL } 
                             ^
src/vm3.c:71:29: note: (near initialization for ‘array[21]’)
src/vm3.c:71:51: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&mult, NULL }  ,  { &&multu, NULL }  ,  { &&div, NULL }  ,  { &&divu, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL } 
                                                   ^
src/vm3.c:71:51: note: (near initialization for ‘array[22]’)
src/vm3.c:71:73: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&mult, NULL }  ,  { &&multu, NULL }  ,  { &&div, NULL }  ,  { &&divu, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL } 
                                                                         ^
src/vm3.c:71:73: note: (near initialization for ‘array[23]’)
src/vm3.c:71:95: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&mult, NULL }  ,  { &&multu, NULL }  ,  { &&div, NULL }  ,  { &&divu, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL } 
                                                                                               ^
src/vm3.c:71:95: note: (near initialization for ‘array[24]’)
src/vm3.c:71:116: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&mult, NULL }  ,  { &&multu, NULL }  ,  { &&div, NULL }  ,  { &&divu, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL } 
                                                                                                                    ^
src/vm3.c:71:116: note: (near initialization for ‘array[25]’)
src/vm3.c:71:138: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&mult, NULL }  ,  { &&multu, NULL }  ,  { &&div, NULL }  ,  { &&divu, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL } 
                                                                                                                                          ^
src/vm3.c:71:138: note: (near initialization for ‘array[26]’)
src/vm3.c:71:158: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&mult, NULL }  ,  { &&multu, NULL }  ,  { &&div, NULL }  ,  { &&divu, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL } 
                                                                                                                                                              ^
src/vm3.c:71:158: note: (near initialization for ‘array[27]’)
src/vm3.c:71:179: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&mult, NULL }  ,  { &&multu, NULL }  ,  { &&div, NULL }  ,  { &&divu, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL } 
                                                                                                                                                                                   ^
src/vm3.c:71:179: note: (near initialization for ‘array[28]’)
src/vm3.c:71:201: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&mult, NULL }  ,  { &&multu, NULL }  ,  { &&div, NULL }  ,  { &&divu, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL } 
                                                                                                                                                                                                         ^
src/vm3.c:71:201: note: (near initialization for ‘array[29]’)
src/vm3.c:72:7: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&add, NULL }  ,  { &&addu, NULL }  ,  { &&sub, NULL }  ,  { &&subu, NULL }  ,  { &&and, NULL }  ,  { &&or, NULL }  ,  { &&xor, NULL }  ,  { &&nor, NULL } 
       ^
src/vm3.c:72:7: note: (near initialization for ‘array[30]’)
src/vm3.c:72:29: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&add, NULL }  ,  { &&addu, NULL }  ,  { &&sub, NULL }  ,  { &&subu, NULL }  ,  { &&and, NULL }  ,  { &&or, NULL }  ,  { &&xor, NULL }  ,  { &&nor, NULL } 
                             ^
src/vm3.c:72:29: note: (near initialization for ‘array[31]’)
src/vm3.c:72:51: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&add, NULL }  ,  { &&addu, NULL }  ,  { &&sub, NULL }  ,  { &&subu, NULL }  ,  { &&and, NULL }  ,  { &&or, NULL }  ,  { &&xor, NULL }  ,  { &&nor, NULL } 
                                                   ^
src/vm3.c:72:51: note: (near initialization for ‘array[32]’)
src/vm3.c:72:71: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&add, NULL }  ,  { &&addu, NULL }  ,  { &&sub, NULL }  ,  { &&subu, NULL }  ,  { &&and, NULL }  ,  { &&or, NULL }  ,  { &&xor, NULL }  ,  { &&nor, NULL } 
                                                                       ^
src/vm3.c:72:71: note: (near initialization for ‘array[33]’)
src/vm3.c:72:92: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&add, NULL }  ,  { &&addu, NULL }  ,  { &&sub, NULL }  ,  { &&subu, NULL }  ,  { &&and, NULL }  ,  { &&or, NULL }  ,  { &&xor, NULL }  ,  { &&nor, NULL } 
                                                                                            ^
src/vm3.c:72:92: note: (near initialization for ‘array[34]’)
src/vm3.c:72:112: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&add, NULL }  ,  { &&addu, NULL }  ,  { &&sub, NULL }  ,  { &&subu, NULL }  ,  { &&and, NULL }  ,  { &&or, NULL }  ,  { &&xor, NULL }  ,  { &&nor, NULL } 
                                                                                                                ^
src/vm3.c:72:112: note: (near initialization for ‘array[35]’)
src/vm3.c:72:133: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&add, NULL }  ,  { &&addu, NULL }  ,  { &&sub, NULL }  ,  { &&subu, NULL }  ,  { &&and, NULL }  ,  { &&or, NULL }  ,  { &&xor, NULL }  ,  { &&nor, NULL } 
                                                                                                                                     ^
src/vm3.c:72:133: note: (near initialization for ‘array[36]’)
src/vm3.c:72:153: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&add, NULL }  ,  { &&addu, NULL }  ,  { &&sub, NULL }  ,  { &&subu, NULL }  ,  { &&and, NULL }  ,  { &&or, NULL }  ,  { &&xor, NULL }  ,  { &&nor, NULL } 
                                                                                                                                                         ^
src/vm3.c:72:153: note: (near initialization for ‘array[37]’)
src/vm3.c:72:172: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&add, NULL }  ,  { &&addu, NULL }  ,  { &&sub, NULL }  ,  { &&subu, NULL }  ,  { &&and, NULL }  ,  { &&or, NULL }  ,  { &&xor, NULL }  ,  { &&nor, NULL } 
                                                                                                                                                                            ^
src/vm3.c:72:172: note: (near initialization for ‘array[38]’)
src/vm3.c:72:192: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&add, NULL }  ,  { &&addu, NULL }  ,  { &&sub, NULL }  ,  { &&subu, NULL }  ,  { &&and, NULL }  ,  { &&or, NULL }  ,  { &&xor, NULL }  ,  { &&nor, NULL } 
                                                                                                                                                                                                ^
src/vm3.c:72:192: note: (near initialization for ‘array[39]’)
src/vm3.c:73:7: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&slt, NULL }  ,  { &&sltu, NULL }  ,  { &&branch, NULL }  ,  { &&jump, NULL }  ,  { &&jal, NULL }  ,  { &&beq, NULL }  ,  { &&bne, NULL }  ,  { &&blez, NULL } 
       ^
src/vm3.c:73:7: note: (near initialization for ‘array[40]’)
src/vm3.c:73:29: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&slt, NULL }  ,  { &&sltu, NULL }  ,  { &&branch, NULL }  ,  { &&jump, NULL }  ,  { &&jal, NULL }  ,  { &&beq, NULL }  ,  { &&bne, NULL }  ,  { &&blez, NULL } 
                             ^
src/vm3.c:73:29: note: (near initialization for ‘array[41]’)
src/vm3.c:73:51: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&slt, NULL }  ,  { &&sltu, NULL }  ,  { &&branch, NULL }  ,  { &&jump, NULL }  ,  { &&jal, NULL }  ,  { &&beq, NULL }  ,  { &&bne, NULL }  ,  { &&blez, NULL } 
                                                   ^
src/vm3.c:73:51: note: (near initialization for ‘array[42]’)
src/vm3.c:73:71: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&slt, NULL }  ,  { &&sltu, NULL }  ,  { &&branch, NULL }  ,  { &&jump, NULL }  ,  { &&jal, NULL }  ,  { &&beq, NULL }  ,  { &&bne, NULL }  ,  { &&blez, NULL } 
                                                                       ^
src/vm3.c:73:71: note: (near initialization for ‘array[43]’)
src/vm3.c:73:92: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&slt, NULL }  ,  { &&sltu, NULL }  ,  { &&branch, NULL }  ,  { &&jump, NULL }  ,  { &&jal, NULL }  ,  { &&beq, NULL }  ,  { &&bne, NULL }  ,  { &&blez, NULL } 
                                                                                            ^
src/vm3.c:73:92: note: (near initialization for ‘array[44]’)
src/vm3.c:73:115: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&slt, NULL }  ,  { &&sltu, NULL }  ,  { &&branch, NULL }  ,  { &&jump, NULL }  ,  { &&jal, NULL }  ,  { &&beq, NULL }  ,  { &&bne, NULL }  ,  { &&blez, NULL } 
                                                                                                                   ^
src/vm3.c:73:115: note: (near initialization for ‘array[45]’)
src/vm3.c:73:136: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&slt, NULL }  ,  { &&sltu, NULL }  ,  { &&branch, NULL }  ,  { &&jump, NULL }  ,  { &&jal, NULL }  ,  { &&beq, NULL }  ,  { &&bne, NULL }  ,  { &&blez, NULL } 
                                                                                                                                        ^
src/vm3.c:73:136: note: (near initialization for ‘array[46]’)
src/vm3.c:73:156: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&slt, NULL }  ,  { &&sltu, NULL }  ,  { &&branch, NULL }  ,  { &&jump, NULL }  ,  { &&jal, NULL }  ,  { &&beq, NULL }  ,  { &&bne, NULL }  ,  { &&blez, NULL } 
                                                                                                                                                            ^
src/vm3.c:73:156: note: (near initialization for ‘array[47]’)
src/vm3.c:73:176: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&slt, NULL }  ,  { &&sltu, NULL }  ,  { &&branch, NULL }  ,  { &&jump, NULL }  ,  { &&jal, NULL }  ,  { &&beq, NULL }  ,  { &&bne, NULL }  ,  { &&blez, NULL } 
                                                                                                                                                                                ^
src/vm3.c:73:176: note: (near initialization for ‘array[48]’)
src/vm3.c:73:196: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&slt, NULL }  ,  { &&sltu, NULL }  ,  { &&branch, NULL }  ,  { &&jump, NULL }  ,  { &&jal, NULL }  ,  { &&beq, NULL }  ,  { &&bne, NULL }  ,  { &&blez, NULL } 
                                                                                                                                                                                                    ^
src/vm3.c:73:196: note: (near initialization for ‘array[49]’)
src/vm3.c:74:7: warning: excess elements in struct initializer
  ,  { &&bgtz, NULL }  ,  { &&addi, NULL }  ,  { &&addiu, NULL }  ,  { &&slti, NULL }  ,  { &&sltiu, NULL }  ,  { &&andi, NULL }  ,  { &&ori, NULL }  ,  { &&xori, NULL }  ,  { &&lui, NULL }  ,  { &&error, NULL } 
       ^
src/vm3.c:74:7: note: (near initialization for ‘array[50]’)
src/vm3.c:74:28: warning: excess elements in struct initializer
  ,  { &&bgtz, NULL }  ,  { &&addi, NULL }  ,  { &&addiu, NULL }  ,  { &&slti, NULL }  ,  { &&sltiu, NULL }  ,  { &&andi, NULL }  ,  { &&ori, NULL }  ,  { &&xori, NULL }  ,  { &&lui, NULL }  ,  { &&error, NULL } 
                            ^
src/vm3.c:74:28: note: (near initialization for ‘array[51]’)
src/vm3.c:74:49: warning: excess elements in struct initializer
  ,  { &&bgtz, NULL }  ,  { &&addi, NULL }  ,  { &&addiu, NULL }  ,  { &&slti, NULL }  ,  { &&sltiu, NULL }  ,  { &&andi, NULL }  ,  { &&ori, NULL }  ,  { &&xori, NULL }  ,  { &&lui, NULL }  ,  { &&error, NULL } 
                                                 ^
src/vm3.c:74:49: note: (near initialization for ‘array[52]’)
src/vm3.c:74:71: warning: excess elements in struct initializer
  ,  { &&bgtz, NULL }  ,  { &&addi, NULL }  ,  { &&addiu, NULL }  ,  { &&slti, NULL }  ,  { &&sltiu, NULL }  ,  { &&andi, NULL }  ,  { &&ori, NULL }  ,  { &&xori, NULL }  ,  { &&lui, NULL }  ,  { &&error, NULL } 
                                                                       ^
src/vm3.c:74:71: note: (near initialization for ‘array[53]’)
src/vm3.c:74:92: warning: excess elements in struct initializer
  ,  { &&bgtz, NULL }  ,  { &&addi, NULL }  ,  { &&addiu, NULL }  ,  { &&slti, NULL }  ,  { &&sltiu, NULL }  ,  { &&andi, NULL }  ,  { &&ori, NULL }  ,  { &&xori, NULL }  ,  { &&lui, NULL }  ,  { &&error, NULL } 
                                                                                            ^
src/vm3.c:74:92: note: (near initialization for ‘array[54]’)
src/vm3.c:74:114: warning: excess elements in struct initializer
  ,  { &&bgtz, NULL }  ,  { &&addi, NULL }  ,  { &&addiu, NULL }  ,  { &&slti, NULL }  ,  { &&sltiu, NULL }  ,  { &&andi, NULL }  ,  { &&ori, NULL }  ,  { &&xori, NULL }  ,  { &&lui, NULL }  ,  { &&error, NULL } 
                                                                                                                  ^
src/vm3.c:74:114: note: (near initialization for ‘array[55]’)
src/vm3.c:74:135: warning: excess elements in struct initializer
  ,  { &&bgtz, NULL }  ,  { &&addi, NULL }  ,  { &&addiu, NULL }  ,  { &&slti, NULL }  ,  { &&sltiu, NULL }  ,  { &&andi, NULL }  ,  { &&ori, NULL }  ,  { &&xori, NULL }  ,  { &&lui, NULL }  ,  { &&error, NULL } 
                                                                                                                                       ^
src/vm3.c:74:135: note: (near initialization for ‘array[56]’)
src/vm3.c:74:155: warning: excess elements in struct initializer
  ,  { &&bgtz, NULL }  ,  { &&addi, NULL }  ,  { &&addiu, NULL }  ,  { &&slti, NULL }  ,  { &&sltiu, NULL }  ,  { &&andi, NULL }  ,  { &&ori, NULL }  ,  { &&xori, NULL }  ,  { &&lui, NULL }  ,  { &&error, NULL } 
                                                                                                                                                           ^
src/vm3.c:74:155: note: (near initialization for ‘array[57]’)
src/vm3.c:74:176: warning: excess elements in struct initializer
  ,  { &&bgtz, NULL }  ,  { &&addi, NULL }  ,  { &&addiu, NULL }  ,  { &&slti, NULL }  ,  { &&sltiu, NULL }  ,  { &&andi, NULL }  ,  { &&ori, NULL }  ,  { &&xori, NULL }  ,  { &&lui, NULL }  ,  { &&error, NULL } 
                                                                                                                                                                                ^
src/vm3.c:74:176: note: (near initialization for ‘array[58]’)
src/vm3.c:74:196: warning: excess elements in struct initializer
  ,  { &&bgtz, NULL }  ,  { &&addi, NULL }  ,  { &&addiu, NULL }  ,  { &&slti, NULL }  ,  { &&sltiu, NULL }  ,  { &&andi, NULL }  ,  { &&ori, NULL }  ,  { &&xori, NULL }  ,  { &&lui, NULL }  ,  { &&error, NULL } 
                                                                                                                                                                                                    ^
src/vm3.c:74:196: note: (near initialization for ‘array[59]’)
src/vm3.c:75:7: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&llo, NULL }  ,  { &&lhi, NULL }  ,  { &&trap, NULL } 
       ^
src/vm3.c:75:7: note: (near initialization for ‘array[60]’)
src/vm3.c:75:29: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&llo, NULL }  ,  { &&lhi, NULL }  ,  { &&trap, NULL } 
                             ^
src/vm3.c:75:29: note: (near initialization for ‘array[61]’)
src/vm3.c:75:51: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&llo, NULL }  ,  { &&lhi, NULL }  ,  { &&trap, NULL } 
                                                   ^
src/vm3.c:75:51: note: (near initialization for ‘array[62]’)
src/vm3.c:75:73: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&llo, NULL }  ,  { &&lhi, NULL }  ,  { &&trap, NULL } 
                                                                         ^
src/vm3.c:75:73: note: (near initialization for ‘array[63]’)
src/vm3.c:75:95: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&llo, NULL }  ,  { &&lhi, NULL }  ,  { &&trap, NULL } 
                                                                                               ^
src/vm3.c:75:95: note: (near initialization for ‘array[64]’)
src/vm3.c:75:117: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&llo, NULL }  ,  { &&lhi, NULL }  ,  { &&trap, NULL } 
                                                                                                                     ^
src/vm3.c:75:117: note: (near initialization for ‘array[65]’)
src/vm3.c:75:139: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&llo, NULL }  ,  { &&lhi, NULL }  ,  { &&trap, NULL } 
                                                                                                                                           ^
src/vm3.c:75:139: note: (near initialization for ‘array[66]’)
src/vm3.c:75:161: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&llo, NULL }  ,  { &&lhi, NULL }  ,  { &&trap, NULL } 
                                                                                                                                                                 ^
src/vm3.c:75:161: note: (near initialization for ‘array[67]’)
src/vm3.c:75:181: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&llo, NULL }  ,  { &&lhi, NULL }  ,  { &&trap, NULL } 
                                                                                                                                                                                     ^
src/vm3.c:75:181: note: (near initialization for ‘array[68]’)
src/vm3.c:75:201: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&llo, NULL }  ,  { &&lhi, NULL }  ,  { &&trap, NULL } 
                                                                                                                                                                                                         ^
src/vm3.c:75:201: note: (near initialization for ‘array[69]’)
src/vm3.c:76:7: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&lb, NULL }  ,  { &&lh, NULL }  ,  { &&lwl, NULL }  ,  { &&lw, NULL }  ,  { &&lbu, NULL } 
       ^
src/vm3.c:76:7: note: (near initialization for ‘array[70]’)
src/vm3.c:76:29: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&lb, NULL }  ,  { &&lh, NULL }  ,  { &&lwl, NULL }  ,  { &&lw, NULL }  ,  { &&lbu, NULL } 
                             ^
src/vm3.c:76:29: note: (near initialization for ‘array[71]’)
src/vm3.c:76:51: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&lb, NULL }  ,  { &&lh, NULL }  ,  { &&lwl, NULL }  ,  { &&lw, NULL }  ,  { &&lbu, NULL } 
                                                   ^
src/vm3.c:76:51: note: (near initialization for ‘array[72]’)
src/vm3.c:76:73: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&lb, NULL }  ,  { &&lh, NULL }  ,  { &&lwl, NULL }  ,  { &&lw, NULL }  ,  { &&lbu, NULL } 
                                                                         ^
src/vm3.c:76:73: note: (near initialization for ‘array[73]’)
src/vm3.c:76:95: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&lb, NULL }  ,  { &&lh, NULL }  ,  { &&lwl, NULL }  ,  { &&lw, NULL }  ,  { &&lbu, NULL } 
                                                                                               ^
src/vm3.c:76:95: note: (near initialization for ‘array[74]’)
src/vm3.c:76:117: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&lb, NULL }  ,  { &&lh, NULL }  ,  { &&lwl, NULL }  ,  { &&lw, NULL }  ,  { &&lbu, NULL } 
                                                                                                                     ^
src/vm3.c:76:117: note: (near initialization for ‘array[75]’)
src/vm3.c:76:136: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&lb, NULL }  ,  { &&lh, NULL }  ,  { &&lwl, NULL }  ,  { &&lw, NULL }  ,  { &&lbu, NULL } 
                                                                                                                                        ^
src/vm3.c:76:136: note: (near initialization for ‘array[76]’)
src/vm3.c:76:155: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&lb, NULL }  ,  { &&lh, NULL }  ,  { &&lwl, NULL }  ,  { &&lw, NULL }  ,  { &&lbu, NULL } 
                                                                                                                                                           ^
src/vm3.c:76:155: note: (near initialization for ‘array[77]’)
src/vm3.c:76:175: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&lb, NULL }  ,  { &&lh, NULL }  ,  { &&lwl, NULL }  ,  { &&lw, NULL }  ,  { &&lbu, NULL } 
                                                                                                                                                                               ^
src/vm3.c:76:175: note: (near initialization for ‘array[78]’)
src/vm3.c:76:194: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&lb, NULL }  ,  { &&lh, NULL }  ,  { &&lwl, NULL }  ,  { &&lw, NULL }  ,  { &&lbu, NULL } 
                                                                                                                                                                                                  ^
src/vm3.c:76:194: note: (near initialization for ‘array[79]’)
src/vm3.c:77:7: warning: excess elements in struct initializer
  ,  { &&lhu, NULL }  ,  { &&lwr, NULL }  ,  { &&error, NULL }  ,  { &&sb, NULL }  ,  { &&sh, NULL }  ,  { NULL, &arrayswl }  ,  { &&sw, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&swr, NULL } 
       ^
src/vm3.c:77:7: note: (near initialization for ‘array[80]’)
src/vm3.c:77:27: warning: excess elements in struct initializer
  ,  { &&lhu, NULL }  ,  { &&lwr, NULL }  ,  { &&error, NULL }  ,  { &&sb, NULL }  ,  { &&sh, NULL }  ,  { NULL, &arrayswl }  ,  { &&sw, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&swr, NULL } 
                           ^
src/vm3.c:77:27: note: (near initialization for ‘array[81]’)
src/vm3.c:77:47: warning: excess elements in struct initializer
  ,  { &&lhu, NULL }  ,  { &&lwr, NULL }  ,  { &&error, NULL }  ,  { &&sb, NULL }  ,  { &&sh, NULL }  ,  { NULL, &arrayswl }  ,  { &&sw, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&swr, NULL } 
                                               ^
src/vm3.c:77:47: note: (near initialization for ‘array[82]’)
src/vm3.c:77:69: warning: excess elements in struct initializer
  ,  { &&lhu, NULL }  ,  { &&lwr, NULL }  ,  { &&error, NULL }  ,  { &&sb, NULL }  ,  { &&sh, NULL }  ,  { NULL, &arrayswl }  ,  { &&sw, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&swr, NULL } 
                                                                     ^
src/vm3.c:77:69: note: (near initialization for ‘array[83]’)
src/vm3.c:77:88: warning: excess elements in struct initializer
  ,  { &&lhu, NULL }  ,  { &&lwr, NULL }  ,  { &&error, NULL }  ,  { &&sb, NULL }  ,  { &&sh, NULL }  ,  { NULL, &arrayswl }  ,  { &&sw, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&swr, NULL } 
                                                                                        ^
src/vm3.c:77:88: note: (near initialization for ‘array[84]’)
src/vm3.c:77:113: warning: excess elements in struct initializer
  ,  { &&lhu, NULL }  ,  { &&lwr, NULL }  ,  { &&error, NULL }  ,  { &&sb, NULL }  ,  { &&sh, NULL }  ,  { NULL, &arrayswl }  ,  { &&sw, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&swr, NULL } 
                                                                                                                 ^
src/vm3.c:77:113: note: (near initialization for ‘array[85]’)
src/vm3.c:77:131: warning: excess elements in struct initializer
  ,  { &&lhu, NULL }  ,  { &&lwr, NULL }  ,  { &&error, NULL }  ,  { &&sb, NULL }  ,  { &&sh, NULL }  ,  { NULL, &arrayswl }  ,  { &&sw, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&swr, NULL } 
                                                                                                                                   ^
src/vm3.c:77:131: note: (near initialization for ‘array[86]’)
src/vm3.c:77:150: warning: excess elements in struct initializer
  ,  { &&lhu, NULL }  ,  { &&lwr, NULL }  ,  { &&error, NULL }  ,  { &&sb, NULL }  ,  { &&sh, NULL }  ,  { NULL, &arrayswl }  ,  { &&sw, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&swr, NULL } 
                                                                                                                                                      ^
src/vm3.c:77:150: note: (near initialization for ‘array[87]’)
src/vm3.c:77:172: warning: excess elements in struct initializer
  ,  { &&lhu, NULL }  ,  { &&lwr, NULL }  ,  { &&error, NULL }  ,  { &&sb, NULL }  ,  { &&sh, NULL }  ,  { NULL, &arrayswl }  ,  { &&sw, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&swr, NULL } 
                                                                                                                                                                            ^
src/vm3.c:77:172: note: (near initialization for ‘array[88]’)
src/vm3.c:77:194: warning: excess elements in struct initializer
  ,  { &&lhu, NULL }  ,  { &&lwr, NULL }  ,  { &&error, NULL }  ,  { &&sb, NULL }  ,  { &&sh, NULL }  ,  { NULL, &arrayswl }  ,  { &&sw, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&swr, NULL } 
                                                                                                                                                                                                  ^
src/vm3.c:77:194: note: (near initialization for ‘array[89]’)
src/vm3.c:78:7: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL } 
       ^
src/vm3.c:78:7: note: (near initialization for ‘array[90]’)
src/vm3.c:78:29: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL } 
                             ^
src/vm3.c:78:29: note: (near initialization for ‘array[91]’)
src/vm3.c:78:51: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL } 
                                                   ^
src/vm3.c:78:51: note: (near initialization for ‘array[92]’)
src/vm3.c:78:73: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL } 
                                                                         ^
src/vm3.c:78:73: note: (near initialization for ‘array[93]’)
src/vm3.c:78:95: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL } 
                                                                                               ^
src/vm3.c:78:95: note: (near initialization for ‘array[94]’)
src/vm3.c:78:117: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL } 
                                                                                                                     ^
src/vm3.c:78:117: note: (near initialization for ‘array[95]’)
src/vm3.c:78:139: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL } 
                                                                                                                                           ^
src/vm3.c:78:139: note: (near initialization for ‘array[96]’)
src/vm3.c:78:161: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL } 
                                                                                                                                                                 ^
src/vm3.c:78:161: note: (near initialization for ‘array[97]’)
src/vm3.c:78:183: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL } 
                                                                                                                                                                                       ^
src/vm3.c:78:183: note: (near initialization for ‘array[98]’)
src/vm3.c:78:205: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL } 
                                                                                                                                                                                                             ^
src/vm3.c:78:205: note: (near initialization for ‘array[99]’)
src/vm3.c:79:7: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL } 
       ^
src/vm3.c:79:7: note: (near initialization for ‘array[100]’)
src/vm3.c:79:29: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL } 
                             ^
src/vm3.c:79:29: note: (near initialization for ‘array[101]’)
src/vm3.c:79:51: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL } 
                                                   ^
src/vm3.c:79:51: note: (near initialization for ‘array[102]’)
src/vm3.c:79:73: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL } 
                                                                         ^
src/vm3.c:79:73: note: (near initialization for ‘array[103]’)
src/vm3.c:79:95: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL } 
                                                                                               ^
src/vm3.c:79:95: note: (near initialization for ‘array[104]’)
src/vm3.c:79:117: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL } 
                                                                                                                     ^
src/vm3.c:79:117: note: (near initialization for ‘array[105]’)
src/vm3.c:79:139: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL } 
                                                                                                                                           ^
src/vm3.c:79:139: note: (near initialization for ‘array[106]’)
src/vm3.c:79:161: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL } 
                                                                                                                                                                 ^
src/vm3.c:79:161: note: (near initialization for ‘array[107]’)
src/vm3.c:79:183: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL } 
                                                                                                                                                                                       ^
src/vm3.c:79:183: note: (near initialization for ‘array[108]’)
src/vm3.c:79:205: warning: excess elements in struct initializer
  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL } 
                                                                                                                                                                                                             ^
src/vm3.c:79:205: note: (near initialization for ‘array[109]’)
src/vm3.c:93:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:94:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:96:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:108:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:133:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:134:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:136:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:148:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:173:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:174:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:176:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:188:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:213:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:214:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:216:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:228:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:253:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:254:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:256:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:268:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:293:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:294:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:296:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:308:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:333:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:334:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:336:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:348:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:373:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:374:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:376:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:388:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:414:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:415:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:417:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:429:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:455:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:456:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:458:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:470:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:495:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:496:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:498:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:510:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:535:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:536:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:538:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:550:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:575:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:576:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:578:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:590:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:615:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:616:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:618:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:630:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:661:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:662:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:664:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:676:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:701:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:702:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:704:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:716:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:741:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:742:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:744:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:756:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:781:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:782:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:784:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:796:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:821:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:822:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:824:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:836:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:861:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:862:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:864:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:876:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:901:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:902:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:904:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:916:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:941:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:942:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:944:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:956:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:981:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:982:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:984:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:996:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:1026:19: error: subscripted value is neither array nor pointer nor vector
   goto *array[op0][op1];
                   ^
src/vm3.c:1039:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:1040:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:1042:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:1054:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:1083:19: error: subscripted value is neither array nor pointer nor vector
   goto *array[op0][op1];
                   ^
src/vm3.c:1096:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:1097:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:1099:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:1111:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:1134:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:1135:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:1137:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:1149:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:1172:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:1173:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:1175:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:1187:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:1210:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:1211:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:1213:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:1225:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:1248:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:1249:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:1251:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:1263:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:1289:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:1290:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:1292:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:1304:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:1329:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:1330:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:1332:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:1344:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:1369:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:1370:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:1372:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:1384:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:1409:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:1410:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:1412:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:1424:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:1449:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:1450:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:1452:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:1464:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:1489:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:1490:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:1492:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:1504:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:1529:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:1530:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:1532:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:1544:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:1568:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:1569:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:1571:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:1583:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:1607:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:1608:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:1610:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:1622:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:1647:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:1648:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:1650:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:1662:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:1687:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:1688:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:1690:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:1702:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:1737:19: error: subscripted value is neither array nor pointer nor vector
   goto *array[op0][op1];
                   ^
src/vm3.c:1777:19: error: subscripted value is neither array nor pointer nor vector
   goto *array[op0][op1];
                   ^
src/vm3.c:1816:19: error: subscripted value is neither array nor pointer nor vector
   goto *array[op0][op1];
                   ^
src/vm3.c:1856:19: error: subscripted value is neither array nor pointer nor vector
   goto *array[op0][op1];
                   ^
src/vm3.c:1876:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:1877:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:1879:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:1891:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:1924:19: error: subscripted value is neither array nor pointer nor vector
   goto *array[op0][op1];
                   ^
src/vm3.c:1943:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:1944:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:1946:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:1958:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:1990:19: error: subscripted value is neither array nor pointer nor vector
   goto *array[op0][op1];
                   ^
src/vm3.c:2009:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:2010:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:2012:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:2024:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:2056:19: error: subscripted value is neither array nor pointer nor vector
   goto *array[op0][op1];
                   ^
src/vm3.c:2075:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:2076:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:2078:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:2090:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:2123:19: error: subscripted value is neither array nor pointer nor vector
   goto *array[op0][op1];
                   ^
src/vm3.c:2142:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:2143:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:2145:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:2157:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:2182:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:2183:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:2185:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:2197:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:2222:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:2223:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:2225:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:2237:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:2262:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:2263:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:2265:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:2277:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:2302:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:2303:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:2305:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:2317:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:2342:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:2343:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:2345:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:2357:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:2382:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:2383:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:2385:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:2397:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:2423:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:2424:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:2426:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:2438:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:2466:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:2467:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:2469:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:2481:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:2510:19: error: subscripted value is neither array nor pointer nor vector
   goto *array[op0][op1];
                   ^
src/vm3.c:2523:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:2524:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:2526:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:2538:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:2568:19: error: subscripted value is neither array nor pointer nor vector
   goto *array[op0][op1];
                   ^
src/vm3.c:2581:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:2582:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:2584:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:2596:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:2619:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:2620:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:2622:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:2634:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:2659:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:2660:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:2662:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:2674:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:2700:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:2701:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:2703:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:2715:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:2740:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:2741:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:2743:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:2755:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:2780:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:2781:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:2783:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:2795:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:2815:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:2816:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:2818:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:2830:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
src/vm3.c:2866:11: error: ‘struct pointer’ has no member named ‘next_level’
 if (p[op0].next_level == NULL)
           ^
src/vm3.c:2867:15: error: ‘struct pointer’ has no member named ‘code’
   goto *p[op0].code;
               ^
src/vm3.c:2869:13: error: ‘struct pointer’ has no member named ‘next_level’
   p = p[op0].next_level;
             ^
src/vm3.c:2881:13: error: ‘struct pointer’ has no member named ‘code’
 goto *p[op1].code;
             ^
In file included from src/ARCH/i386_OS/OS_loader.c:6:0:
src/EH.h:114:17: warning: inline function ‘event_timer’ declared but never defined
 void __inline__ event_timer(void); //To be called by the timer and then process data from sensors and (maybe) generate events
                 ^
make: *** [i386] Error 1
