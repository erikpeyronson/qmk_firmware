#include "progmem.h"

// Helidox 8x6 font with QMK Firmware Logo
// Online editor: http://teripom.x0.com/

static const unsigned char font[] PROGMEM = {0,  0,  0,  0,  0,  0, 62,  91, 79, 91,  62,  0,   62,  107, 79, 107, 62,  0,   28,  62,  124, 62,  28,  0,   24,  60,  126, 60,  24,  0,   28,  87,  125, 87,  28,  0,  28,  94, 127, 94, 28, 0, 0,  24,  60,  24,  0,   0,   255, 231, 195, 231, 255, 0,   0,   24,  36,  24, 0, 0,   255, 231, 219, 231, 255, 0,   48,  72,  58,  6,   14,  0,   38,  41,  121, 41,  38,  0,   64,  127, 5,   5,   7,   0, 64,  127, 5,   37,  63,  0,   90,  60,  231, 60,  90,  0,   127, 62, 28, 28,  8,   0,   8,   28,  28,  62,  127, 0,   20,  34,  127, 34,  20,  0, 95, 95, 0,  95, 95, 0, 6,  9,  127, 1,   127, 0, 0,   102, 137, 149, 106, 0,   96,  96,  96,  96,  96, 0, 148, 162, 255, 162, 148, 0,   8,   4,   126, 4,   8,   0, 16, 32,  126, 32,  16,  0,  8,  8,   42,  28,  8,  0, 8,   28,  42,  8,   8,   0,   30,  16,  16,  16, 16,  0, 12, 30, 12, 30, 12,  0, 48, 56, 62, 56, 48, 0, 6,  14, 62, 14, 6,  0,
                                             0,  0,  0,  0,  0,  0, 0,   0,  95, 0,   0,   0,   0,   7,   0,  7,   0,   0,   20,  127, 20,  127, 20,  0,   36,  42,  127, 42,  18,  0,   35,  19,  8,   100, 98,  0,  54,  73, 86,  32, 80, 0, 0,  8,   7,   3,   0,   0,   0,   28,  34,  65,  0,   0,   0,   65,  34,  28, 0, 0,   42,  28,  127, 28,  42,  0,   8,   8,   62,  8,   8,   0,   0,   128, 112, 48,  0,   0,   8,   8,   8,   8,   8,   0, 0,   0,   96,  96,  0,   0,   32,  16,  8,   4,   2,   0,   62,  81, 73, 69,  62,  0,   0,   66,  127, 64,  0,   0,   114, 73,  73,  73,  70,  0, 33, 65, 73, 77, 51, 0, 24, 20, 18,  127, 16,  0, 39,  69,  69,  69,  57,  0,   60,  74,  73,  73,  49, 0, 65,  33,  17,  9,   7,   0,   54,  73,  73,  73,  54,  0, 70, 73,  73,  41,  30,  0,  0,  0,   20,  0,   0,  0, 0,   64,  52,  0,   0,   0,   0,   8,   20,  34, 65,  0, 20, 20, 20, 20, 20,  0, 0,  65, 34, 20, 8,  0, 2,  1,  89, 9,  6,  0,
                                             62, 65, 93, 89, 78, 0, 124, 18, 17, 18,  124, 0,   127, 73,  73, 73,  54,  0,   62,  65,  65,  65,  34,  0,   127, 65,  65,  65,  62,  0,   127, 73,  73,  73,  65,  0,  127, 9,  9,   9,  1,  0, 62, 65,  65,  81,  115, 0,   127, 8,   8,   8,   127, 0,   0,   65,  127, 65, 0, 0,   32,  64,  65,  63,  1,   0,   127, 8,   20,  34,  65,  0,   127, 64,  64,  64,  64,  0,   127, 2,   28,  2,   127, 0, 127, 4,   8,   16,  127, 0,   62,  65,  65,  65,  62,  0,   127, 9,  9,  9,   6,   0,   62,  65,  81,  33,  94,  0,   127, 9,   25,  41,  70,  0, 38, 73, 73, 73, 50, 0, 3,  1,  127, 1,   3,   0, 63,  64,  64,  64,  63,  0,   31,  32,  64,  32,  31, 0, 63,  64,  56,  64,  63,  0,   99,  20,  8,   20,  99,  0, 3,  4,   120, 4,   3,   0,  97, 89,  73,  77,  67, 0, 0,   127, 65,  65,  65,  0,   2,   4,   8,   16, 32,  0, 0,  65, 65, 65, 127, 0, 4,  2,  1,  2,  4,  0, 64, 64, 64, 64, 64, 0,
                                             0,  3,  7,  8,  0,  0, 32,  84, 84, 120, 64,  0,   127, 40,  68, 68,  56,  0,   56,  68,  68,  68,  40,  0,   56,  68,  68,  40,  127, 0,   56,  84,  84,  84,  24,  0,  0,   8,  126, 9,  2,  0, 24, 36,  36,  28,  120, 0,   127, 8,   4,   4,   120, 0,   0,   68,  125, 64, 0, 0,   32,  64,  64,  61,  0,   0,   127, 16,  40,  68,  0,   0,   0,   65,  127, 64,  0,   0,   124, 4,   120, 4,   120, 0, 124, 8,   4,   4,   120, 0,   56,  68,  68,  68,  56,  0,   124, 24, 36, 36,  24,  0,   24,  36,  36,  24,  124, 0,   124, 8,   4,   4,   8,   0, 72, 84, 84, 84, 36, 0, 4,  4,  63,  68,  36,  0, 60,  64,  64,  32,  124, 0,   28,  32,  64,  32,  28, 0, 60,  64,  48,  64,  60,  0,   68,  40,  16,  40,  68,  0, 76, 144, 144, 144, 124, 0,  68, 100, 84,  76,  68, 0, 0,   8,   54,  65,  0,   0,   0,   0,   119, 0,  0,   0, 0,  65, 54, 8,  0,   0, 2,  1,  2,  4,  2,  0, 60, 38, 35, 38, 60, 0,
                                             0,  0,  24, 24, 0,  0, 0,   0,  0,  0,   0,   0,   0,   0,   0,  0,   192, 224, 240, 248, 248, 24,  0,   192, 240, 252, 254, 255, 255, 255, 255, 255, 255, 255, 126, 0,  0,   0,  0,   0,  0,  0, 0,  0,   128, 192, 224, 224, 224, 224, 224, 224, 224, 224, 192, 128, 0,   0,  0, 0,   128, 192, 224, 224, 224, 224, 224, 224, 224, 224, 192, 128, 0,   0,   0,   224, 224, 192, 192, 224, 224, 224, 224, 0, 0,   224, 224, 192, 192, 224, 224, 224, 224, 224, 192, 128, 0,   0,  0,  0,   128, 192, 224, 224, 224, 224, 224, 224, 224, 224, 192, 128, 0,   0, 0,  0,  0,  0,  0,  0, 0,  0,  0,   0,   0,   0, 224, 240, 240, 240, 224, 236, 238, 247, 243, 112, 32, 0, 124, 124, 124, 126, 0,   126, 126, 126, 127, 127, 127, 0, 0,  128, 192, 224, 126, 91, 79, 91,  254, 192, 0,  0, 192, 0,   220, 215, 222, 222, 222, 215, 220, 0,  192, 0, 0,  0,  0,  0,  0,   0, 0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0,
                                             0,  0,  0,  0,  0,  0, 0,   0,  0,  248, 252, 254, 255, 224, 0,  255, 255, 255, 255, 255, 255, 128, 255, 255, 255, 255, 255, 255, 255, 255, 255, 31,  7,   1,   0,   0,  0,   0,  0,   0,  0,  0, 0,  255, 255, 255, 129, 0,   0,   0,   0,   0,   0,   129, 195, 195, 195, 0,  0, 255, 255, 255, 129, 0,   0,   0,   0,   0,   0,   129, 255, 255, 255, 0,   0,   255, 255, 255, 1,   0,   0,   0,   0,   0, 0,   255, 255, 255, 1,   0,   0,   0,   0,   1,   255, 255, 255, 0,  0,  255, 255, 255, 157, 28,  28,  28,  28,  28,  28,  157, 223, 223, 223, 0, 0,  0,  0,  0,  0,  0, 0,  0,  0,   0,   0,   0, 15,  31,  63,  127, 127, 127, 127, 127, 63,  30,  12, 0, 31,  31,  31,  63,  0,   63,  63,  63,  127, 127, 127, 0, 48, 123, 127, 120, 48,  32, 32, 48,  120, 127, 59, 0, 3,   0,   15,  127, 15,  15,  15,  127, 15,  0,  3,   0, 0,  0,  0,  0,  0,   0, 0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0,
                                             0,  0,  0,  0,  0,  0, 0,   0,  0,  3,   15,  31,  63,  63,  63, 63,  31,  31,  63,  63,  127, 127, 127, 63,  63,  31,  63,  127, 127, 127, 127, 124, 120, 120, 56,  28, 15,  0,  0,   0,  0,  0, 0,  0,   1,   3,   7,   7,   7,   7,   7,   7,   7,   7,   3,   1,   0,   0,  0, 0,   1,   3,   7,   7,   7,   7,   7,   7,   7,   7,   3,   1,   0,   0,   0,   7,   7,   7,   0,   0,   0,   0,   0,   0, 0,   7,   7,   7,   0,   0,   0,   0,   0,   0,   7,   7,   7,   0,  0,  0,   1,   3,   7,   7,   7,   7,   7,   7,   7,   7,   3,   1,   0,   0, 0,  0,  0,  0,  0,  0, 0,  0,  0,   0,   0,   0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 0,  0,   0,   0,   0,   0,  0,  0,   0,   0,   0,  0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,   0, 0,  0,  0,  0,  0,   0, 0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0};
