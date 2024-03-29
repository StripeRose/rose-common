#pragma once

#define EXPAND(x) x
#define FOR_EACH_1(what, x, ...) what(x)
#define FOR_EACH_2(what, x, ...)\
  what(x);\
  EXPAND(FOR_EACH_1(what,  __VA_ARGS__))
#define FOR_EACH_3(what, x, ...)\
  what(x);\
  EXPAND(FOR_EACH_2(what, __VA_ARGS__))
#define FOR_EACH_4(what, x, ...)\
  what(x);\
  EXPAND(FOR_EACH_3(what,  __VA_ARGS__))
#define FOR_EACH_5(what, x, ...)\
  what(x);\
  EXPAND(FOR_EACH_4(what,  __VA_ARGS__))
#define FOR_EACH_6(what, x, ...)\
  what(x);\
  EXPAND(FOR_EACH_5(what,  __VA_ARGS__))
#define FOR_EACH_7(what, x, ...)\
  what(x);\
  EXPAND(FOR_EACH_6(what,  __VA_ARGS__))
#define FOR_EACH_8(what, x, ...)\
  what(x);\
  EXPAND(FOR_EACH_7(what,  __VA_ARGS__))
#define FOR_EACH_NARG(...) FOR_EACH_NARG_(__VA_ARGS__, FOR_EACH_RSEQ_N())
#define FOR_EACH_NARG_(...) EXPAND(FOR_EACH_ARG_N(__VA_ARGS__))
#define FOR_EACH_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N
#define FOR_EACH_RSEQ_N() 8, 7, 6, 5, 4, 3, 2, 1, 0
#define CONCATENATE(x,y) CONCATENATE_INNER(x, y)
#define CONCATENATE_INNER(x,y) x##y
#define STRINGIZE(x) STRINGIZE_INNER(x)
#define STRINGIZE_INNER(x) #x
#define FOR_EACH_(N, what, ...) EXPAND(CONCATENATE(FOR_EACH_, N)(what, __VA_ARGS__))
#define FOR_EACH(what, ...) FOR_EACH_(FOR_EACH_NARG(__VA_ARGS__), what, __VA_ARGS__)