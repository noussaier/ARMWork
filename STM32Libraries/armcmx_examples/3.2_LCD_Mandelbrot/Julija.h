#define REAL_CONSTANT -0.35f //0.285
#define IMG_CONSTANT  0.61f //0.01

#define REAL_CONSTANT2 -0.4f
#define IMG_CONSTANT2  0.6f

#define REAL_CONSTANT3  -0.70176f
#define IMG_CONSTANT3   0.3842f

#define REAL_CONSTANT4  -0.835f
#define IMG_CONSTANT4    0.2321f

#define REAL_CONSTANT5 -0.8f
#define IMG_CONSTANT5   0.156f

#define REAL_CONSTANT6 -0.74543f
#define IMG_CONSTANT6   0.11301f

#define REAL_CONSTANT7 -0.75f
#define IMG_CONSTANT7  0.11f

#define REAL_CONSTANT8 -0.1f
#define IMG_CONSTANT8   0.651f


#define REAL_CONSTANT9 0.001643721971153f
#define IMG_CONSTANT9  0.822467633298876f

#define ITERATION    256

#define ASSEMBLE_RGB(R ,G, B)    ((((R)& 0xF8) << 8) | (((G) & 0xFC) << 3) | (((B) & 0xF8) >> 3)) 


typedef struct {
    float x, y;
} Complex; 

int iterate (Complex zInit, int maxIter);
void Julia2(uint16_t size_x, uint16_t size_y, uint16_t offset_x, uint16_t offset_y, uint16_t zoom);
